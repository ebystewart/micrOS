#ifndef __LM016_LCD_H
#define __LM016_LCD_H


void lCD_Init(void);
void lCD_DeInit(void);
void lcd_data(int a);
void lcd_command(int a);
void lcd_display(char arr[]);
void __delay_ms(long int tmpVal);







#endif

