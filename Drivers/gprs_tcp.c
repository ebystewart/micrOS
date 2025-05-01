#include "gprs.h"
static uint8_t stGprsPostTcp_u8;
enum stGprsTcp{
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
			READ_STATUS1_E,
      READ_STATUS2_E,
      READ_STATUS3_E,
      READ_STATUS4_E,
      READ_STATUS5_E,
      READ_STATUS6_E,
      READ_STATUS7_E,
      READ_STATUS8_E,
      READ_STATUS9_E,
			READ_STATUS10_E,
      READ_STATUS11_E,
      READ_STATUS12_E,
      READ_STATUS13_E,
      READ_STATUS14_E,			
    };

void gprs_http_post_tcp(void)
{
	
	switch(stGprsPostTcp_u8)
	{
		case TEST_AT_E:
		{
			__delay_ms(20);
			Uart3_Str_Tx("AT\r\n");			//send "AT" command modem will response
			__delay_ms(10);
			stGprsPostTcp_u8 = SET_COTYPE_E;
			break;
		}
		case TERM_HTTP_E:
			{
				Uart3_Str_Tx("AT+CPIN?\r\n");	//Select TCPIP Application mode
				__delay_ms(100);
				stGprsPostTcp_u8 = SET_COTYPE_E;
			}
		case SET_COTYPE_E:
		{
			Uart3_Str_Tx("AT+CGACT?\r\n");	//set csd or GPRS for Connection mode
			__delay_ms(200);
			stGprsPostTcp_u8 = SET_APN_E;
			break;
		}
		case SET_APN_E:
		{
			Uart3_Str_Tx("AT+CGATT=1\r\n");	//set csd or GPRS for Connection mode
			__delay_ms(200);
			stGprsPostTcp_u8 = SET_1_1_E;
			break;			
		}
		case SET_1_1_E:
		{
			Uart3_Str_Tx("AT+CGDCONT=1,\"IP\",\"BSNLNET\"\r\n");	//set csd or GPRS for Connection mode
			__delay_ms(700);
			stGprsPostTcp_u8 = SET_1_2_E;
			break;			
		}
		case SET_1_2_E:
		{
			Uart3_Str_Tx("AT+CIPACK\r\n");	//Send Data Through TCP or UDP Connection
			__delay_ms(700);
			stGprsPostTcp_u8 = HTTP_INIT_E;
			break;			
		}
		case HTTP_INIT_E:
		{
			Uart3_Str_Tx("AT+CIPSHUT\r\n");	//Start Task and set apn
			__delay_ms(200);	
			stGprsPostTcp_u8 = HTTP_PARA_1_E;
			break;			
		}
		case HTTP_PARA_1_E:
		{
			Uart3_Str_Tx("AT+CIPSTATUS\r");	//Bring up wireless connection with GPRS or CSD
			__delay_ms(300);			
			stGprsPostTcp_u8 = HTTP_PARA_2_E;
			break;			
		}
		case HTTP_PARA_2_E:
		{
			Uart3_Str_Tx("AT+CIPMUX=0\r");	// Get Local Ip Address "is assign for GPRS Modem" 
	    __delay_ms(200);
			stGprsPostTcp_u8 = HTTP_PARA_3_E;
			break;			
		}
		case HTTP_PARA_3_E:
		{
			Uart3_Str_Tx("AT+CSTT=\"BSNLNET\"\r\n"); // Start Up TCP or Udp Connection
			__delay_ms(300);	
			stGprsPostTcp_u8 = HTTP_DATA_1_E;
			break;
		}
		case HTTP_DATA_1_E:
		{
			Uart3_Str_Tx("AT+CIICR\r\n");	//Send Data Through TCP or UDP Connection
			__delay_ms(100);			
			stGprsPostTcp_u8 = HTTP_DATA_2_E;
			break;			
		}
		case HTTP_DATA_2_E:
		{
			Uart3_Str_Tx("AT+CIFSR\r\n");	//Send Data Through TCP or UDP Connection
			__delay_ms(100);
			stGprsPostTcp_u8 = SEND_HTTP_E;
			break;			
		}
		case SEND_HTTP_E:
		{
			Uart3_Str_Tx("AT+CDNSCFG=\"8.8.8.8\",\"8.8.4.4\"\r\n");	//dns cONFIGURATION
			__delay_ms(200);			
			stGprsPostTcp_u8 = READ_STATUS_E;
			break;			
		}
		case READ_STATUS_E:
		{
			Uart3_Str_Tx("AT+CDNSGIP=\"recprojectone.net16.net\"\r\n");	//DOMAIN NAME TO IP CONVERSION
			__delay_ms(200);
			stGprsPostTcp_u8 = READ_STATUS1_E;
			break;
		}
		case READ_STATUS1_E:
		{
			Uart3_Str_Tx("AT+CIPSHUT\r\n");	//Send Data Through TCP or UDP Connection
			__delay_ms(100);
			stGprsPostTcp_u8 = READ_STATUS2_E;
			break;			
		}
		case READ_STATUS2_E:
		{
			Uart3_Str_Tx("AT+CIPHEAD=1\r\n");	//Send Data Through TCP or UDP Connection
			__delay_ms(100);
			stGprsPostTcp_u8 = READ_STATUS3_E;
			break;			
		}
		case READ_STATUS3_E:
		{		
			Uart3_Str_Tx("AT+CIPQSEND=1\r\n");	//QUICK DATA SEND
			__delay_ms(200);
			stGprsPostTcp_u8 = READ_STATUS4_E;
			break;			
		}
		case READ_STATUS4_E:
		{		
			Uart3_Str_Tx("AT+CIPSTART=\"TCP\",\"recprojectone.net16.net\",\"80\"\r\n"); // Start Up TCP or Udp Connection
			__delay_ms(200);
			stGprsPostTcp_u8 = READ_STATUS5_E;
			break;			
		}
		case READ_STATUS5_E:
		{		
			Uart3_Str_Tx("AT+CIPSEND\r\n");	//Send Data Through TCP or UDP Connection
			__delay_ms(200);
			stGprsPostTcp_u8 = READ_STATUS6_E;
			break;			
		}
		case READ_STATUS6_E:
		{		
			Uart3_Str_Tx("POST /httppost.php HTTP/1.1\r\n");
			__delay_ms(2);
			Uart3_Str_Tx("User-Agent:curl/7.37.0\r\n");
			__delay_ms(2);
			Uart3_Str_Tx("Host:recprojectone.net16.net\r\n");
			__delay_ms(2);
			Uart3_Str_Tx("Connection:keep-alive\r\n");
			__delay_ms(2);
			Uart3_Str_Tx("Accept:*/*\r\n");
			__delay_ms(2);
			Uart3_Str_Tx("Accept-Language: en-us\r\n");
			__delay_ms(2);
			Uart3_Str_Tx("Content-Length:135\r\n");
			__delay_ms(2);
			Uart3_Str_Tx("Content-Type:application/x-www-form-urlencoded\r\n\n");
			__delay_ms(2);
			Uart3_Str_Tx("pin=p1a2s3s4w5o6r7d8&latitude=22222.222222222&longitude=33333.333333333&altitude=44444.444444444&timestamp=1111.1111&velocity=5555.5555");
			__delay_ms(2);	
			Uart3_Transmit(26);	//transmitting ctrl+z
			__delay_ms(200);			
			stGprsPostTcp_u8 = TEST_AT_E;
			break;			
		}
		default:
		{

		}			
	}
}

