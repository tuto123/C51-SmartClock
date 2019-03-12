/*******************************************************************************

* 函数功能名:   日期显示

*******************************************************************************/
#include"lcd.h"
#include"lcd1602.h"
#include "DS1302.h"
#include<temp.h>
void DisTime();
void DisTemperture();
void DisDate();
extern unsigned char clockdata[9];
void DisDate()
{
  	
 /*   clockdata[0] = 0;			//秒
	clockdata[1] = 42;			//分
	clockdata[2] = 10;			//小时
	clockdata[3] = 10;		    //日期
	clockdata[4] = 1;		    //月份
	clockdata[5] = 19;		    //年
	clockdata[6] = 3;			//星期几
	clockdata[7] = 0;
	clockdata[8] = 20;	*/

//	LCD1602_Initialize();

//	DS1302_settime();
//	while (1)
//	{
//		DS1302_gettime();
		
		//年份
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
//    }
}
  



