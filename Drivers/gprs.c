#include "gprs.h"
static uint8_t stGprsPost_u8;
enum stGprs{
	    TEST_AT_E=0,
			TERM_HTTP_E,
			SET_COTYPE_E,
			SET_APN_E,
			SET_1_1_E,
			SET_1_2_E,
			HTTP_INIT_E,
			HTTP_PARA_1_E,
			HTTP_PARA_2_E,
			HTTP_PARA_3_E,
			HTTP_DATA_1_E,
			HTTP_DATA_2_E,
			SEND_HTTP_E,
	    READ_STATUS_E,	
    };

void gprs_http_post(void)
{
	
	switch(stGprsPost_u8)
	{
		case TEST_AT_E:
		{
			__delay_ms(20);
			Uart3_Str_Tx("AT\r\n");			//send "AT" command modem will response
			__delay_ms(10);
			stGprsPost_u8 = SET_COTYPE_E;
			break;
		}
		case TERM_HTTP_E:
			{
				Uart3_Str_Tx("AT+HTTPTERM\r\n");
				__delay_ms(100);
				stGprsPost_u8 = SET_COTYPE_E;
			}
		case SET_COTYPE_E:
		{
			Uart3_Str_Tx("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n");	//Select
			__delay_ms(200);
			stGprsPost_u8 = SET_APN_E;
			break;
		}
		case SET_APN_E:
		{
			Uart3_Str_Tx("AT+SAPBR=3,1,\"APN\",\"BSNLNET\"\r\n");	//set 
			__delay_ms(200);
			stGprsPost_u8 = SET_1_1_E;
			break;			
		}
		case SET_1_1_E:
		{
			Uart3_Str_Tx("AT+SAPBR=1,1\r\n");	//set 
			__delay_ms(700);
			stGprsPost_u8 = SET_1_2_E;
			break;			
		}
		case SET_1_2_E:
		{
			Uart3_Str_Tx("AT+SAPBR=2,1\r\n");	//Start 
			__delay_ms(700);
			stGprsPost_u8 = HTTP_INIT_E;
			break;			
		}
		case HTTP_INIT_E:
		{
			Uart3_Str_Tx("AT+HTTPINIT\r");	//IN INITIATE HTTP 
			__delay_ms(200);	
			stGprsPost_u8 = HTTP_PARA_1_E;
			break;			
		}
		case HTTP_PARA_1_E:
		{
			Uart3_Str_Tx("AT+HTTPPARA=\"CID\",1\r\n");	// 
			__delay_ms(300);			
			stGprsPost_u8 = HTTP_PARA_2_E;
			break;			
		}
		case HTTP_PARA_2_E:
		{
			Uart3_Str_Tx("AT+HTTPPARA=\"URL\",\"http://recprojectone.net16.net/httppost1.php?\"\r\n"); // 
	    __delay_ms(200);
			stGprsPost_u8 = HTTP_PARA_3_E;
			break;			
		}
		case HTTP_PARA_3_E:
		{
			Uart3_Str_Tx("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"\r\n");	// 
			__delay_ms(300);	
			stGprsPost_u8 = HTTP_DATA_1_E;
			break;
		}
		case HTTP_DATA_1_E:
		{
			Uart3_Str_Tx("AT+HTTPDATA=101,10000\r\n"); // 
			__delay_ms(10);			
			stGprsPost_u8 = HTTP_DATA_2_E;
			break;			
		}
		case HTTP_DATA_2_E:
		{
			Uart3_Str_Tx("pin=1p2a3s4s5w6o7r8d");//&latitude=0008.19&longitude=00077.38&altitude=0000&timestamp=000000&velocity=0000\r\n");
			Uart3_Str_Tx("&latitude=");
			send_string(&latitude_u8[0],7u);
			Uart3_Str_Tx("&longitude=");
			send_string(&longitude_u8[0],8u);
			Uart3_Str_Tx("&altitude=");
			send_string(&altitude_u8[0],4u);
			Uart3_Str_Tx("&timestamp=");
			send_string(&tiStamp_u8[0],6u);
			Uart3_Str_Tx("&velocity=");
			send_string(&vVelocity_u8[0],4u);
			Uart3_Str_Tx("\r\n");
			//__delay_ms(10);
			payload_sent = 1;
			stGprsPost_u8 = SEND_HTTP_E;
			break;			
		}
		default:
		{

		}			
	}
}
void gprs_http_post_end(void)
{
	switch(stGprsPost_u8)
	{
		case SEND_HTTP_E:
		{
			Uart3_Str_Tx("AT+HTTPACTION=1\r\n");	//
			__delay_ms(200);			
			stGprsPost_u8 = READ_STATUS_E;
			break;			
		}
		case READ_STATUS_E:
		{
			Uart3_Str_Tx("AT+HTTPREAD\r\n"); // 
			__delay_ms(200);
			stGprsPost_u8 = TEST_AT_E;
			payload_sent = 0;
			break;
		}
		default:
		{

		}	
	}		
}



