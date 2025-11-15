//implimentation of key stream cipher
//author: alexandria jones

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "KStream.h"

#define PRIME_BYTES 1024
#define S_SIZE 256

struct KStream_S{
	unsigned char* key;
	size_t keylen;
	unsigned char S[S_SIZE];
	unsigned int i;
	unsigned int j;
};

static unsigned char next_byte(KStream ks){
	ks->i = (ks->i + 1) % S_SIZE;
	ks->j = (ks->j + ks->S[ks->i]) % S_SIZE;
	unsigned char temp = ks->S[ks->i];
	ks->S[ks->i] = ks->S[ks->j];
	ks->S[ks->j] = temp;
	unsigned char B = ks->S[(ks->S[ks->i] + ks->S[ks->j]) % S_SIZE];
	return B;

}

static void init_S(KStream ks){

	for(int i = 0; i < S_SIZE; i++){
		ks->S[i] = (unsigned char)i;
	}

	//key scheduling
	ks->j = 0;
	for(int i = 0; i < S_SIZE; i++){
		ks->j = (ks->j + ks->S[i] + ks->key[i % ks->keylen]) % S_SIZE;
        
        	//swap
		unsigned char temp = ks->S[i];
		ks->S[i] = ks->S[ks->j];
		ks->S[ks->j] = temp;
	}
}

KStream ks_create(FILE* key_fp){
	assert(key_fp != NULL);
	KStream ks = malloc(sizeof(struct KStream_S));
	if(!ks){return NULL;}
        //read the key -8 bytes
	ks->keylen = 8;
	ks->key = malloc(ks->keylen);
	if(!ks->key){
		free(ks);
		return NULL;
	}


	size_t bytes_read = fread(ks->key, 1, ks->keylen, key_fp);
	if (bytes_read != ks->keylen){
		free(ks->key);
		free(ks);
		return NULL;
	}
	//init state
	ks->i = 0;
	ks->j = 0;
	init_S(ks);

// discarding first 1024 bytes
	for(int n = 0; n < PRIME_BYTES; n++){
		next_byte(ks);
	}
	return ks;
}

