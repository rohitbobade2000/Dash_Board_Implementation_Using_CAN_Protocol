#include"header.h"
void uart0_init(u32 baud)
{
u32 a[]={15,60,30,15,15};
u32 pclk,result;
PINSEL0=0x5;
pclk=a[VPBDIV]*1000000;
result=pclk/(16*baud);
U0LCR=0x83;
U0DLL=result&0xff;
U0DLM=(result>>8)&0xff;
U0LCR=0x03;
}
#define RDR (U0LSR&1)
u8 uart0_rx()
{
while(RDR==0);
return U0RBR;
}
#define THRE ((U0LSR>>5)&1)
void uart0_tx(u8 data)
{
U0THR=data;
while(THRE==0);
}
void uart0_tx_string(char *p)
{
while(*p)
{
uart0_tx(*p);
p++;
}
}
//void uart0_int(float no)
//{	 
//char s[10];
//sprintf(s,"%0.3f",no);
//uart0_tx_string(s);

void uart0_integer(u32 num)
{
int n1,rev,n2,j=0,m=0;
char a[50],ch;

if(num==0)
uart0_tx('0');
if(num<0)
{
n1=-num;
uart0_tx('-');
}
else
n1=num;

for(n1,rev=0; n1; n1=n1/10)
{
	m=n1%10;
	rev=rev*10+m;
}	
	for(n2=rev,j=0; n2;j++,n2=n2/10)
		{
		ch=((n2%10)+48);
		a[j]=ch;
	    }
	a[j]='\0';
	uart0_tx_string(a);
//	lcd_string(a);
}
void uart0_float(float f)
{
	int i,n1,j,k;
	char p[30],t;
//	if(f<0)
//	{
//	  f1=-f;
//	  lcd_data('-');
//	}
//	else
      n1=f;
	  i=f*100;
	for(j=0;j<2;j++,i=i/10)
	{
	   p[j]=(i%10)+48;
	}
	   p[j]='.';
	   j++;
	for(;n1;n1=n1/10,j++)
	{
	   
	   p[j]=(n1%10)+48;
	}
	p[j]='\0';
	j--;
    for(k=0;k<j;k++,j--)
	{
	  t=p[k];
	  p[k]=p[j];
	  p[j]=t;
	}
	//lcd_data(p);
	uart0_tx_string(p);
}

