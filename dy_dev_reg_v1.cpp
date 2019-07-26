﻿//
//  dy_dev_reg_body.hpp.cpp
//  
//
//  Created by  on 2018/3/23.
//

#include "dy_dev_reg_v1.h"
#include "idadef.h"
#include "tool.h"


#include <string.h>
#include <random>
#include <iostream>
#include <time.h>



unsigned char sBox[] ={
    0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76,
    0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0,
    0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15,
    0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75,
    0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84,
    0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf,
    0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8,
    0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2,
    0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73,
    0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb,
    0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79,
    0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08,
    0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbd,0x8b,0x8a,
    0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e,
    0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf,
    0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16
};
unsigned char invsBox[256] = {
    0x52,0x09,0x6a,0xd5,0x30,0x36,0xa5,0x38,0xbf,0x40,0xa3,0x9e,0x81,0xf3,0xd7,0xfb,
    0x7c,0xe3,0x39,0x82,0x9b,0x2f,0xff,0x87,0x34,0x8e,0x43,0x44,0xc4,0xde,0xe9,0xcb,
    0x54,0x7b,0x94,0x32,0xa6,0xc2,0x23,0x3d,0xee,0x4c,0x95,0x0b,0x42,0xfa,0xc3,0x4e,
    0x08,0x2e,0xa1,0x66,0x28,0xd9,0x24,0xb2,0x76,0x5b,0xa2,0x49,0x6d,0x8b,0xd1,0x25,
    0x72,0xf8,0xf6,0x64,0x86,0x68,0x98,0x16,0xd4,0xa4,0x5c,0xcc,0x5d,0x65,0xb6,0x92,
    0x6c,0x70,0x48,0x50,0xfd,0xed,0xb9,0xda,0x5e,0x15,0x46,0x57,0xa7,0x8d,0x9d,0x84,
    0x90,0xd8,0xab,0x00,0x8c,0xbc,0xd3,0x0a,0xf7,0xe4,0x58,0x05,0xb8,0xb3,0x45,0x06,
    0xd0,0x2c,0x1e,0x8f,0xca,0x3f,0x0f,0x02,0xc1,0xaf,0xbd,0x03,0x01,0x13,0x8a,0x6b,
    0x3a,0x91,0x11,0x41,0x4f,0x67,0xdc,0xea,0x97,0xf2,0xcf,0xce,0xf0,0xb4,0xe6,0x73,
    0x96,0xac,0x74,0x22,0xe7,0xad,0x35,0x85,0xe2,0xf9,0x37,0xe8,0x1c,0x75,0xdf,0x6e,
    0x47,0xf1,0x1a,0x71,0x1d,0x29,0xc5,0x89,0x6f,0xb7,0x62,0x0e,0xaa,0x18,0xbe,0x1b,
    0xfc,0x56,0x3e,0x4b,0xc6,0xd2,0x79,0x20,0x9a,0xdb,0xc0,0xfe,0x78,0xcd,0x5a,0xf4,
    0x1f,0xdd,0xa8,0x33,0x88,0x07,0xc7,0x31,0xb1,0x12,0x10,0x59,0x27,0x80,0xec,0x5f,
    0x60,0x51,0x7f,0xa9,0x19,0xb5,0x4a,0x0d,0x2d,0xe5,0x7a,0x9f,0x93,0xc9,0x9c,0xef,
    0xa0,0xe0,0x3b,0x4d,0xae,0x2a,0xf5,0xb0,0xc8,0xeb,0xbb,0x3c,0x83,0x53,0x99,0x61,
    0x17,0x2b,0x04,0x7e,0xba,0x77,0xd6,0x26,0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d
};



int reCalcBodyLen(int len)
{
    int v1 = len + 15;
    if (len >= 0) {
        v1 = len;
    }
    int v2 = len - (v1 & 0xFFFFFFF0); 
    int v3 = 16 - v2; 
    int v4 = 31 - v2;
    if (v3 >= 0) {
        v4 = v3;
    }
    return len + v3 - (v4 & 0xFFFFFFF0) + 4;
}

int indexOfsbox(uint8_t ch)
{
	int idx = -1;
	for (int i=0; i<256; i++) {
		if (sBox[i] == ch) {
			idx = i;
			break;
		}
	}

	return idx;
}

uint32_t swapInt32(uint32_t ii)
{
    return (((ii & 0xFF) << 24) | ((ii & 0xFF00) << 8)
    | ((ii & 0xFF0000) >> 8) | ((ii & 0xFF000000) >> 24));
}


int pBuf(const char* keyBytes, int keyLen, char* & buf)
{
	//VMP_MARKER_BEGIN;

    int result = 0;
    
    int v5 = keyLen >= 16 ? 16 : keyLen;
    
    memcpy(buf, keyBytes, keyLen);
    
    if (keyLen <= 15) {
        int v7 = v5 + 1 - 2;
        while (v7++ < 15) {
            *((char*)buf + v7 + 1) = invsBox[*(buf+v7)];
        }
    }
    
    int v8 = 0;
    while (v8 != 16) {
        *(buf + v8) = sBox[*(buf + v8)];
        v8 += 1;
    }
    
    uint32_t* vv = (uint32_t*)buf;
    *vv = swapInt32(*vv);
    vv[1] = swapInt32(*(vv + 1));
    vv[2] = swapInt32(*(vv + 2));
    vv[3] = swapInt32(*(vv + 3));
    
	//VMP_MARKER_END;

    return result;
}

