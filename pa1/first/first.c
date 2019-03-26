#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int size){
    int temp, i, j;
        
    for (i = 0; i < size; i++){
        for (j = 0; j < (size - i - 1); j++){
            if (arr[j] > arr[j + 1]){
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    int tempa[size];
    int left = 0;
    int right = size-1;

    for(i = 0; i < size; i++){
        if(arr[i] % 2 == 0){
            tempa[left] = arr[i];
            left++;
        }else{
            tempa[right] = arr[i];
            right--;
        }
    }

    for(i = 0; i < size; i++){
        arr[i] = tempa[i];
    }
}

int main(int argc, char *argv[]){
    int size;
    int i;

    FILE *fptr;
    fptr = fopen(argv[1],"r");
    if(fptr == NULL){
        printf("Can't find file");
        exit(1);
    }

    fscanf(fptr,"%d",&size);
    if(size <= 0||size > 20){
        printf("Invalid file");
        exit(1);
    }
    int a[size];
    
    for(i = 0; i < size; i++){
        fscanf(fptr,"%d",&a[i]);
    }
    fclose(fptr);
    
    sort(a,size);
    for(i = 0; i < size; i++){
        printf("%d\t", a[i]);
    }
    printf("\n");

    return 0;
}
