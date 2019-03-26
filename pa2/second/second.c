#include <stdlib.h>
#include <stdio.h>

unsigned short parity(unsigned short n) { 
	unsigned short count = 0; 
	while (n){ 
	    count += n & 1; 
	    n >>= 1; 
  	} 
  	return count; 
} 
int pair(unsigned short n){
	int count = 0;
	while(n){
		if(n & 1){
			n >>= 1; 
			if(n & 1){
				count++;
			}
		}
		n >>= 1; 
	}
	return count;
}

int main(int argc, char** argv){
	unsigned short x = atoi(argv[1]);
	unsigned short par = parity(x);
	if(par%2 == 0){
		printf("Even-Parity\t");
	}else{
		printf("Odd-Parity\t");
	}
	int pai = pair(x);
	printf("%d\n", pai);
}