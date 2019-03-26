#include <stdlib.h>
#include <stdio.h>

int isPalindrome(unsigned short x){
	unsigned short left = 32768;
	unsigned short right = 1;
	int l, r;
	while(left > right){
		l = left&x;
		r = right&x;
		if((l == 0||r == 0)&&(l != r)){
			return 0;
		}
		left >>= 1;
		right <<= 1;
	}
	return 1;
}

int main(int argc, char** argv){
	unsigned short x = atoi(argv[1]);
	if(isPalindrome(x)==1){
		printf("Is-Palindrome\n");
	}else{
		printf("Not-Palindrome\n");
	}
}