#include<reg51.h>
#include<intrins.h>		  			 
#define GPIO_KEY P1
sbit LED = P2^3	;  //用于看是否进入修改

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef UINT 
#define UINT unsigned int
#endif

extern UCHAR clock_week[2], clock_hour[2], clock_minute[2],clock_number;
extern UCHAR show,key,z; //show 选择显示内容 ，key 按键按下后取值，用于识别那个按键按下
						//z 	数组TIME下标数组index的下标
extern bit flag,digit,KEY_clock_stop,clock_number_logo; //flag 判断是否在修改 1 是，0否
					   //digit 判断十位还是个位 ，1十位 0个位
					   // KEY_clock_stop 按键结束闹钟标志

void judge(UCHAR logo);//输入数字限制判断	
UCHAR calc(UCHAR l,bit x);//计算对应输出在LCD1602位置	

void KeyDown();		//识别按键按下
void KeyDown_clock_stop(); // 闹钟结束按钮
void KEY_Pro(UCHAR k);	//处理按键
void number_input_date(UCHAR number); //数字输入处理
void number_input_week(UCHAR number);
void number_input_time(UCHAR number);
	