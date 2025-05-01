#ifndef __GPRS_H
#define __GPRS_H
#include "stm32f10x.h"                  // Device header
#include "lm016_lcd.h"
#include "usart.h"
#include "gps.h"

extern char tiStamp_u8[9];
extern char latitude_u8[15];
extern char longitude_u8[15];
extern char altitude_u8[15];
extern char vVelocity_u8[9];
extern char payload_sent;

void gprs_http_post(void);
void gprs_http_post_end(void);
void gprs_http_post_tcp(void);





#endif




