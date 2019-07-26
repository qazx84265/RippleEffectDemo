//
//  dymas.cpp
//  IDADemo
//
//  Created by  on 2018/7/16.
//  Copyright © 2018年 . All rights reserved.
//

#include "dymas.h"
#include "idaDef.h"

#include <stdint.h>
#include <string.h>
#include <iostream>
using namespace std;


#define K_CONS_2827 (2827)
#define k_CONS_B (0xB)
#define k_CONS_55 (0x55)
#define k_CONS_AA (0xAA)
#define k_CONS_33 (0x33)
#define k_CONS_CC (0xCC)
#define k_CONS_F0 (0xF0)
#define k_CONS_F (0xF)

#define k_CONS_13 0xAAAAAAAA
#define k_CONS_14 0x55555555
#define k_CONS_674 0xCCCCCCCC
#define k_CONS_673 0x33333333
#define k_CONS_672 0xF0F0F0F0
#define k_CONS_671 0x0F0F0F0F

#define swapInt32(ii) (((ii & 0xFF) << 24) | ((ii & 0xFF00) << 8) | ((ii & 0xFF0000) >> 8) | ((ii & 0xFF000000) >> 24))

//process12
void df49ace7647d598b747f5a7d658626d7(uint32_t* p_i32, int64_t& res1, int64_t& res2, int64_t& res3)
{
    uint32_t i1 = *p_i32;
    uint32_t i2 = *(p_i32 + 1);
    uint32_t i3 = *(p_i32 + 2);
    
    int64_t f1 = res1;
    int64_t f2 = res2;
    int64_t f3 = res3;
    
    uint32_t factor = K_CONS_2827;
    uint8_t ii = k_CONS_B;
    while (1)
    {
        uint32_t v184 = i1 ^ (factor << 16) ^ (uint32_t)f1;
        uint32_t v185 = i2 ^ (uint32_t)f2;
        uint32_t v186 = i3 ^ factor ^ (uint32_t)f3;
        uint32_t v187 = v184 ^ v185 ^ v186;
        
        uint32_t v189 = __ROR4__(v187, 16) ^ __ROR4__(v187, 24);
        uint32_t v191 = (((__PAIR__(v184, v186) >> 8) & 0xFFFFFFFF) ^ (v185 << 8));
        uint32_t v192 = (((__PAIR__(v186, v185) >> 24) ^ (__PAIR__(v185, v184) >> 8))) & 0xFFFFFFFF;
        res1 = v184 ^ (v184 >> 24) ^ v191 ^ v189;
        res2 = v192 ^ v185 ^ v189;
        res3 = v186 ^ (v191 >> 16) ^ v189 ^ (v192 << 16);
        if ( !ii )
            break;
        
        uint32_t v181 = __ROR4__((uint32_t)res3, 0x1F);
        i1 = __ROR4__(((uint32_t)res2 | ~v181) ^ __ROR4__((uint32_t)res1, 10), 0x1F);
        i2 = (v181 | ~__ROR4__((uint32_t)res1, 10)) ^ (uint32_t)res2;
        uint32_t f = factor << 1;
        if ( f & 0x10000 )
            factor = f ^ 0x11011;
        else
            factor = f;
        
        --ii;
        
        uint32_t v182 = (~(uint32_t)res2 | __ROR4__((uint32_t)res1, 10)) ^ __ROR4__((uint32_t)res3, 31);
        i3 = __ROR4__(v182, 10);
    }
    
    *p_i32 = (uint32_t)res1;
    *(p_i32 + 1) = (uint32_t)res2;
    *(p_i32 + 2) = (uint32_t)res3;
    
    uint32_t v196 = 0;
    uint32_t v197 = (uint32_t)res1;

    while ( 1 )
    {
        char* v198 = (char*)((char*)p_i32 + v196);
        
        uint32_t v199 = (((v197 & 0xFF) << 4) | ((v197 >> 4) & 0xF)) ^ 0xFF;
        *(char*)v198 = v199;
        
        uint32_t v200 = (v196 + 1) > k_CONS_B ? *(char*)p_i32 : *(char*)(v198 + 1);
        uint32_t v201 = ((k_CONS_55 & (v200 ^ v199) & 0x7F) << 1) | ((k_CONS_AA & (v200 ^ v199)) >> 1);
        uint32_t v202 = ((v201 & k_CONS_33 & 0x3F) << 2) | ((v201 & k_CONS_CC) >> 2);
        *(char*)v198 = ((((v202 & k_CONS_F0) >> 4) & 0xF) | ((v202 & k_CONS_F) << 4)) ^ 0xF3;
        if ( v196 == k_CONS_B )
            break;
        v197 = *(char*)(v198 + 1);
        v196 += 1;
    }
}
//rev process12
void df49ace7647d598b747f5d7d658626d7(uint32_t* p_i32, int64_t& res1, int64_t& res2, int64_t& res3)
{
    
    int jj = k_CONS_B;
    char* v198 = (char*)((char*)p_i32);
    while (1) {
        char ch = *(v198 + jj) ^ 0xF3;
        ch = (((k_CONS_55 & ch) & 0x7F) << 1) | ((k_CONS_AA & ch) >> 1);
        char cc = ((ch & k_CONS_33 & 0x3F) << 2) | ((ch & k_CONS_CC) >> 2);
        char ccc = ((((cc & k_CONS_F0) >> 4) & 0xF) | (((cc & k_CONS_F) & 0xFF) << 4));
        *(v198 + jj) = ccc;
        
        char ch1 = *v198;
        if (jj < k_CONS_B) {
            ch1 = *(v198 + jj + 1);
        }
        
        ccc ^= ch1;
        *(v198 + jj) = ccc;
        
        *(v198 + jj) = (((~ccc & 0xFF) << 4) & 0xF0) | ((~ccc & 0xFF) >> 4);
        
        jj -= 1;
        if (jj < 0) {
            break;
        }
    }
    
    uint32_t v11 = res2 & 0xFFFFFFFF;
    uint32_t v12 = res1 & 0xFFFFFFFF;
    uint32_t v670 = res3 & 0xFFFFFFFF;
    
    uint32_t v360 = v11 ^ v12 ^ v670;
    uint32_t v362 = __ROR4__((uint32_t)v360, 16) ^ __ROR4__((uint32_t)v360, 24);
    uint32_t v363 = (((__PAIR__(v12, v670) >> 8) & 0xFFFFFFFF) ^ (v11 << 8));
    uint32_t v364 = (((__PAIR__(v670, v11) >> 24) ^ (__PAIR__(v11, v12) >> 8))) & 0xFFFFFFFF;
    uint32_t v365 = v12 ^ (v12 >> 24) ^ v363 ^ v362;
    uint32_t v366 = v364 ^ v11 ^ v362;
    uint32_t v367 = v670 ^ (v363 >> 16) ^ v362 ^ (v364 << 16);
    
    uint32_t v368 = ((k_CONS_14 & v366) << 1) | ((k_CONS_13 & v366) >> 1);
    uint32_t v369 = ((k_CONS_674 & v368) >> 2) | ((k_CONS_673 & v368) << 2);
    uint32_t v370 = ((k_CONS_672 & v369) >> 4) | ((k_CONS_671 & v369) << 4);
    
    uint32_t v371 = ((k_CONS_14 & v365) << 1) | ((k_CONS_13 & v365) >> 1);
    uint32_t v372 = ((k_CONS_674 & v371) >> 2) | ((k_CONS_673 & v371) << 2);
    uint32_t v373 = ((k_CONS_672 & v372) >> 4) | ((k_CONS_671 & v372) << 4);
    
    uint32_t v374 = ((k_CONS_14 & v367) << 1) | ((k_CONS_13 & v367) >> 1);
    uint32_t v375 = ((k_CONS_674 & v374) >> 2) | ((k_CONS_673 & v374) << 2);
    uint32_t v376 = ((k_CONS_672 & v375) >> 4) | ((k_CONS_671 & v375) << 4);
    
    uint32_t v378 = __ROR4__(((v376 >> 8) & 0xFF00FF) | ((v376 << 8) & 0xFF00FF00), 0x10);
    uint32_t v379 = __ROR4__(((v370 >> 8) & 0xFF00FF) | ((v370 << 8) & 0xFF00FF00), 0x10);
    uint32_t v396 = __ROR4__(((v373 >> 8) & 0xFF00FF) | ((v373 << 8) & 0xFF00FF00), 0x10);
    
    res1 = *p_i32;
    res2 = *(p_i32 + 1);
    res3 = *(p_i32 + 2);
    uint32_t v382 = swapInt32(*p_i32);
    uint32_t v383 = swapInt32(*(p_i32 + 1));
    uint32_t v384 = swapInt32(*(p_i32 + 2));
    
    uint32_t v385 = ((v383 & k_CONS_13) >> 1) | ((v383 & k_CONS_14) << 1);
    uint32_t v386 = ((v385 & k_CONS_674) >> 2) | ((v385 & k_CONS_673) << 2);
    uint32_t v387 = ((v386 & k_CONS_672) >> 4) | ((v386 & k_CONS_671) << 4);
    
    uint32_t v388 = ((v382 & k_CONS_13) >> 1) | ((v382 & k_CONS_14) << 1);
    uint32_t v389 = ((v388 & k_CONS_674) >> 2) | ((v388 & k_CONS_673) << 2);
    uint32_t v390 = ((v389 & k_CONS_672) >> 4) | ((v389 & k_CONS_671) << 4);
    
    uint32_t v391 = ((v384 & k_CONS_13) >> 1) | ((v384 & k_CONS_14) << 1);
    uint32_t v392 = ((v391 & k_CONS_674) >> 2) | ((v391 & k_CONS_673) << 2);
    uint32_t v393 = ((v392 & k_CONS_672) >> 4) | ((v392 & k_CONS_671) << 4);
    
    uint32_t factor = 45489;
    uint32_t ii = k_CONS_B;
    
    
    uint32_t v409 = 0LL;
    uint32_t v410 = 0LL;
    uint32_t v411 = 0LL;
    while (1) {
        uint32_t v401 = v378 ^ (factor << 16) ^ v393;
        uint32_t v402 = v387 ^ v379;
        uint32_t v403 = factor ^ v396 ^ v390;
        uint32_t v404 = v402 ^ v403 ^ v401;
        
        uint32_t v406 = __ROR4__(v404, 16) ^ __ROR4__(v404, 24);
        uint32_t v407 = (((__PAIR__(v401, v403) >> 8) & 0xFFFFFFFF) ^ (v402 << 8));
        uint32_t v408 = (((__PAIR__(v403, v402) >> 24) ^ (__PAIR__(v402, v401) >> 8))) & 0xFFFFFFFF;
        v409 = v401 ^ (v401 >> 24) ^ v407 ^ v406;
        v410 = v408 ^ v402 ^ v406;
        v411 = v403 ^ (v407 >> 16) ^ v406 ^ (v408 << 16);
        if ( !ii )
            break;
        
        uint32_t v181 = __ROR4__((uint32_t)v411, 0x1F);
        v393 = __ROR4__(((uint32_t)v410 | ~v181) ^ __ROR4__((uint32_t)v409, 10), 0x1F);
        v387 = (v181 | ~__ROR4__((uint32_t)v409, 10)) ^ (uint32_t)v410;
        uint32_t f = factor << 1;
        if ( f & 0x10000 )
            factor = f ^ 0x11011;
        else
            factor = f;
        
        --ii;
        
        uint32_t v182 = (~(uint32_t)v410 | __ROR4__((uint32_t)v409, 10)) ^ __ROR4__((uint32_t)v411, 31);
        v390 = __ROR4__(v182, 10);
    }
    uint32_t v412 = ((k_CONS_14 & v410) << 1) | ((k_CONS_13 & v410) >> 1);
    uint32_t v413 = ((k_CONS_14 & v409) << 1) | ((k_CONS_13 & v409) >> 1);
    uint32_t v414 = ((k_CONS_674 & v413) >> 2) | ((k_CONS_673 & v413) << 2);
    uint32_t v415 = ((k_CONS_672 & v414) >> 4) | ((k_CONS_671 & v414) << 4);
    uint32_t v416 = ((k_CONS_14 & v411) << 1) | ((k_CONS_13 & v411) >> 1);
    uint32_t v417 = __ROL4__(((v415 >> 8) & 0xFF00FF) | ((v415 << 8) & 0xFF00FF00), 16);
    
    uint32_t v996 = ((v416 & k_CONS_674) >> 2) | ((v416 & k_CONS_673) << 2);
    uint32_t v997 = ((v996 & k_CONS_672) >> 4) | ((v996 & k_CONS_671) << 4);
    uint32_t v998 = ((0x00ff00ff & (v997 >> 8)) | (0xff00ff00 & (v997 << 8)));
    uint32_t v999 = (v998 << 16) | (v998 >> 16);
    
    uint32_t v1000 = ((v412 & k_CONS_674) >> 2) | ((v412 & k_CONS_673) << 2);
    uint32_t v1001 = ((v1000 & k_CONS_672) >> 4) | ((v1000 & k_CONS_671) << 4);
    uint32_t v1002 = ((0x00ff00ff & (v1001 >> 8)) | (0xff00ff00 & (v1001 << 8)));
    uint32_t v1004 = (v1002 << 16) | (v1002 >> 16);
    
    *(p_i32) = v999;
    *(p_i32 + 1) = v1004;
    *(p_i32 + 2) = v417;
    
}

