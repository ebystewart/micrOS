#include "gps.h"

uint8_t tiStamp_u8[6]="000000";
uint8_t latitude_u8[7]= "0008.19";
uint8_t longitude_u8[8]= "00077.38";
uint8_t altitude_u8[4]= "0001";
uint8_t vVelocity_u8[4]= "0001";
static 	uint8_t i, stGPS;
enum
	{
		GET_G=0,
		STR1_G,
	};
	

void process_gps_data(uint8_t *data)
{
	switch (stGPS)
	{
		case GET_G:
		{
		  read_succ_u8 = 0u;
			for(int i=0;i<256;i++)
			{
				if(data[i] != 'G')
					{					
						i++;
					}
				else if (data[i] == 'G')
				{
					if (data[i+1u] == 'P')
					{
						if (data[i+2u] == 'G')
						{
							if (data[i+3u] == 'G')
							{
								if (data[i+4u] == 'A')
								{
									for (int j=6; j<13 ; j++)
									{
										tiStamp_u8[j-6] = data[i+j]; 
									}
									for (int j=16; j<24; j++)
									{
										latitude_u8[j-16] = data[i+j]; 
									}
									for (int j=28; j<37 ; j++)
									{
										longitude_u8[j-28] = data[i+j]; 
									}		
									for (int j=53; j<58 ; j++)
									{
										altitude_u8[j-53] = data[i+j]; 
									}	
								}
							}	
						}
						else if (data[i+3u] == 'V')
						{
							if (data[i+4u] == 'T')
							{
								if (data[i+5u] == 'G')
								{
									for (int j=7; j<12 ; j++)
									{
										vVelocity_u8[j-7] = data[i+j]; 
									}
								}					
							}
						}
					}
				}
			}
			read_succ_u8 = 1u;
			stGPS = STR1_G;
			break;
		}
		case STR1_G:
		{					
			stGPS = GET_G;
			break;
		}
		default:
		{
			
		}
	}
}

void send_string(char *value, uint8_t size)
{
	for(int i=0; i<size;i++)
	{
		Uart3_Transmit(value[i]);
	}
}







