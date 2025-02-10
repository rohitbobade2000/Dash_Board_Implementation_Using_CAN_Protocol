#include<lpc21xx.h>
#include"header.h"
extern int FLAG_HEADLIGHT;
extern int FLAG_INDICATOR_RIGHT;
extern int FLAG_INDICATOR_LEFT;

void ext_init(void)
{
 	PINSEL0|=0xA0000000;	 // pin 14,15
	PINSEL1|=0X00000001;     // pin 16;
	EXTMODE=0x7;			  // 3 pin for the aged 
	EXTPOLAR=0x0;			  // active low
}
void EXT0_handler(void)__irq
{
	FLAG_INDICATOR_RIGHT=1;
	EXTINT=0x01;
	VICVectAddr=0;	
}
void EXT1_handler(void)__irq
{
	FLAG_INDICATOR_LEFT=1;
	EXTINT=0x02;
	VICVectAddr=0;
		
}
void EXT2_handler(void)__irq
{
	FLAG_HEADLIGHT=1;
	EXTINT=0x04;
	VICVectAddr=0;			
}
void interrupt_confg(void)
{
		VICIntSelect=0;
	    VICVectAddr0=(u32)EXT0_handler;
		VICVectCntl0=14|(1<<5);
	    VICVectAddr1=(u32)EXT1_handler;
		VICVectCntl1=15|(1<<5);
	    VICVectAddr2=(u32)EXT2_handler;
		VICVectCntl2=16|(1<<5);	
      	VICIntEnable=(1<<14)|(1<<15)|(1<<16);
}