int32_t processFactor_v1(int32_t factor) {
    int32_t result = factor << 24;
    int8_t i = 8;
    while (i--) {
        if (result >= 0) {
            result = result << 1;
        }
        else {
            result = (result << 1) ^ 0x04c11db7;
        }
    }
    return result;
}


/*
 抖音mas
 第一字节固定为0x00
 */
void cb4da8435e82e69c0271ba133bb9cd8d(const char* as, int asLen, int a3, char* &mas, int &masLen) {
    //    if (!as || !asLen || !mas || !masLen) {
    //        return;
    //    }

    masLen = 0;
    *(int64_t*)mas = 0LL;

    uint32_t ll = asLen + 5;
    char *nMas = (char*)malloc(ll);
    if (!nMas) {
        return;
    }

    //动态调试数据，为了生成相同mas
	int64_t moni_as_addr = (int64_t)as;//0x000000017082fdc0;// 
    //int64_t moni_mas_addr = 0x000000016fd0d088;
    int64_t moni_new_mas_addr = (int64_t)nMas;//0x000000017082cce0;// 

    //
    *(int16_t*)(nMas + 1) = (int16_t)(moni_new_mas_addr & 0xFFFF);
    *(int16_t*)(nMas + 3) = 0x21;
    *(char*)nMas = a3 & 0xFF;

    memcpy((char*)(nMas+5), as, asLen);

    mas = nMas;
    masLen = ll;

    if (a3) {
        free(nMas);
        return;
    }

    uint32_t v18 = asLen + 4;
    if (v18 <= 0) {
        return;
    }

    int64_t res1 = 0LL;
    int64_t res2 = 0LL;
    int64_t res3 = 0LL;

    uint32_t v38 = v18;//26
    uint32_t v40 = v38;
    uint32_t v339 = v18;
    uint32_t v344 = v18;

    uint32_t v19 = 0; //while(1)计数，步长12

    /*
     每组12字节进行处理
     */
    while (1) {

        int32_t v43 = processFactor_v1((int32_t)res1);
        int32_t v45 = processFactor_v1((int32_t)(res1 >> 8));
        int32_t v47 = processFactor_v1((int32_t)(res1 >> 16));
        int32_t v50 = processFactor_v1((int32_t)(res1 >> 24));
        res1 = v43 ^ v45 ^ v47 ^ v50;

        res2 = (((((((uint32_t)res2 & 0xFF) << 4) + ((uint32_t)(res2 >> 8) & 0xFF)) << 4) + ((uint32_t)(res2 >> 16) & 0xFF)) << 4) + ((uint32_t)(res2 >> 24) & 0xFF);


        uint32_t v59 = (uint8_t)res3 + 177573 + BYTE1(res3) + (((uint8_t)res3 + 177573) << 5);
        res3 = v59 + BYTE2(res3) + (v59 << 5) + BYTE3(res3) + ((v59 + BYTE2(res3) + (v59 << 5)) << 5);

        v40 = v38;
        uint32_t v343 = v19 + 0xC;
        if (v343 > v344) {
            break;
        }

        bool isDone = false;
        int64_t v205 = 0LL;

        uint32_t v206 = 0; //dowhile循环计数
        uint32_t v207 = res1 & 0xF;
        if (!v207) {
            v207 = (moni_new_mas_addr + 1) & 0xF;
        }
        if (!v207) {
            v207 = moni_as_addr & 0xF;
        }
        if (!v207) {
            v207 = 4;
        }
        uint32_t v353 = v207; //dowhile循环次数,

        uint32_t* v209 = (uint32_t*)(nMas + 1 + v19);
        int64_t v211 = moni_new_mas_addr + 1;
        int64_t v212 = moni_as_addr;
        double v213 = 1.0;
        int64_t v57 = res1;

        do {

            int64_t v214 = ((v211 >> 13) & (v212 >> 17)) | (v57 >> 9);
            v205 += v214;
            double v215 = v213 * (double)(v205);

            if (v215 > (double)(v205) && !isDone) {
				df49ace7647d598b747f5a7d658626d7(v209, res1, res2, res3);
                
                v205 += v214 << 1;
                isDone = true;
            }

            
            int64_t v245 = (v211 << 15) & (v212 << 19);
            v57 -= (v205 << v57) | v245;
            double v246 = v215 + (double)(v57);
            if ( v246 > (double)(v57) && !isDone )
            {
				df49ace7647d598b747f5a7d658626d7(v209, res1, res2, res3);
                
                v57 = (v57 - ((v205 << v57) | v245)) - ((v205 << (v57 - ((v205 << v57) | v245))) | v245);
                isDone = true;
            }

            int64_t v276 = ((v57 >> 9) & (v212 >> 13)) | (v205 >> 5);
            v211 *= v276;
            double v277 = v246 - (double)(v211);
            if ( v277 > (double)(v211) && !isDone )
            {
				df49ace7647d598b747f5a7d658626d7(v209, res1, res2, res3);
                
                v211 *= v276 * v276;
                isDone = true;
            }

            v212 = v212 | (v205 << 7);
            v212 = v212 | ((v57 << v57) & (v211 << 15));
            if ( v212 && v277 > (double)(v212) )
                v277 = v277 / (double)(v212);

            if (!isDone) {
				df49ace7647d598b747f5a7d658626d7(v209, res1, res2, res3);
            }
            
            v213 = v277 * v277;
            v206 += 1;
            isDone = true;

        } while (v206 < v353);

        v38 = v40 - 12;
        v19 = v343;
        if (v344 <= v343) {
            return;
        }
    }


    uint32_t v61 = (uint32_t)(v339 - v19);
    uint32_t v64 = ~(BYTE)v61;
    uint32_t v65 = v40 - 1;
    char *v62 = (char*)(nMas + 1 + v19);

	uint32_t ii = 0;
    while (ii < v40) {
        char ch = *(v62 + ii);
        ch = (((ch >> 4) & 0xF) | (ch << 4) )^ 0xFF;
        *(v62 + ii) = ch;

        char chh = *v62;
        bool b = true;
        if ((ii + 1) >= v61) {
            if (!ii || v65 != ii) {
                b = false;
            }
            else {
                chh = *v62;
            }
        }
        else {
            chh = *(v62 + ii + 1);
        }

        if (b) {
            ch ^= chh;
            *(v62 + ii) = ch;
        }

        char cc = (((ch  & k_CONS_55) & 0x7F) << 1) | ((ch & k_CONS_AA) >> 1);
        char ccc = (((cc  & k_CONS_33) & 0x3F) << 2) | ((cc & k_CONS_CC) >> 2);
        char cccc = v64 ^ ((((ccc & k_CONS_F0) >> 4) & 0xF) | ((ccc & k_CONS_F) << 4));
        *(v62+ii) = cccc;

        ii += 1;
    }

}

