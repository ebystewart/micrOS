#include "lm016_lcd.h"
#include "stm32f10x.h"                  // Device header

void lCD_Init(void)
{
	RCC->APB2ENR |= 0x0000000C; /* Enable clock for PA and PB	*/
  GPIOA->CRL = 0x33333333;    /* DATA PINS -> A0 to A7 */
	GPIOB->CRL = 0x00333000;		/* CONTROL PINS -> B3 to B5	*/	
}	
void lCD_DeInit(void)
{
	RCC->APB2ENR ^= 0x0000000C;
  GPIOA->CRL ^= 0x22222222;    /* DATA PINS -> A0 to A7 */
	GPIOB->CRL ^= 0x00222000;		/* CONTROL PINS -> B3 to B5	*/	
}	
void lcd_data(int a)
{
  GPIOA->ODR = (0x000000ff & a);
  GPIOB->ODR = (1<<3);        	/* PB3-> RS=1 */
  GPIOB->ODR = (0<<4);			   	/* PB4-> RW=0 */
  GPIOB->ODR = (1<<5);					/* PB5-> EN=1 */
  __delay_ms(100);
  GPIOB->ODR = (0<<5);					/* PB5-> EN=0 */
}
void lcd_command(int a)
{
  GPIOA->ODR = (0x000000ff & a);
  GPIOB->ODR = (1<<3);        	/* PB3-> RS=1 */
  GPIOB->ODR = (0<<4);			   	/* PB4-> RW=0 */
  GPIOB->ODR = (1<<5);					/* PB5-> EN=1 */
  __delay_ms(100);
  GPIOB->ODR = (0<<5);					/* PB5-> EN=0 */
}
void lcd_display(char arr[])
{ int i=0;
  while(arr[i]!='\0')
      {
        lcd_data(arr[i]);
        i++;
      }
}

void __delay_ms(long int tmpVal)
{
	long int i=0;
  for (i=0; i<tmpVal; i++)
	{
		/* Do Nothing	*/
	}
}

