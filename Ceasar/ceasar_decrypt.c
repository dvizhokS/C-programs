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
		
	printf("ciphertext: ");
	gets(ciphertext);
	printf("plaintext: ");
	
	
	
	for(i = 0, n = strlen(ciphertext); i < n; i++){
		if(ciphertext[i] >= 'a' && ciphertext[i] <= 'z'){
			plaintext[i] = (ciphertext[i] - 'a' + 26 - key) % 26 + 'a';
		}else if(ciphertext[i] >= 'A' && ciphertext[i] <= 'Z'){
			plaintext[i] = (ciphertext[i] - 'A' + 26 - key) % 26 + 'A';
		}else{
			plaintext[i] = ciphertext[i];
		}
	}
	plaintext[i] = '\0';
	
	printf("%s\n", plaintext);
	
}