/*xlog ecode*/
void b71bb87dba5d115f9770ab296ae81201(const char* src, int srcLen, char* &pout, int &outLen)
{
	cb4da8435e82e69c0271ba133bb9cd8d(src, srcLen, 0, pout, outLen);
}

/*xlog decode*/
void b72bb87dba5d115f9770ab296ae81201(const char* src, int srcLen, char* &pout, int &outLen)
{
	//    if (!src || !srcLen || !out || !outLen) {
	//        return;
	//    }

	if (1 == srcLen) {
		return;
	}

	char *dest = (char*)malloc(srcLen);
	if (!dest) {
		return;
	}

	memcpy(dest, src, srcLen);
	pout = dest;
	outLen = srcLen;

	if (*src) {
		free(dest);
		return;
	}

	int64_t src_addr = (int64_t)src;//0x00000001701ba780;//
	int64_t out_addr = (int64_t)pout;//0x000000016efe28a8;//
	int64_t dest_addr = (int64_t)dest;//0x00000001701a9920;//


	int64_t dest_addr_1 = dest_addr + 1;
	uint32_t dest_addr_1_f = dest_addr_1 & 0xF;
	uint32_t src_f = src_addr & 0xF;

	uint32_t v21 = outLen & 0xF;
	if (!v21) {
		v21 = srcLen & 0xF;
	}
	if (!v21) {
		v21 = out_addr & 0xF;
	}
	if (!v21) {
		v21 = 4;
	}

	uint32_t v12 = 0;

	int64_t res1 = 0LL;
	int64_t res2 = 0LL;
	int64_t res3 = 0LL;

	uint32_t v27 = 0;
	while (1) {
		int32_t v43 = processFactor_v1((int32_t)res1);
		int32_t v45 = processFactor_v1((int32_t)(res1 >> 8));
		int32_t v47 = processFactor_v1((int32_t)(res1 >> 16));
		int32_t v50 = processFactor_v1((int32_t)(res1 >> 24));
		res1 = v43 ^ v45 ^ v47 ^ v50;

		res2 = (((((((uint32_t)res2 & 0xFF) << 4) + ((uint32_t)(res2 >> 8) & 0xFF)) << 4) + ((uint32_t)(res2 >> 16) & 0xFF)) << 4) + ((uint32_t)(res2 >> 24) & 0xFF);


		uint32_t v59 = (uint8_t)res3 + 177573 + BYTE1(res3) + (((uint8_t)res3 + 177573) << 5);
		res3 = v59 + BYTE2(res3) + (v59 << 5) + BYTE3(res3) + ((v59 + BYTE2(res3) + (v59 << 5)) << 5);

		uint32_t v641 = v27 + 0xC;
		if (v641 > outLen) {
			break;
		}

		uint32_t d_s = 0;
		uint32_t d_c = v12 & 0xF;
		if (!d_c) {
			d_c = dest_addr_1_f;
		}
		if (!d_c) {
			d_c = src_f;
		}
		if (!d_c) {
			d_c = 4;
		}


		bool isDone = false;
		int64_t v165 = 0LL;
		int64_t v168 = res1;
		uint32_t*v169 = (uint32_t*)(dest + 1 + v27);
		int64_t v170 = src_addr;
		int64_t v172 = dest_addr_1;
		double v173 = 1.0;

		do {

			int64_t v174 = ((v172 >> 13) & (v170 >> 17)) | (v168 >> 9);
			v165 += v174;
			double v175 = v173 * (double)(v165);

			if (v175 > (double)(v165) && !isDone) {
				df49ace7647d598b747f5d7d658626d7(v169, res1, res2, res3);

				v165 += v174 << 1;
				isDone = true;
			}

			int64_t v203 = (v172 << 15) & (v170 << 19);
			v168 -= (v165 << v168) | v203;
			double v204 = v175 + (double)(v168);
			if (v204 > (double)(v168) && !isDone) {

				df49ace7647d598b747f5d7d658626d7(v169, res1, res2, res3);

				v168 = (v168 - ((v165 << v168) | v203)) - ((v165 << (v168 - ((v165 << v168) | v203))) | v203);
				isDone = true;
			}

			int64_t v232 = ((v168 >> 9) & (v170 >> 13)) | (v165 >> 5);
			v172 *= v232;
			double v233 = v204 - (double)(v172);
			if (v233 > (double)(v172) && !isDone)
			{
				df49ace7647d598b747f5d7d658626d7(v169, res1, res2, res3);

				v172 *= v232 * v232;
				isDone = true;
			}

			v170 = v170 | (v165 << 7);
			v170 = v170 | ((v168 << v168) & (v172 << 15));
			if (v170 && v233 > (double)(v170)) {
				v233 = v233 / (double)(v170);
			}
			if (!isDone)
			{
				df49ace7647d598b747f5d7d658626d7(v169, res1, res2, res3);
			}
			v173 = v233 * v233;
			d_s += 1;
			isDone = true;

		} while (d_s < d_c);

		v27 = v641;

		if ((srcLen - 1) <= v641) {
			return;
		}
	}


	int ll = srcLen - 1 - v27;
	char *p_last_s = (char*)(dest + v27 + 1);
	char *p_last_e = (char*)(dest + srcLen - 2);

	int v40 = 0;
	while (v40 > -ll) {
		char* p = (char*)(p_last_e + v40);
		char ch = *(p + 1);
		char c = ll ^ 0xFF ^ ch;
		char cc = (((c  & k_CONS_55) & 0x7F) << 1) | ((c & k_CONS_AA) >> 1);
		char ccc = (((cc  & k_CONS_33) & 0x3F) << 2) | ((cc & k_CONS_CC) >> 2);
		char cccc = (((ccc & k_CONS_F0) >> 4) & 0xF) | ((ccc & k_CONS_F) << 4);
		*(p + 1) = cccc;

		char v51 = *p_last_s;
		bool b = false;
		if (v40 || (srcLen - v27) == 2) {
			if ((srcLen - 1 - v27 + v40) >= ll) {
				b = true;
			}
			else {
				v51 = *(p_last_e + v40 + 2);
			}
		}

		if (!b) {
			cccc ^= v51;
			*(p + 1) = cccc;
		}

		*(p + 1) = (((~cccc & 0xFF) << 4) & 0xF0) | ((~cccc & 0xFF) >> 4);


		--v40;
	}
}
