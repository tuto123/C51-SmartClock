/*******************************************************************************
* 实验效果       :1602显示时钟，按K3进入时钟设置，按K1选择设置的时分秒日月，按K2选择
*选择设置加1。 
*******************************************************************************/
#include"lcd.h"
#include"ds1302.h"
#include "lcd1602.h"
sbit K1=P3^0;	//+
sbit K2=P3^1;	//下一项设置
sbit K3=P3^2;   //时间日期星期设置
sbit K4=P3^3;	//闹钟设置
sbit K5=P3^4;	//-
void Int0Configuration();
void Int1Configuration();
void DisDate();
void DisTime();
void Clocker();
unsigned char SetState,ClockState,SetPlace=0,SetNao=0;
void Delay10ms(void);   //误差 0us
extern unsigned char clockdata[];
unsigned char naozhongdata[]={0,28,10,0};
extern unsigned char jz;
unsigned char evd;
/*******************************************************************************
* 函数名         : main
* 函数功能		   : 主函数
*******************************************************************************/

void Buttons()
{
    
    unsigned char i;
	Int0Configuration();
	Int1Configuration();
/**********************************************************************/	
		while(SetState)
		{
		  DS1302_settime();
		  /***********************************/
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
		  /************************************/
		  	LCD1602_PrintChar(2,7,clockdata[8]/10 + '0');
			LCD1602_PrintChar(2,8,clockdata[8]%10 + '0');
			LCD1602_PrintChar(2,9,clockdata[5]/10 + '0');
			LCD1602_PrintChar(2,10,clockdata[5]%10 + '0');
			LCD1602_PrintChar(2,11,'/');
			//月份
			LCD1602_PrintChar(2,12,clockdata[4]/10 + '0');
			LCD1602_PrintChar(2,13,clockdata[4]%10 + '0');
		    LCD1602_PrintChar(2,14,'/');
			//日期
			LCD1602_PrintChar(2,15,clockdata[3]/10 + '0');
			LCD1602_PrintChar(2,16,clockdata[3]%10 + '0');
	
			switch( clockdata[6] )
			{
				case 1:
					//星期日
					LCD1602_PrintString(1,14,"Sun");
					break;
				case 2:
					//星期一
					LCD1602_PrintString(1,14,"Mon");
					break;
				case 3:
					//星期二
					LCD1602_PrintString(1,14,"The");
					break;
				case 4:
					//星期三
					LCD1602_PrintString(1,14,"Wed");
					break;
				case 5:
					//星期四
					LCD1602_PrintString(1,14,"Thu");
					break;
				case 6:
					//星期五
					LCD1602_PrintString(1,14,"Fri");
					break;
				case 7:
					//星期六
					LCD1602_PrintString(1,14,"Sat");
					break;
				default:
					LCD1602_PrintString(1,14,"Ero");
					break;
			}
		  /************************************/
		  		if(K1==0)		//检测按键K1是否按下	  //+
			{
				Delay10ms();	//消除抖动
				if(K1==0)
				{
					clockdata[SetPlace]++;
					if(SetPlace>=7)
					{
					  SetPlace=0;
					}
					if(clockdata[0]>=60)	  //秒
					{
					   clockdata[0]=0;
					}
					if(clockdata[1]>=60)	  //分
					{
					   clockdata[1]=0;
					}
					if((jz==2)&&(clockdata[2]==24))	  //24时
					{
					   clockdata[2]=0;
					}
					if((jz==1)&&(clockdata[2]>12))	  //12时
					{
					   clockdata[2]=0;
					}
					if(clockdata[3]>=32)	  //日
					{
					   clockdata[3]=1;
					}
					if(clockdata[4]>=13)	  //月
					{
					   clockdata[4]=1;
					}
					if(clockdata[5]>=99)	  //年
					{
					   clockdata[5]=0;
					}
					if(clockdata[6]>=7)		  //星期
					{
					   clockdata[6]=1;
					}					
				}

				while((i<50)&&(K1==0))	 //检测按键是否松开
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
			/****************************************/
			if(K5==0)		//检测按键K5是否按下		//-
			{
				Delay10ms();	//消除抖动
				if(K5==0)
				{
					clockdata[SetPlace]--;
					if(SetPlace>=7)
					{
					 SetPlace=0;
				 	 }
					 if(clockdata[0]<0)	  //秒
					{
					   clockdata[0]=59;
					}
					if(clockdata[1]<0)	  //分
					{
					   clockdata[1]=59;
					}
					if((jz==2)&&(clockdata[2]<0))	  //24时
					{
					   clockdata[2]=23;
					}
					if((jz==1)&&(clockdata[2]<0))	  //12时
					{
					   clockdata[2]=11;
					}
					if(clockdata[3]<0)	  //日
					{
					   clockdata[3]=31;
					}
					if(clockdata[4]<0)	  //月
					{
					   clockdata[4]=12;
					}
					if(clockdata[5]<0)	  //年
					{
					   clockdata[5]=99;
					}
					if(clockdata[6]<0)	  //星期
					{
					   clockdata[6]=7;
					}								
				}

				while((i<50)&&(K5==0))	 //检测按键是否松开
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
			/**************************************************/
		
			/***************************************************/
			if(K2==0)		//检测按键K2是否按下
			{
				Delay10ms();	//消除抖动
				if(K2==0)
				{
					SetPlace++;
					if(SetPlace>=7)
					{
					  SetPlace=0;
					}
				/*	if((clockdata[SetPlace]&0x0f)>9)					 //换成BCD码。
					{
						clockdata[SetPlace]=clockdata[SetPlace]+6;
					}  */
					if((clockdata[SetPlace]>=60)&&(SetPlace<2))		//分秒只能到59
					{
						clockdata[SetPlace]=0;
					}
					if((jz==2)&&(clockdata[SetPlace]>24)&&(SetPlace==2))		//24小时只能到23
					{
						clockdata[SetPlace]=0;
					}
					if((jz==1)&&(clockdata[SetPlace]>=12)&&(SetPlace==2))		//12小时只能到12
					{
						clockdata[SetPlace]=0;
					}   
					if((clockdata[SetPlace]>=32)&&(SetPlace==3))		//日只能到31
					{
						clockdata[SetPlace]=0;	
					}
					if((clockdata[SetPlace]>=13)&&(SetPlace==4))		//月只能到12
					{
						clockdata[SetPlace]=0;
					}
					if((clockdata[SetPlace]>=99)&&(SetPlace==5))		//年只能到99
					{
						clockdata[SetPlace]=1;
					}	
					if((clockdata[SetPlace]>=7)&&(SetPlace==6))		//周只能到7
					{
						clockdata[SetPlace]=1;
					}		
	
				}
				
				while((i<50)&&(K2==0))	 //检测按键是否松开
				{
					Delay10ms();
					i++;
				}
				i=0;
				
			}
								
		}
/***********************************************************/
//闹钟设置
/***********************************************************/
   while(ClockState)
		{
		  /***********************************/
			//时
			LCD1602_PrintChar(1,1,naozhongdata[2]/10 + '0');
			LCD1602_PrintChar(1,2,naozhongdata[2]%10 + '0');
			LCD1602_PrintChar(1,9,' ');
			LCD1602_PrintChar(1,10,' ');
			//分
			LCD1602_PrintChar(1,4,naozhongdata[1]/10 + '0');
			LCD1602_PrintChar(1,5,naozhongdata[1]%10 + '0');
			
			//秒
			LCD1602_PrintChar(1,7,naozhongdata[0]/10 + '0');
			LCD1602_PrintChar(1,8,naozhongdata[0]%10 + '0');
			/****************************************************/
		    if(K1==0)		//检测按键K1是否按下	  //+
			{
				Delay10ms();	//消除抖动
				if(K1==0)
				{
				   naozhongdata[SetNao]++;
					if(naozhongdata[0]>=60)	  //秒
					{
					   naozhongdata[0]=0;
					}
					if(naozhongdata[1]>=60)	  //分
					{
					   naozhongdata[1]=0;
					}
					if((naozhongdata[2]==24))	  //24时
					{
					   clockdata[2]=0;
					}
					if(naozhongdata[3]>1)		  //星期
					{
					   naozhongdata[3]=0;
					}					
				}

				while((i<50)&&(K1==0))	 //检测按键是否松开
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
			/*****************************************************/
			if(K5==0)		//检测按键K5是否按下		//-
			{
				Delay10ms();	//消除抖动
				if(K5==0)
				{
					naozhongdata[SetNao]--;
					 if(naozhongdata[0]<0)	  //秒
					{
					   naozhongdata[0]=0;
					}
					if(naozhongdata[1]<0)	  //分
					{
					   naozhongdata[1]=59;
					}
					if((naozhongdata[2]<0))	  //24时
					{
					   naozhongdata[2]=23;
					}
					if(naozhongdata[3]==0)	  //星期
					{
					   naozhongdata[3]=0;
					}								
				}

				while((i<50)&&(K5==0))	 //检测按键是否松开
				{
					Delay10ms();
					i++;
				}
				i=0;
			}
			/***************************************************/
			if(K2==0)		//检测按键K2是否按下		设置下一项
			{
				Delay10ms();	//消除抖动
				if(K2==0)
				{
					SetNao++;
					if(SetNao>3)
					{
					  SetNao=0;
					}
					if((naozhongdata[SetNao]>=60)&&(SetNao<2))		//分秒只能到59
					{
						naozhongdata[SetNao]=0;
					}
					if((naozhongdata[SetNao]>24)&&(SetNao==2))		//24小时只能到23
					{
						naozhongdata[SetNao]=0;
					}
			 
					if((naozhongdata[SetNao]>1)&&(SetNao==3))		//周只能到7
					{
						naozhongdata[SetNao]=1;
					}		
				}	
				while((i<50)&&(K2==0))	 //检测按键是否松开
				{
					Delay10ms();
					i++;
				}
				i=0;	
			}
			if(naozhongdata[3]==1)
			{
				LCD1602_PrintChar(1,11,'E');
				LCD1602_PrintChar(1,12,'v');
				LCD1602_PrintChar(1,13,'D');
		      }
		  if(naozhongdata[3]==0)
			{
				LCD1602_PrintChar(1,11,' ');
				LCD1602_PrintChar(1,12,' ');
				LCD1602_PrintChar(1,13,' ');
		      } 
		 
	   }
	   if((naozhongdata[0]==clockdata[0])&&(naozhongdata[1]==clockdata[1])
		     &&(naozhongdata[2]==clockdata[2])&&(naozhongdata[3]==1))
		 { 
		 while(1)
		  { 
	 	   Clocker();
		  if(K1==0)
			{
			   Delay10ms();	//消除抖动
			   if(K1==0)
			   { 	
		 	    break;
			   }
			}
	        
		  }
		 }
		

/*****************************************************************/		
}
/*******************************************************************************
* 函数名         : Int0Configuration()
* 函数功能		   : 配置外部中断0
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void Int0Configuration()
{
	//设置INT0
	IT0=1;//跳变沿出发方式（下降沿）
	EX0=1;//打开INT0的中断允许。
	EA=1;//打开总中断	
}

/*******************************************************************************
* 函数名         : Int0() 
* 函数功能		   : 外部中断0 中断函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void Int0() interrupt 0		 
{
	Delay10ms();
	if(K3==0)
	{
		SetState=~SetState;
		SetPlace=0;	
	}
}
/*******************************************************************************
* 函数名         : Int1Configuration()
* 函数功能		   : 配置外部中断0
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Int1Configuration()
{
	//设置INT0
	IT1=1;//跳变沿出发方式（下降沿）
	EX1=1;//打开INT0的中断允许。
	EA=1;//打开总中断	
}
/*******************************************************************************
* 函数名         : Int0() 
* 函数功能		   : 外部中断0 中断函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Int1() interrupt 2		 
{
	Delay10ms();
	if(K4==0)
	{
	 ClockState=~ClockState;
	 SetPlace=0;		
	}
}
/*******************************************************************************
* 函数名         : Delay10ms
* 函数功能		   : 延时函数，延时10ms
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Delay10ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
} 
 