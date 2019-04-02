#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_TEXT 1024


int main(int argc, char** argv){
	int key;
	char plaintext[LEN_TEXT];
	char ciphertext[LEN_TEXT];
	int i,n;
	
	if(argc != 2){
		printf("Sorry! not have 2 arguments!\n");
		return 1;
	}else{
		for(int i = 0, n = strlen(argv[1]); i < n; i++){
			if(argv[1][i] < '0' || argv[1][i] > '9'){
				printf("Second argument not number!\n");
				return 2;
			}
		}
		key = atoi(argv[1]);
	}
		
	printf("plaintext: ");
	gets(plaintext);
	printf("ciphertext: ");
	
	
	
	for(i = 0, n = strlen(plaintext); i < n; i++){
		if(plaintext[i] >= 'a' && plaintext[i] <= 'z'){
			ciphertext[i] = (plaintext[i] - 'a' + key) % 26 + 'a';
		}else if(plaintext[i] >= 'A' && plaintext[i] <= 'Z'){
			ciphertext[i] = (plaintext[i] - 'A' + key) % 26 + 'A';
		}else{
			ciphertext[i] = plaintext[i];
		}
	}
	ciphertext[i] = '\0';
	
	printf("%s\n", ciphertext);
	
}
