#include"lcd.h"
#include "DS1302.h"
#include "lcd1602.h"
sbit K6=P3^6;   //12制的变换
sbit K7=P3^7;   //24制的变换
void DisTemperture();
void DisDate();
void Buttons();
extern unsigned char jz=2;
extern unsigned char clockdata[9];
void Deley10ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
} 
void Distime()
{
/*	clockdata[0] = 0;			//秒
	clockdata[1] = 42;			//分
	clockdata[2] = 10;			//小时
	clockdata[3] = 10;		    //日期
	clockdata[4] = 1;		    //月份
	clockdata[5] = 19;		    //年
	clockdata[6] = 3;			//星期几
	clockdata[7] = 0;
	clockdata[8] = 20; */
	
	
//	LCD1602_Initialize();
//	DS1302_settime();
//	   while(1)
//	   {
		 DS1302_gettime();
			/************************************/
		if(K6==0)		//检测按键K6是否按下		//12进制
			{
				Deley10ms();	//消除抖动
				if(K6==0)
				{
				   jz=1;
				}
			}
		  if(K7==0)		//检测按键K6是否按下		//12进制
			{
				Deley10ms();	//消除抖动
				if(K7==0)
				{
				   jz=2;
				}
			} 
		//小时
		switch( jz )
		{
		case 2:
		LCD1602_PrintChar(1,1,clockdata[2]/10 + '0');
		LCD1602_PrintChar(1,2,clockdata[2]%10 + '0');
		LCD1602_PrintChar(1,9,' ');
		 LCD1602_PrintChar(1,10,' ');
		break;
		case 1:	
		if(clockdata[2]>12)
		{
	 	 LCD1602_PrintChar(1,1,12/clockdata[2] + '0');
		 LCD1602_PrintChar(1,2,clockdata[2]%12 + '0');
		 LCD1602_PrintChar(1,9,'p');
		 LCD1602_PrintChar(1,10,'m');
		}
		else
		{
		 LCD1602_PrintChar(1,1,clockdata[2]/12 + '0');
		 LCD1602_PrintChar(1,2,clockdata[2]%12 + '0');
		 LCD1602_PrintChar(1,9,'a');
		 LCD1602_PrintChar(1,10,'m');
		}
		break;
		}
		
	    LCD1602_PrintChar(1,3,':');
		//分
		LCD1602_PrintChar(1,4,clockdata[1]/10 + '0');
		LCD1602_PrintChar(1,5,clockdata[1]%10 + '0');
		LCD1602_PrintChar(1,6,':');
		//秒
		LCD1602_PrintChar(1,7,clockdata[0]/10 + '0');
		LCD1602_PrintChar(1,8,clockdata[0]%10 + '0');
		LCD1602_PrintChar(1,11,' ');
		LCD1602_PrintChar(1,12,' ');
		LCD1602_PrintChar(1,13,' ');
		
		delay_ms( 500 );
//	}  
}