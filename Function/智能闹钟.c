/*-----------------------------------------------------*/
        /****************智能闹钟*****************/
               /***********************
功能介绍：1、显示时间	   2、显示星期
          3、显示温度      4、显示日期    年/  月/  日 
		   		***********************/
/*******************************************************************/

/* 使用说明:独立按键：* * * *      +按键（按下停止闹钟） 设置时间日期按键  设置闹钟按键  设置闹铃按键
                      *   * *      -按键	                               12进制        24进制
						     		   	   
					            	   
*/         




/****************************************
 功能说明:此闹钟功能为
          显示时间，当前时间可用按键进行调整
          显示当前的温度，利用温度传感器进行测温
		  添加闹钟后可以到一定时间后即可闹铃，闹铃为小星星(可修改)
		  显示当前日期和星期可利用按键进行修改
  
*****************************************/
/****************************************************************************************************************/
						    
#include<reg51.h>
#include<temp.h>
#include<lcd.h>
#include<lcd1602.h>
#include "DS1302.h"
void DisTime();
void DisTemperture();
void DisDate();
void Clocker();
void Buttons();
extern unsigned char jz;
extern unsigned char clockdata[];
extern unsigned char naozhongdata[];
void main()
{
/*	naozhongdata[0] = 0;	   //闹钟秒
	naozhongdata[1] = 0;	   //闹钟分
	naozhongdata[2] = 0;	   //闹钟时
	naozhongdata[3] = 0;	   //闹钟星期	*/
    clockdata[0] = 57;			//秒
	clockdata[1] = 26;			//分
	clockdata[2] = 10;			//小时
	clockdata[3] = 10;		    //日期
	clockdata[4] = 1;		    //月份
	clockdata[5] = 19;		    //年
	clockdata[6] = 4;		    //星期几
	clockdata[7] = 0;			//12,24进制
	clockdata[8] = 20;			//20年
	
	 LcdInit();			 //初始化LCD1602
	 LCD1602_Initialize();


  	 DS1302_settime();

     while(1)
	 {	

	
 	    DisTime();					  //显示时间
		 
	    DisTemperture();			  //显示温度
		
    	DisDate();					  //显示日期 	
			
		Buttons();				      //独立按键处理

	 }
}