int b0248093943bba54213b58c6ad4bda36(const char* bodyBytes, int bodyLen, const char* keyBytes, int keyLen, char *buf)
{
	//VMP_MARKER_BEGIN;

	if (NULL == bodyBytes || 0 == bodyLen || NULL == keyBytes || 0 == keyLen)
	{
		return -1;
	}
	
	char *b = (char*)malloc(keyLen);
	pBuf(keyBytes, keyLen, b);

	int v11 = -bodyLen & 0xF; 
	int v12 = bodyLen + v11 + 4;
	char* v13 = buf + 4;
	memmove(v13, bodyBytes, bodyLen);
	*(int16_t*)buf = 25460;
	*(buf + 2) = 2;
	*(buf + 3) = v11;

	if (v12 >= 5) {
		int v14 = v12 - 4;
		while (v14--) {
			*v13 = sBox[*(uint8_t*)v13];
			++v13;
		}
	}

	int v100 = v11 + bodyLen;
	if (v100 >= 16) {

		int v15 = v100 >> 4;
		uint32_t v16 = *(uint32_t*)b;
		uint32_t v17 = *((uint32_t*)b + 1);
		uint32_t v18 = *((uint32_t*)b + 2);
		uint32_t v19 = *((uint32_t*)b + 3);
		uint32_t* v20 = (uint32_t*)(buf + 16);

		while (v15--) {
			uint32_t v21 = *(v20 - 2);
			*(v20 - 3) = swapInt32(swapInt32(*(v20 - 3)) ^ v16);
			*(v20 - 2) = swapInt32(v17 ^ __ROR4__(swapInt32(v21), 24));
			*(v20 - 1) = swapInt32(v18 ^ __ROR4__(swapInt32(*(v20 - 1)), 16));
			*v20 = swapInt32(v19 ^ __ROR4__(swapInt32(*v20), 8));
			v20 += 4;
		}
	}

	free(b);
    
	//VMP_MARKER_END;

    return 0;
}


int decryBody(char* e, int el, const char* k, int kl, char *&o, int& ol)
{
	if (NULL == e || 0 == el || NULL == k || 0 == kl) {
		return -1;
	}

	char *b = (char*)malloc(kl);
	pBuf(k, kl, b);

	int v100 = el - 4;
	if (v100 >= 16) {

		int v15 = v100 >> 4;
		uint32_t v16 = *(uint32_t*)b;
		uint32_t v17 = *((uint32_t*)b + 1);
		uint32_t v18 = *((uint32_t*)b + 2);
		uint32_t v19 = *((uint32_t*)b + 3);
		uint32_t* v20 = (uint32_t*)(e + 16);

		while (v15--) {
			*(v20 - 3) = swapInt32(swapInt32(*(v20 - 3)) ^ v16);
			*(v20 - 2) = swapInt32(__ROL4__(swapInt32(*(v20 - 2)) ^ v17, 24));
			*(v20 - 1) = swapInt32(__ROL4__(swapInt32(*(v20 - 1)) ^ v18, 16));
			*v20 = swapInt32(__ROL4__(swapInt32(*v20) ^ v19, 8));

			v20 += 4;
		}
	}

	if (el >= 5) {
		int v14 = el - 4;
		char* v13 = e + 4;
		while (v14--) {
			*(v13) = indexOfsbox(*v13);
			++v13;
		}
	}

	ol = el - 4 - (int)*(e + 3);
	char* dbuf = (char*)malloc(ol);
	memcpy(dbuf, e+4, ol);
	o = dbuf;

	free(b);

	return 0;
}


#define SECKEY "!*ss!_defaul%t54K&EY"
int a2ed53e51905bdc07e5ea7ddbdb307d8(const char* bodyBytes, int bodyLen, char **buf, int& el)
{
	if (NULL == bodyBytes || 0 == bodyLen)
	{
		return -1;
	}

	//uint32_t clen = 2048;
	//char cmpr[2048] = {'\0'};
	//int res = gzcompress((unsigned char*)bodyBytes, bodyLen, (unsigned char*)cmpr, &clen);
	//if (0 != res || 0 == strlen((const char*)cmpr))
	//{
	//	return res;
	//}

	char key[] = SECKEY;
	int len = reCalcBodyLen(bodyLen); // len + (-len & 0xF) + 4
	*buf = (char*)malloc(len);
	memset(*buf, '\0', len);
	el = len;
	return b0248093943bba54213b58c6ad4bda36((const char*)bodyBytes, bodyLen, key, sizeof(key) / sizeof(key[0]), *buf);
}

//int dea2ed53e51905bdc07e5ea7ddbdb307d8(const char* en, int enLen, char *&buf, int& el)
//{
//	if (NULL == en || 0 == enLen)
//	{
//		return -1;
//	}
//
//	char key[] = SECKEY;
//	char* d = NULL;
//	int dl = 0;
//	int res = decryBody((char*)en, enLen, key, sizeof(key) / sizeof(key[0]), d, dl);
//	buf = d;
//	el = dl;
//	if (NULL == d || 0 == dl)
//	{
//		return -1;
//	}
//
//	uint32_t dcomLen = 2048;
//	unsigned char *decmpr = (unsigned char *)malloc(dcomLen);
//	memset(decmpr, '\0', dcomLen);
//	gzdecompress((unsigned char*)d, dl, decmpr, &dcomLen);
//
//	buf = (char*)decmpr;
//	el = dcomLen;
//
//	return res;
//
//}