
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv){

	int num=0;
	int i,k;
	for( i=1;i<argc;i++){
		num=strlen(argv[i]);
		for(k = 0;k < num;k++){
			if(argv[i][k]=='a' || argv[i][k]=='A' || argv[i][k]=='e' || argv[i][k]=='E' || argv[i][k]=='i' || argv[i][k]=='I' || argv[i][k]=='o' || argv[i][k]=='O' || argv[i][k]=='u' || argv[i][k]=='U'){
				printf("%c", argv[i][k]);
			}
		}
	}
	printf("\n");
	return 0;
}