/*
* author: alexandria jones
*
* encrypts or decrypts files using keystream cipher
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "KStream.h"
#define BUFFER_SIZE 4096

static void print_usage(void){
	fprintf(stderr, "usage: mcrypt key-file in-file [ out-file | - ]\n");
}

static void process_file(KStream ks, FILE* in_fp, FILE * out_fp, int to_stdout){
	unsigned char in_buf[BUFFER_SIZE];
	unsigned char out_buf[BUFFER_SIZE];
	size_t bytes_read;

	while((bytes_read= fread(in_buf, 1, BUFFER_SIZE, in_fp)) > 0){
		ks_translate(ks, in_buf, out_buf, bytes_read);
		if(to_stdout){
			for(size_t i = 0; i < bytes_read; i++){
				if(isascii(out_buf[i])){
					putchar(out_buf[i]);
				}else{ 
					printf("%02x", out_buf[i]);
				}
			}
		}else{
		fwrite(out_buf, 1, bytes_read, out_fp);
		}
	}
}

int main(int argc, char* argv[]){
	if(argc != 4){
		print_usage();
		return EXIT_FAILURE;
	}
	FILE * key_fp = fopen(argv[1],"rb");//open key file
	if(!key_fp){
		fprintf(stderr,"Error: cannot open key file '%s'\n", argv[1]);
		return EXIT_FAILURE;
	
	}
	KStream ks = ks_create(key_fp);
	fclose(key_fp);
	if(!ks){
		fprintf(stderr,"Error: failed to create keystream\n");
		return EXIT_FAILURE;
	}
	FILE* in_fp = fopen(argv[2], "rb");
	if(!in_fp){
		fprintf(stderr, "Error: cannot open input file '%s'\n", argv[2]);
		ks_destroy(ks);
		return EXIT_FAILURE;
	}
	FILE * out_fp = NULL;
	int to_stdout =(strcmp(argv[3], "-") == 0);
	if(!to_stdout){
		out_fp = fopen(argv[3], "wb");
        
	if(!out_fp){
		fprintf(stderr, "Error: cannot open output file '%s'\n", argv[3]);
		fclose(in_fp);

		ks_destroy(ks);
		return EXIT_FAILURE;
		}
	}
	process_file(ks, in_fp, to_stdout ? stdout : out_fp, to_stdout);
	fclose(in_fp);
	if (out_fp){fclose(out_fp);
	}
	ks_destroy(ks);
	return EXIT_SUCCESS;
}
