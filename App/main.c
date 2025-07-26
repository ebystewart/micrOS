#include "osKernel.h"
#include "stm32_rtos_bsp.h"

#define QUANTA 10
//Uart_Acc_t Uart2_Acc;
uint32_t count0, count1, count2;
static uint8_t stLcd_u8; 
static uint32_t _tick_proc;
char payload_sent;
enum{
			LCD_INIT = 0,
	    LCD_COMMAND,
			LCD_DATA,
			LCD_DEINIT
    };

void Task0(void);
void Task1(void);
void Task2(void);
void print_on_lcd(void);

int main()
{
	GPIO_PA_Init();
	TIM_Tim2_Init();
	Uart_Init(2);
	Uart_Init(1);
  Uart_Init(3);	
	osKernelInit();
	osKernelAddThreads(&Task0, &Task1, &Task2);
	osKernelLaunch(QUANTA);
}

void Task0(void)
{
	while(1)
	{
		count0++;
		osThreadYield();
	}
}

void Task1(void)
{
		while(1)
	{
		count1++;
		osThreadYield();
	}
}

void Task2(void)
{
		while(1)
	{
		count2++;
		osThreadYield();
	}
}

void TIM2_IRQHandler(void)
{
	_tick_proc++;
if(TIM2->SR & 0x00000001) 	// if UIF flag is set
  {
		TIM2->SR ^= 0x00000001; 	// clear UIF flag
		//Probe_PA5(); 							// toggle LED state
					
		if((_tick_proc%10) == 0u)
		{
       gprs_http_post();
		}
		if(((_tick_proc%60) == 0u) && (payload_sent == 1))
		{
			gprs_http_post_end();
		}
		if((_tick_proc%60) == 0u)
		{	
      USART2->CR1  ^=  (1<<5);    // UART2 Receive Interrupt Disable.			
			process_gps_data(&Uart2_Acc.rxBuffer[0]);
			read_succ_u8 = 1u;
      //USART2->CR1  ^=  (1<<5);    // UART2 Receive Interrupt Disable.				
			USART2->CR1  ^=  (1<<5);    // UART2 Receive Interrupt Enable.
			//USART2->SR ^= (1<<15);
		}				
		else if ((_tick_proc%100) == 0u)
		{
			  //print_on_lcd();		
		}
  }
}
void print_on_lcd(void)
{
	switch(stLcd_u8)
	{
		case LCD_INIT:
		{
			lCD_Init();
			stLcd_u8 = LCD_COMMAND;
			break;
		}
	  case LCD_COMMAND:
		{
			lcd_command(0x0c);
			lcd_command(0x80);
			stLcd_u8 = LCD_DATA;
			break;
		}
		case LCD_DATA:
		{
			lcd_display("Data:");
			stLcd_u8 = LCD_DEINIT;
			break;
		}
		case LCD_DEINIT:
		{
			lCD_DeInit();
			stLcd_u8 = LCD_INIT;
			break;
		}
		default:
		{
			/*Do Nothing*/
		}
	}		
}




