#ifndef LCD1602_H
#define LCD1602_H
#include <reg51.h>
#include <intrins.h>
#endif

//#define LCD1602_MODE_4BIT  1

#define delay_5us()	{_nop_();_nop_();_nop_();_nop_();_nop_();}
#define LCD1602_CMD_RESET	0x01			//LCD复位，光标复位，显存清零

#define LCD1602_CMD_CURSOR_TO_LEFT	0x04 	//光标左移
#define LCD1602_CMD_SCREEN_TO_RIGHT	0x05	//屏幕右移
#define LCD1602_CMD_CURSOR_TO_RIGHT	0x06	//光标右移
#define LCD1602_CMD_SCREEN_TO_LEFT	0x07	//屏幕左移

#define LCD1602_CMD_LCD_OFF_CURSOR_OFF_BLANK_OFF				0x08		//屏幕关、光标关、闪烁关
#define LCD1602_CMD_LCD_ON_CURSOR_OFF_BLANK_OFF					0x0C		//屏幕开、光标关、闪烁关
#define LCD1602_CMD_LCD_ON_CURSOR_ON_BLANK_OFF					0x0E		//屏幕开、光标开、闪烁关
#define LCD1602_CMD_LCD_ON_CURSOR_ON_BLANK_ON					0x0F		//屏幕开、光标开、闪烁关

//不符合逻辑，待测！！
#define LCD1602_CMD_LCD_OFF_CURSOR_ON_BLANK_OFF					0x0A		//屏幕关、光标开、闪烁关
#define LCD1602_CMD_LCD_ON_CURSOR_OFF_BLANK_ON					0x0D		//屏幕开、光标关、闪烁开
#define LCD1602_CMD_LCD_OFF_CURSOR_OFF_BLANK_ON					0x09		//屏幕关、光标关、闪烁开
#define LCD1602_CMD_LCD_OFF_CURSOR_ON_BLANK_ON					0x09		//屏幕关、光标开、闪烁开

//光标位置移动，不改变DDRAM的值
#define LCD1602_CMD_CURSORPOSITION_TO_LEFT						0x10 		//光标左移
#define LCD1602_CMD_CURSORPOSITION_TO_RIGHT						0x14 		//光标右移
#define LCD1602_CMD_SCREENPOSITION_TO_RIGHT						0x18 		//屏幕左移
#define LCD1602_CMD_SCREENPOSITION_TO_LEFT						0x1C 		//屏幕右移

#define LCD1602_CMD_8BIT_2LINE_5X7								0x38 		//8位、双行、5*7模式
#define LCD1602_CMD_8BIT_1LINE_5X7								0x30 		//8位、单行、5*7模式
#define LCD1602_CMD_4BIT_2LINE_5X7								0x28 		//4位、双行、5*7模式
#define LCD1602_CMD_4BIT_1LINE_5X7								0x20 		//4位、单行、5*7模式

#define LCD1602_CMD_8BIT_2LINE_5X10								0x39 		//8位、双行、5*10模式
#define LCD1602_CMD_8BIT_1LINE_5X10								0x31 		//8位、单行、5*10模式
#define LCD1602_CMD_4BIT_2LINE_5X10								0x29 		//4位、双行、5*10模式
#define LCD1602_CMD_4BIT_1LINE_5X10								0x21 		//4位、单行、5*10模式

#define LCDDATAPORT P0

sbit LCDRW = P2^5;
sbit LCDRS = P2^6;
sbit LCDEN = P2^7;

//等待LCD1602空闲
void LCD1602_Wait();

//向LCD1602写入命令
void LCD1602_WriteCommand( unsigned char cmd );

//向LCD1602写入数据
void LCD1602_WriteData( unsigned char dat);

//初始化LCD1602
void LCD1602_Initialize( );

//将自定义字符点阵数据写到CGRAM
void LCD1602_WriteCGRAM( unsigned char cgramdata[][8], unsigned char n);//将自定义字符点阵数据写到CGRAM 

//将DDRAM数据指针定位到第row行、第column列；row取1或2，column范围为1~16
void LCD1602_Locate( unsigned char row, unsigned char column );

//在第row行、第column列显示字符c,row取1或2，column范围为1~16
void LCD1602_PrintChar(  unsigned char row, unsigned char column, unsigned char c );

//从第row行、第column列开始显示字符串str,row取1或2，column范围为1~16,str以'\0'结束
void LCD1602_PrintString(  unsigned char row, unsigned char column, unsigned char *str );