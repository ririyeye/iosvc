#ifndef __crc16_h___
#define __crc16_h___

#ifdef __cplusplus
extern "C" {
#endif
 
unsigned short crc_16(const char *data, unsigned long size, unsigned short crc);
 
#ifdef __cplusplus
}
#endif



#endif