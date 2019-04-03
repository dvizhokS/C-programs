#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_TEXT 1024


int main(int argc, char** argv){
	int key;
	char plaintext[LEN_TEXT];
	char ciphertext[LEN_TEXT];
	int i,n;

	printf("ciphertext: ");
	gets(ciphertext);
	
	n = strlen(ciphertext);
	
	for(int key = 1; key <= 26; key++){
		for(i = 0; i < n; i++){
			if(ciphertext[i] >= 'a' && ciphertext[i] <= 'z'){
				plaintext[i] = (ciphertext[i] - 'a' + key) % 26 + 'a';
			}else if(ciphertext[i] >= 'A' && ciphertext[i] <= 'Z'){
				plaintext[i] = (ciphertext[i] - 'A' + key) % 26 + 'A';
			}else{
				plaintext[i] = ciphertext[i];
			}
		}
		plaintext[i] = '\0';
		
		printf("key = %i   text = %s\n\n",key, plaintext);	
	}
	
}
