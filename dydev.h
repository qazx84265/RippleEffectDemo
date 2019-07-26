//
//  
//
//
//  Created by  on 2018/3/23.
//

#ifndef dydev_h
#define dydev_h

#include <stdint.h>

int reCalcBodyLen(int len);
uint32_t swapInt32(uint32_t ii);

//设备注册post body加密算法
int a2ed53e51905bdc07e5ea7ddbdb307d8(const char* bodyBytes, int bodyLen, char **buf, int& el);
int decryBody(char* e, int el, const char* k, int kl, char *&o, int& ol);

#endif /* dy_dev_reg_body_h */
