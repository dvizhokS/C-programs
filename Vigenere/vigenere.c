#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_TEXT 1024

int shift(char c);

int main(int argc, char** argv){
	
	int len_key;
	int key;
	char* keyword;
	char plaintext[LEN_TEXT];
	char ciphertext[LEN_TEXT];
	int i,j,n;
	
	if(argc != 2){
		printf("Sorry! not have 2 arguments!\n");
		return 1;
	}else{
		len_key = strlen(argv[1]);

		for(int i = 0; i < len_key; i++){
			if( (argv[1][i] < 'a' || argv[1][i] > 'z') && (argv[1][i] < 'A' || argv[1][i] > 'Z')){
				printf("Second argument not word!\n");
				return 2;
			}
		}
	}
	
	keyword =(char*) malloc( (len_key + 1) * sizeof(char) );
	keyword = argv[1];
	int keys[len_key];

	for(int i = 0; i < len_key; i++){
		keys[i] = shift(keyword[i]);
		printf("%i\n", keys[i]);
	}

	printf("plaintext: ");
	gets(plaintext);
	printf("ciphertext: ");
	
	for(i = 0, j = 0, n = strlen(plaintext); i < n; i++){
		if(j >= len_key){
			j = 0;
		}

		if(plaintext[i] >= 'a' && plaintext[i] <= 'z'){
			ciphertext[i] = (plaintext[i] - 'a' + keys[j++]) % 26 + 'a';
		}else if(plaintext[i] >= 'A' && plaintext[i] <= 'Z'){
			ciphertext[i] = (plaintext[i] - 'A' + keys[j++]) % 26 + 'A';
		}else{
			ciphertext[i] = plaintext[i];
		}
	}
	ciphertext[i] = '\0';
	
	printf("%s\n", ciphertext);
	
}


int shift(char c){
	if(c >= 'a' && c <= 'z'){
		return c -'a';
	}else if(c >= 'A' && c <= 'Z'){
		return c -'A';
	}else{
		return -1;
	}
}
