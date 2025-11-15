//author: Alexandria Jones

#ifndef KSTREAM_H
#define KSTREAM_H
#include <stddef.h>
#include <tdio.h>

typedef struct KStream_s* Kstream;

KStream ks_create(FILE* key_fp);

void ks_destroy(KStream ks);

void ks_translate(KStream ks, const unsigned char* in, unsigned char* out, size_t len);

#endif  
