#ifndef DS1302_H
#define DS1302_H
#include "reg51.h"
#include "intrins.h"
#include "common.h"
#endif
/*********************************************************************************************/
//---定义全局函数---//
void Ds1302Write(unsigned char addr, unsigned char dat);
unsigned char Ds1302Read(unsigned char addr);
void Ds1302Init();
void Ds1302ReadTime();

//---加入全局变量--//
//extern unsigned char TIME[7];
extern unsigned char code WRITE_RTC_ADDR[7];	//加入全局变量

/*********************************************************************************************/

//操作方向
#define DS1302_WRITE	0x00			 //写
#define DS1302_READ		0x01			 //读

//秒、分、时、日、月、周、年寄存器地址	     |  7  |  6  |     5     |  4  | 3 | 2 | 1 | 0 |
#define DS1302_SECOND	0x80			//	 | CH  |     10     SEC        |      SEC      |
#define DS1302_MINUTE	0x82			//	 |  0  |     10     MIN        |      MIN      |
#define DS1302_HOUR		0x84			//	 |12/24|  0  |  10/(A/P) | HR  |      HR       |
#define DS1302_DATE		0x86			//	 |  0  |  0  |    10 DATE      |     DATE      |
#define DS1302_MONTH	0x88			//	 |  0  |  0  |     0     | 10 M|     MONTH     |
#define DS1302_WEEKDAY	0x8A			//	 |  0  |  0  |     0     |0    |  0 |   DAY    |
#define DS1302_YEAR		0x8C			//	 |           10 YEAR           |     YEAR      | 

//控制寄存器地址 		               |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
#define DS1302_CONTROL	0x8E	    // | W/P |  0  |  0  |  0  |  0  |  0  |  0	 |  0  |

//点滴充电控制寄存器写、读地址	               |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
#define DS1302_TRICKLECHARGE	0x90        // | TCS | TCS | TCS | TCS |  DS |  DS |  RS |  RS |

//时钟突发写、读地址
#define DS1302_CLOCKBURST		0xBE

//BRAM
#define DS1302_BRAMSTART			0xC0			 //BRAM起始地址
#define DS1302_BRAMEND				0xFC			 //BRAM结束地址
#define DS1302_BRAMBURST			0xFE			 //BRAM突发操作地址





//向DS1302写一个字节的数据
void DS1302_SPIwritebyte( unsigned char dat );
//从DS1302读一个字节的数据
unsigned char DS1302_SPIreadbyte( );

//向DS1302写一个字节的数据到地址为address的单元（寄存器）
void DS1302_writeybyte( unsigned char address, unsigned char dat );
//从DS1302的address的单元（寄存器）读一个字节的数据
unsigned char DS1302_readbyte( unsigned char address );

//突发模式写时钟数据，数据存放在clockdataBCD[8]中
void DS1302_writeclockburst( );
//突发模式读时钟数据，数据存放在clockdataBCD[8]中
void DS1302_readclockburst( );

//突发模式写ram数据，数据存放在BRAMdata[31]中
void DS1302_writeramburst( );
//突发模式读ram数据，数据存放在BRAMdata[31]中
void DS1302_readramburst( );

//上锁（开启写保护）
void DS1302_lock();

//解锁（取消写保护）
void DS1302_unlock();


//获得时钟数据，输出为二进码
unsigned char DS1302_getsecond();				  //秒
unsigned char DS1302_getminute();				  //分
unsigned char DS1302_gethour();					  //时
unsigned char DS1302_getdate();					  //日
unsigned char DS1302_getmonth();				  //月
unsigned char DS1302_getweekday();				  //周
unsigned char DS1302_getyear();					  //年

//设置时钟数据，输入为二进码
void DS1302_setsecond( unsigned char second );	  //秒
void DS1302_setminute( unsigned char minute );	  //分
void DS1302_sethour( unsigned char hour );		  //时
void DS1302_setdate( unsigned char date );		  //日
void DS1302_setmonth( unsigned char month );	  //月
void DS1302_setweekday( unsigned char weekday );  //周
void DS1302_setyear( unsigned char year );		  //年


//获得控制寄存器数据，输出为二进码
unsigned char DS1302_getcontrol();					  //控制寄存器
//设置控制寄存器数据
void DS1302_setcontrol( unsigned char con );					  //控制寄存器

//设置DS1302的时间，输入为一个字符串，格式为：YYYY-MM-DD HH:MM:SS 或 YYYY/MM/DD HH:MM:SS
void DS1302_settime( );

//获取DS1302的时间（字符串），格式为：YYYY-MM-DD HH:MM:SS 或 YYYY/MM/DD HH:MM:SS 
void DS1302_gettime( );
