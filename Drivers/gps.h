#ifndef __GPS_H
#define __GPS_H
#include "stm32f10x.h"                  // Device header
#include "lm016_lcd.h"
#include "usart.h"


void process_gps_data(uint8_t*);
void send_string(char *value, uint8_t size);
extern uint8_t read_succ_u8;


#endif



