#include <REGX52.H>
#include <LCD.h>

#define TRIG P2_0
#define ECHO P2_1

int dem;

long time, trunggian, khoangcach;
void delay(long time)
{
	time = time * 25;
	while(time--);
	
}

void Ngat1() interrupt 0
{	
	dem++;
	if(dem > 1) dem = 0;
}

void main()
{
	LCD_Init();
	
	TMOD = 0X01;
	TH0 = 0X00;
	TL0 = 0X00;
	
	EA = 1;
	EX0 = 1;
	IT0 = 1;
while(1){
	while(dem == 0){
	LCD_Gotoxy(0,0);
	LCD_Puts("Do an mon hoc");
	LCD_Gotoxy(0,1);
	LCD_Puts("The Interupts");
	if(dem != 0) {
	LCD_Clear();
	break;
		}
	}
	while(dem == 1){
		while(1){
		TRIG = 1; delay(10);
		TRIG = 0;
		
		if(ECHO==0)
		{
			TR0 = 0;
			TH0 = TL0 = 0;
			dem++;
			while(ECHO==0)
			{
				if(dem<8) break;
			}
		}
		if(ECHO==1)
		{
			TR0 = 1;
			TH0 = TL0 = 0;
			while(ECHO==1);
			TR0 = 0;
		}

		time = TH0 * 256 + TL0;
		trunggian = time * 1.058;
		khoangcach = trunggian / 58;
		
		if(khoangcach>=3 && khoangcach<=5) khoangcach++;
		if(khoangcach>=24 && khoangcach<=41) khoangcach--;
		if(khoangcach>=42 && khoangcach<=59) khoangcach =  khoangcach - 2;
		if(khoangcach>=60 && khoangcach<=77) khoangcach =  khoangcach - 3;
		
		LCD_Gotoxy(0,0);
		LCD_Puts("The Interrupts");
		LCD_Gotoxy(0,1);
		LCD_Puts("Do dai: ");
		LCD_PutNumber(khoangcach);
		LCD_Puts("CM");
	}
				if(dem != 1){ 
				LCD_Clear();
				break;}
		}
	}
}