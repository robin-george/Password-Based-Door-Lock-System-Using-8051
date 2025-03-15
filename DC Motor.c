#include<reg52.h>
sbit in1=P1^0;
sbit in2=P1^1;
sbit en1=P1^2;
sbit vcc=P1^3;
void delay(unsigned int ms);
void main()
{
	P1=0x00;
	en1=1;
	vcc=1;
		in1=0;
		in2=1;
		delay(1500);
		in1=1;
		in2=0;
		delay(1500);
}
void delay(unsigned int ms) 
{
	unsigned int i,j;
	for (i=0;i<ms;i++)
	{
		for (j=0;j<1275;j++);
	}
}