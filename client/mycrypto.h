#ifndef __CRYPTO_H____
#define __CRYPTO_H____
#include <stddef.h>
#include <stdint.h>
//加密函数

int encrypto_data(void *dst, void *src, size_t inlen, size_t outmax, uint16_t insession_id, uint64_t insn);
int decrypto_data(void *dst, void *src, size_t len);
#endif
