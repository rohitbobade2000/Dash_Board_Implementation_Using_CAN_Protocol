#include<lpc21xx.h>
#include"header.h"
#define LED (7<<17)
#define OVER (1<<17)
#define LLED (1<<18)
#define RLED (1<<19)
#define BUZ (1<<21)
CAN2_ST M1;
u32 RECEIVER_FLAG;
main()
{
    
	float temp,result;
	u32 spd;
	lcd_init();
	can2_init();
	EN_CAN2_INTERRUPT();
	lcd_cgram();
	lcd_cmd(0x80);
	lcd_string("SPD:");
	lcd_cmd(0x88);
	lcd_string("TEMP:");
	lcd_cmd(0xC7);
	lcd_data(3);
	IODIR0|=LED;
	IOSET0|=LED;
	IODIR0|=BUZ;
	while(1)
	{
		if(RECEIVER_FLAG)
		{
			RECEIVER_FLAG=0;
		    if(TEMPERATURE_ID==M1.ID)
			{
				lcd_cmd(0x8D);
				temp=(M1.BYTEA*3.3)/1023;
				result=(temp-0.5)/0.01;
				lcd_data(((int)result/100)+48);
				lcd_data((((int)result/10)%10)+48);
				lcd_data(((int)result%10)+48);
			}
			if(SPEED_ID==M1.ID)
			{
				lcd_cmd(0x84);
				spd=(M1.BYTEA*280)/1023;
				lcd_data((spd/100)+48);
				lcd_data(((spd/10)%10)+48);
				lcd_data((spd%10)+48);
				//add
				if(spd>=120)
				{
				  IOCLR0|=OVER;
				  IOSET0|=BUZ;
				}
				else
				{
				   IOSET0|=OVER;
				   IOCLR0|=BUZ;
				}
			}
			if(HEADLIGHT_ID==M1.ID)
			{
				if(HEADLIGHT_ON==M1.BYTEA)
				{ 
					lcd_cmd(0xC8);
				    lcd_data(4);
				}
			  	else if(HEADLIGHT_OFF==M1.BYTEA)
				{
				    lcd_cmd(0xC8);
				    lcd_data(' ');
				}
			}
			if(INDICATOR_ID==M1.ID)
			{
				if(INDICATOR_RIGHT_ON==M1.BYTEA)
				{ 
					lcd_cmd(0xC1);
					lcd_data(' ');
					lcd_data(' ');
					lcd_cmd(0xCD);
				    lcd_data(0);
					lcd_data(1);

					IOCLR0|=RLED;
					IOSET0|=LLED;

				}
			  	else if(INDICATOR_LEFT_ON==M1.BYTEA)
				{
	  				lcd_cmd(0xC1);
				    lcd_data(2);
					lcd_data(0);
					lcd_cmd(0xCD);
					lcd_data(' ');
					lcd_data(' ');

					IOCLR0|=LLED;
					IOSET0|=RLED;
				}
				else if(INDICATOR_RIGHT_OFF==M1.BYTEA)
				{
	  				lcd_cmd(0xCD);
				    lcd_data(' ');
					lcd_data(' ');

					IOSET0|=RLED;
				}
				else if(INDICATOR_LEFT_OFF==M1.BYTEA)
				{
	  				lcd_cmd(0xC1);
				    lcd_data(' ');
					lcd_data(' ');

					IOSET0|=LLED;
				}
			}
	    }			
	}
}


