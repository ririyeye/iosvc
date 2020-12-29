#include "mycrypto.h"
#include <stdint.h>
#include <string.h>
#include <netinet/in.h>
#include "crc16.h"
#include <stdio.h>
typedef struct
{
	uint8_t version; //version for rsa key
	uint8_t type; //0:none, 1:aes, 2:rsa
	uint16_t actual_size;
	uint32_t session_id;
	uint64_t sn;
} CRYPTO_HEADER;

int encrypto_data(void *dst, void *src, size_t inlen, size_t outmax, uint16_t insession_id, uint64_t insn)
{
	if (!dst || !src || !inlen || !outmax) {
		return -1;
	}
	//out buff 太小
	if (outmax < inlen + sizeof(CRYPTO_HEADER)) {
		return -2;
	}

	CRYPTO_HEADER ch;
	ch.version = 'a';
	ch.type = 0xbb;
	ch.actual_size = inlen;
	ch.session_id = insession_id;
	ch.sn = insn;

	memcpy(dst, &ch, sizeof(CRYPTO_HEADER));

	memcpy((char *)dst + sizeof(CRYPTO_HEADER), src, inlen);

	return sizeof(CRYPTO_HEADER) + inlen;
}

int decrypto_data(void *dst, void *src, size_t len)
{
	if (!src || !dst || len < sizeof(CRYPTO_HEADER)) {
		return -1;
	}

	CRYPTO_HEADER *srcptr = (CRYPTO_HEADER *)src;

	if (srcptr->version != 'a' || srcptr->type != 0xbb) {
		return -2;
	}

	uint16_t actual_size = ntohs(srcptr->actual_size);
	printf("actual_size = %d \n", actual_size);
	if (actual_size + sizeof(CRYPTO_HEADER) > len) {
		return -3;
	}

	char *data = (char *)src + sizeof(CRYPTO_HEADER);
	uint16_t crc = crc_16((const char *)data + sizeof(uint16_t), actual_size - sizeof(uint16_t), 1); //crc
	if (ntohs(*(uint16_t *)data) != crc)
		return -4;

	memcpy(dst, data, actual_size);

	return actual_size;
}
