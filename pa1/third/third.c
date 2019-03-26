#include <stdio.h>
#include <stdlib.h>

typedef struct node{
  int data;
  struct node* next;
}node;

typedef struct hashtable{
  int size;
  struct node** bucket;
}hashtable;

hashtable* newtable(int size){
  struct hashtable *table = (struct hashtable*) malloc(sizeof(struct hashtable));
  table->size = size;
	table->bucket = malloc(size*sizeof(struct node*));
	int i;
	for (i = 0; i < size; i++) {
  	table->bucket[i] = NULL;
  }
  return table;
}

int search(struct hashtable* table,int num){
  int key;
  if(num<0){
    key=(num*-1)%table->size;
  }else{
    key=num%table->size;
  }
  if(table->bucket[key]==NULL){
    return 0;
  }
  if(table->bucket[key]->data==num){
    return 1;//found
  }
  struct node* point=table->bucket[key];

  while(point->next!=NULL){
    if(point->next->data==num){
      return 1;//found
    }
    point=point->next;
  }

  return 0;

}

int insert(struct hashtable* table,struct node* new){
  int data=new->data;
  int key;
  if(data<0){
    key=(data*-1)%table->size;
  }else{
    key=data%table->size;
  }

  struct node* point;

  if(table->bucket[key]==NULL){
    table->bucket[key]=new;
    return 1;
  }

  if(table->bucket[key]->data==data){
  return 0;
  }
  point=table->bucket[key];
  while(point->next!=NULL){
    if(point->next->data==data){
      return 0;
    }
  point=point->next;
  }

  point->next=new;
  return 0;


}


node* newnode(int data,struct node* head){

  node* temp=(node*)malloc(sizeof(node));
  temp->data=data;
  temp->next=head;
  head=temp;
  return head;
}

int main(int argc, char**argv){

  struct hashtable* table=newtable(10000);
  FILE* fptr;

  fptr=fopen(argv[1],"r");
  if(fptr==NULL){
    printf("error\n");
    return 0;
  }
  int sucsearch = 0;
  int collision = 0;
  int num;
  char op;
  int boolean1;
  int boolean2;
  struct node* temp=NULL;

  while(fscanf(fptr,"%c\t%d\n",&op,&num)!=EOF){
    if(op=='i'){
      temp=NULL;
      temp=newnode(num,temp);
      boolean1=insert(table,temp);
      if(boolean1==0){
        collision++;
      }
    }
    if(op=='s'){
      boolean2=search(table,num);

      if(boolean2==1){
        sucsearch++;
      }
    }
  }
  //(1) num of collision
  printf("%d\n", collision);
  //(2) successful search
  printf("%d\n", sucsearch);

  return 0;

  }