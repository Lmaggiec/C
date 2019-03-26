#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned short set(unsigned short x, int n, unsigned short v){
	x = (x & (~(1 << n))) | (v << n);
	return x;
}
unsigned short comp(unsigned short x, int n){
	x = (x ^ (1 << n)); 
	return x;
}
unsigned short get(unsigned short x, int n){
    unsigned short y;
    y = (x >> n) & 1;
	return y;
}
int main(int argc, char** argv){
	FILE *fptr;
    fptr = fopen(argv[1],"r");
    if(fptr == NULL){
        printf("error\n");
    	return 0;
    }
    unsigned short x, num2;
    fscanf(fptr,"%hu\n",&x);
    char operation[10];
    int num1;
    unsigned short r;
    while(!feof(fptr)){
        fscanf(fptr, "%s\t%d\t%hu\n", operation, &num1, &num2);
        if(strcmp("set", operation)==0){
            x = set(x, num1, num2);
            printf("%hu\n",x);
        }
        else if(strcmp("comp", operation)==0){
            x = comp(x, num1);
            printf("%hu\n",x);
        }
        else if(strcmp("get", operation)==0){
            r = get(x, num1);
            printf("%hu\n",r);
        }
    }
    fclose(fptr);
    return 0;
}
