#include <stdlib.h>
#include <stdio.h>

struct node{
    int value;
    struct node* next;
};

struct node* head = NULL;
int count = 0;

void insert(int a){
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    struct node *prev = head;
    struct node *curr = head;
    temp->value = a;
    temp->next = head;
    if(head == NULL){
        head = temp;
        return;
    }
    else if (temp->value <= head->value) {
        head = temp;
        return;
    }
    while(curr != NULL){
        if(temp->value <= curr->value){
            prev->next = temp;
            temp->next = curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    prev->next = temp;
    temp->next = NULL;


}

void delete(int a){
    struct node *temp = head;
    struct node *prev = temp;

    if(head == NULL){
        return;
    } 
    if(head->value == a){
        head = head->next;
        count--;
        temp = head;
        prev = temp;
    }
    while (temp != NULL) {
        if(temp->value == a){
            prev->next = temp->next;
            count--;
            break;
        }else{
            prev = temp;
            temp = temp->next;
        }
    }
    free(temp);
}

void print(){
    struct node * temp =  head;
    while(temp != NULL){
		if(temp->next != NULL){
        	while(temp->value == temp->next->value){
				temp = temp->next;
				if(temp->next == NULL){
        			break;
        		}
			}
		}
		printf("%d\t", temp-> value);
        if(temp->next == NULL){
        	break;
        }
		temp = temp->next;
    }
    printf("\n");
    free(temp);
}

int main(int argc, char** argv){
    char* filename = NULL;
    FILE* fptr =NULL;
    char operation;
    int num;
    
    filename = argv[1];
    
    fptr = fopen(filename, "r");
    
    if(fptr == NULL){
        printf("error\n");
    	return 0;
    }
    while(!feof(fptr)){
        fscanf(fptr, "%c %d\n", &operation, &num);        
        if(operation == 'i'){
            insert(num);
            count++;
        }
        else if(operation == 'd'){
            delete(num);
        }
        
    }
    fclose(fptr);
    printf("%d\n", count);
    print();
    
    return 0;
}