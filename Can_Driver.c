#include<lpc21xx.h>
#include"header.h"
extern u32 RECEIVER_FLAG;  
extern CAN2_ST M1;
void can2_init(void)
{
  	PINSEL1|=0X00014000; 
	VPBDIV=1;
	C2MOD=0X1;
	AFMR=0X2;
	C2BTR=0X001C001D;
	C2MOD=0;
}
void CAN2_RX_HANDLER(void)__irq
{
	RECEIVER_FLAG=1;
	M1.ID=C2RID;    //receciver ideftifer
	M1.DLC=((C2RFS>>16)&0XF);  //receive frame for data length of code
	M1.RTR=((C2RFS>>30)&1);	   // rtr bit is zero
	if(M1.RTR==0)
	{
		M1.BYTEA=C2RDA;		  //higer 4 byte
		M1.BYTEB=C2RDB;		  // lower 4 byte
	}
	C2CMR=(1<<2);		 	  // free rx buffer
	VICVectAddr=0;
}
void EN_CAN2_INTERRUPT(void)
{
	C2IER=0X01;		  // enable the rx interrupt
	VICIntSelect=0;
	VICVectAddr0=(u32)CAN2_RX_HANDLER;
	VICVectCntl0=27|(1<<5);
	VICIntEnable=(1<<27);
}

