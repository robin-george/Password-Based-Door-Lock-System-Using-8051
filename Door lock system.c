#include<reg51.h>
#include<string.h>

sbit C1=P1^0;
sbit C2=P1^1;
sbit C3=P1^2;
sbit C4=P1^3;
sbit R1=P2^0;
sbit R2=P2^1;
sbit R3=P2^2;
sbit R4=P2^3;
sbit rs=P0^0;
sbit rw=P0^1;
sbit en=P0^2;
sbit busy=P3^7;

unsigned char key[40];
unsigned char index;

void intro();
unsigned char rowfinder_1();
unsigned char rowfinder_2();
unsigned char rowfinder_3();
unsigned char rowfinder_4();
void datawrt(unsigned char lcddata);
void cmdwrt(unsigned char cmd);
void lcdready();
void search();

void main()
{
	P0=0x00;
  P1=0xFF;
	P3=0x00;
	TMOD=0x01;
	intro();
	P1=P1 & 0x0F;
	while(1)
	{
		P2=0x00;
		while(P1==0x0F);
		while(P1 != 0x0F)
		{
			if(rowfinder_1());
			else if(rowfinder_2());
			else if(rowfinder_3());
			else
				rowfinder_4();
		}
	}
}

void intro()
{
	unsigned char a[]={0x38,0x0E,0x01,0x80};
	unsigned char b[]="Enter Password : ";
	unsigned char i;
	for(i=0;i<4;i++)
	{
		cmdwrt(a[i]);
	}
	for(i=0;b[i]!='\0';i++)
	{
		datawrt(b[i]);
	}
	cmdwrt(0xC3);
	index=0;
}

unsigned char rowfinder_1()
{
	R1=0,R2=R3=R4=1;
	if (C1==0)
	{
		datawrt('1');
		key[index]='1';
		index++;
		key[index]='\0';
		while(C1==0);
	}
	else if (C2==0)
	{
		datawrt('2');
		key[index]='2';
		index++;
		key[index]='\0';
		while(C2==0);
	}
	else if (C3==0)
	{
		datawrt('3');
		key[index]='3';
		index++;
		key[index]='\0';
		while(C3==0);
	}
	else if (C4==0)
	{
		memset(key,'\0',sizeof(key));
		intro();
		while(C4==0);
	}
	else
		return 0;
	return 1;
}
unsigned char rowfinder_2()
{
	R2=0,R1=R3=R4=1;
	if (C1==0)
	{
		datawrt('4');
		key[index]='4';
		index++;
		key[index]='\0';
		while(C1==0);
	}
	else if (C2==0)
	{
		datawrt('5');
		key[index]='5';
		index++;
		key[index]='\0';
		while(C2==0);
	}
	else if (C3==0)
	{
		datawrt('6');
		key[index]='6';
		index++;
		key[index]='\0';
		while(C3==0);
	}
	else if (C4==0)
	{
		cmdwrt(0x14);
		index++;
		key[index]='\0';
		while(C4==0);
	}
	else
		return 0;
	return 1;
}
unsigned char rowfinder_3()
{
	R3=0,R1=R2=R4=1;
	if (C1==0)
	{
		datawrt('7');
		key[index]='7';
		index++;
		key[index]='\0';
		while(C1==0);
	}
	else if (C2==0)
	{
		datawrt('8');
		key[index]='8';
		index++;
		key[index]='\0';
		while(C2==0);
	}
	else if (C3==0)
	{
		datawrt('9');
		key[index]='9';
		index++;
		key[index]='\0';
		while(C3==0);
	}
	else if (C4==0)
	{
		cmdwrt(0x10);
		index--;
		while(C4==0);
	}
	else
		return 0;
	return 1;
}
unsigned char rowfinder_4()
{
	unsigned char i;
	R4=0,R1=R2=R3=1;
	if (C1==0)
	{
		datawrt('*');
		key[index]='*';
		index++;
		key[index]='\0';
		while(C1==0);
	}
	else if (C2==0)
	{
		datawrt('0');
		key[index]='0';
		index++;
		key[index]='\0';
		while(C2==0);
	}
	else if (C3==0)
	{
		i=index;
		do
		{
			key[index]=key[index+1];
			datawrt(key[index]);
			index++;
		}while(key[index] != '\0');
		index=i;
		i=0xC3+i;
		cmdwrt(i);
		while(C3==0);
	}
	else if (C4==0)
	{
		search();
		while(C4==0);
	}
	else
		return 0;
	return 1;
}
			
void cmdwrt(unsigned char cmd)
{
	lcdready();
	P3=cmd;
	rs=0;
	rw=0;
	en=1;
	TH0=0xFC;
	TL0=0x66;
	TR0=1;
	while(TF0==0);
	TR0=0;
	TF0=0;
	en=0;
}
void datawrt(unsigned char lcddata)
{
	lcdready();
	P3=lcddata;
	rs=1;
	rw=0;
	en=1;
	TH0=0xFC;
	TL0=0x66;
	TR0=1;
	while(TF0==0);
	TR0=0;
	TF0=0;
	en=0;
}
void lcdready()
{
	busy=1;
	rs=0;
	rw=1;
	do
	{
		en=0;
		TH0=0xFC;
		TL0=0x66;
		TR0=1;
		while(TF0==0);
		TR0=0;
		TF0=0;
		en=1;
	}while(busy==1);
}

void search()
{
	unsigned char i;
	unsigned char password[]="0123";
	unsigned char a[]="Verifying...";
	unsigned char b[]="Door Open";
	unsigned char c[]="Door Closed";
	cmdwrt(0x01);
	cmdwrt(0x80);
	for(i=0;a[i]!='\0';i++)
	{
		datawrt(a[i]);
	}
	if (strcmp(key,password)==0)
	{
		cmdwrt(0xC3);
		for(i=0;b[i]!='\0';i++)
		{
			datawrt(b[i]);
		}
	}
	else
	{
		cmdwrt(0xC2);
		for(i=0;c[i]!='\0';i++)
		{
			datawrt(c[i]);
		}
	}
}
