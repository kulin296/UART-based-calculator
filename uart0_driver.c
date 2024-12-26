#include<LPC21XX.H>
#include"header.h"
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)
#define sw3 ((IOPIN0>>17)&1)
//extern int flag;
void uart0_init(unsigned int baud)
{
	int a[]={15,60,30,50,50};
	unsigned int pclk,result=0;
	pclk=a[VPBDIV]*1000000;
	result=pclk/(16*baud);
	PINSEL0 |= 0x5;
	U0LCR=0x83;
	U0DLL=result & 0xff;
	U0DLM=(result>>8) & 0xff;
	U0LCR=0x03;
}

void uart0_tx(unsigned char data)
{
	U0THR=data;
	while(THRE==0);
	
}

void uart0_tx_string(char *ptr)
{
	while(*ptr)
	{
		U0THR=*ptr;
		while(THRE==0);
		ptr++;
	}
}

void uart0_tx_integer(int n)
{
	int a[16],i;
	if(n==0)
		uart0_tx('0');
	if(n<0)
	{
		uart0_tx('-');
		n=-n;
	}
	i=0;
	while(n)
	{
		a[i]=n%10;
		n/=10;
		i++;
	}
	for(i=i-1;i>=0;i--)
		uart0_tx(a[i]+48);
}	

unsigned char uart0_rx(void)
{
	while(RDR==0);
//	{
//		if(sw3==0)
//		{
//			while(sw3==0)
//				flag=1;
//			break;
//		}
//	}
	return U0RBR; 
}
