#include<stdio.h>
#include<stdlib.h>

typedef struct node{
  int data;
  int level;
  struct node* left;
  struct node* right;
}node;

int insert(node* head,int data){
  int level=1;
  struct node* point=head;
  struct node* prev=NULL;
  if(head->level==0){
    head->left=NULL;
    head->right=NULL;
    head->data=data;
    head->level=1;
    return 1;
  }

  struct node*newnode=(node*)malloc(sizeof(node));
  newnode->left=NULL;
  newnode->right=NULL;
  newnode->data=data;
  newnode->level=0;

  while(point!=NULL){
    if(point->data==newnode->data){
      return 0;
    }
    if(point->data>newnode->data){
      prev=point;
      point=point->left;
      level++;
    }else{
      prev=point;
      point=point->right;
      level++;
    }
  }
  newnode->level=level;
  if(prev->data>newnode->data){
    prev->left=newnode;
    return newnode->level;
  }else{

    prev->right=newnode;

    return newnode->level;
  }

}
void printInorder(struct node* node) { 
  if (node == NULL) {
    return;
  }  
  printInorder(node->left); 
  printf("%d\t", node->data);   
  printInorder(node->right); 
}


int main(int argc,char** argv){
  struct node* head=(node*)malloc(sizeof(node));
  head->level=0;
  FILE * fptr=fopen(argv[1],"r");

  if(fptr==NULL){
    printf("error\n");
    return 0;
  }
  char op;
  int data;
  while(fscanf(fptr,"%c\t%d\n",&op,&data)!=EOF){
    if(op=='i'){
      insert(head,data);
    }else{
      printf("error\n");
      return 0;
    }
  }
  printInorder(head);
  return 0;
}