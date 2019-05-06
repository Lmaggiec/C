#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int miss;
int hit;
struct line** cache;
unsigned long int count;
int read;
int write;
int i,j,min;

typedef struct line{
    unsigned long int tag;
    int valid;
    unsigned long int data;
}line;

line** createcache(int setnum,int assoc){
    cache=(line**)malloc(setnum*sizeof(line*));
    for(i=0;i<setnum;i++){
        cache[i]=(line*)malloc((assoc)*sizeof(line));
    }
    for(i=0;i<setnum;i++){
        for(j=0;j<assoc;j++){
            cache[i][j].valid=0;
        }
    }
return cache;
}

void readf(unsigned long int tagindex,unsigned long int setindex,int assoc){
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            miss++;
            read++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].data=count;
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                hit++;
                count++;
                cache[setindex][i].data=count;
                return;
            }
            if(i==(assoc-1)){
                miss++;
                read++;
                count++;
                min=0;
                for(j=0;j<assoc;j++){
                    if(cache[setindex][j].data<=cache[setindex][min].data){
                        min=j;
                    }   
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                cache[setindex][min].data=count;
                return;
            }
        }
    }
return;
}

void empty(int setnum, int assoc){
    for(i=0;i<setnum;i++){
        for(j=0;j<assoc;j++){
            cache[i][j].tag=0;
            cache[i][j].valid=0;
            cache[i][j].data=0;
        }
    }
    miss=0;
    hit=0;
    read=0;
    write=0;
    count=0;
}

void prefetch(unsigned long int tagindex,unsigned long int setindex,int assoc){
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            read++;        
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].data=count;
            return;
        }else{            
            if(cache[setindex][i].tag==tagindex){
                return;
            }
            if(i==(assoc-1)){
                read++;
                count++;
                min=0;
                for(j=0;j<assoc;j++){
                    if(cache[setindex][j].data<=cache[setindex][min].data){
                        min=j;
                    }   
                }                
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                cache[setindex][min].data=count;
                return;
            }    
        }
    }
return;
}
 
void prefetchr(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int newtagindex,unsigned long int newsetindex){
    for(i=0;i<assoc;i++){
        if(cache[setindex][i].valid==0){
            miss++;
            read++;
            count++;
            cache[setindex][i].valid=1;
            cache[setindex][i].tag=tagindex;
            cache[setindex][i].data=count;
            prefetch(newtagindex,newsetindex,assoc);
            return;
        }else{
            if(cache[setindex][i].tag==tagindex){
                hit++;
                count++;
                cache[setindex][i].data=count;
                return;
            }
            if(i==(assoc-1)){
                miss++;
                read++;
                count++;
                min=0;
                for(j=0;j<assoc;j++){
                    if(cache[setindex][j].data<=cache[setindex][min].data){
                        min=j;
                    }   
                }
                cache[setindex][min].valid=1;
                cache[setindex][min].tag=tagindex;
                cache[setindex][min].data=count;
                prefetch(newtagindex,newsetindex,assoc);
                return;
            } 
        }
    }
return;
}
 

int main(int argc, char** argv){
    int cachesize=atoi(argv[1]);
    int blocksize=atoi(argv[4]);
    int n;
    int setnum;
    int assoc;
    int b;
    int s;
    char op;
    unsigned long int setmask;
    unsigned long int tagindex;
    unsigned long int setindex;

    if(argv[3][0]=='l'){
        FILE* fl;
        fl=fopen(argv[5],"r");
        if(fl==NULL){
            printf("error\n");
            exit(0);
        }

        if(argv[2][0]=='d'){
            assoc=1;
            setnum=cachesize/blocksize;
        }else if(argv[2][5]!=':'){
            assoc=cachesize/blocksize;
            setnum=1;
        }else if(argv[2][5]==':'){
            sscanf(argv[2],"assoc:%d",&n);
            assoc=n;
            setnum=cachesize/blocksize/n;
        }else{
            printf("error\n");
            exit(0);
        }
        cache=createcache(setnum,assoc);
        b=log(blocksize)/log(2);
        s=log(setnum)/log(2);
        setmask=((1<<s)-1);

        unsigned long int address;

        while(fscanf(fl, "%*x: %c %lx", &op, &address)==2){
            setindex=(address>>b)&setmask;
            tagindex=address>>(b+s);

            if(op=='R'){
                readf(tagindex,setindex,assoc);
            }else if(op=='W'){
                write++;
                readf(tagindex,setindex,assoc);
            }
        }

        fclose(fl);

        fl=fopen(argv[5],"r");

        if(fl==NULL){
            printf("error\n");
            exit(0);
        }

        printf("no-prefetch\n");
        printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",read,write,hit,miss);

        empty(setnum,assoc);
        unsigned long int newaddress;
        unsigned long int newtagindex;
        unsigned long int newsetindex;

        while(fscanf(fl, "%*x: %c %lx", &op, &address)==2){
            setindex=(address>>b)&setmask;
            tagindex=address>>(b+s);
            newaddress=address+blocksize;
            newsetindex=(newaddress>>b)&setmask;
            newtagindex=newaddress>>(b+s);

            if(op=='R'){
                prefetchr(tagindex,setindex,assoc,newtagindex,newsetindex);    
            }else if(op=='W'){
                write++;
                prefetchr(tagindex,setindex,assoc,newtagindex,newsetindex);
            }
        }

        printf("with-prefetch\n");
        printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",read,write,hit,miss);
        fclose(fl);
    
    }else{
        printf("error\n");
        exit(0);
    }
return 0;
}
