#include "mycrypto.h"
#include <stdint.h>
#include <string.h>

typedef struct
{
	uint8_t version; //version for rsa key
	uint8_t type; //0:none, 1:aes, 2:rsa
	uint16_t actual_size;
	uint32_t session_id;
	uint64_t sn;
} CRYPTO_HEADER;

int crypto_data(void *dst, void *src, size_t inlen, size_t outmax)
{
	if (!dst || !src || !inlen || !outmax) {
		return -1;
	}
	//out buff 太小
	if (outmax < inlen + sizeof(CRYPTO_HEADER)) {
		return -2;
	}

	CRYPTO_HEADER ch;
	ch.version = 0;
	ch.type = 0;
	ch.actual_size = inlen;
	ch.session_id = 0;
	ch.sn = 1;

	memcpy(dst, &ch, sizeof(CRYPTO_HEADER));

	memcpy((char *)dst + sizeof(CRYPTO_HEADER), src, inlen);

	return sizeof(CRYPTO_HEADER) + inlen;
}
