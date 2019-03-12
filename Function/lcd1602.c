#include "LCD1602.h"
#include "common.h"

//等待LCD1602空闲
void LCD1602_Wait()
{
#ifdef	LCD1602_MODE_4BIT				//////////////////////////////4位模式
	unsigned char lcdstatus_low;
#endif

	unsigned char lcdstatus;
	
	do {

#ifdef LCD1602_MODE_4BIT				   //-------------------------4位模式
		LCDDATAPORT = 0xF0;	   	          //数据商品设置为0xF0
#else									  /////////////////////////8位模式
		LCDDATAPORT = 0xFF;	   	          //数据商品设置为0xFF
#endif

		LCDEN = 0; LCDRS = 0; LCDRW = 1;  //禁止LCD; 选择命令寄存器; 读操作

#ifdef LCD1602_MODE_4BIT			 //-------------------------4位模式
		LCDEN = 1; delay_5us();	   	//使能LCD
		lcdstatus = LCDDATAPORT; delay_5us();  //读取状态高4位
		LCDEN = 0;delay_5us();     	//禁止LCD

		LCDEN = 1; delay_5us();		 //使能LCD
		lcdstatus_low = LCDDATAPORT; delay_5us();  //读取状态低4位
		LCDEN = 0;delay_5us(); 		//禁止LCD
#else								//+++++++++++++++++++++++8位模式
		LCDEN = 1; delay_5us();		//使能LCD
		lcdstatus = LCDDATAPORT;delay_5us();  //读取状态
		LCDEN = 0;delay_5us();	   //禁止LCD
#endif								  
	} while ( lcdstatus & 0x80);
}

//向LCD1602写入命令
void LCD1602_WriteCommand( unsigned char cmd )
{
	LCD1602_Wait();						 //等待LCD空闲

	LCDEN = 0;	LCDRS = 0; LCDRW = 0;	 //禁止LCD，选择命令寄存器，写操作

#ifdef LCD1602_MODE_4BIT				 //---------------------------------4位模式
	LCDDATAPORT = cmd & 0xF0;			 //写入命令高4位
	LCDEN = 1; delay_5us();				 //使能LCD
	LCDEN = 0; delay_5us();				 //禁止LCD

	LCDDATAPORT = (( cmd & 0x0F) << 4 );//写入命令低4位
	LCDEN = 1; delay_5us();				//使能LCD
	LCDEN = 0; delay_5us();				//禁止LCD
#else									 //+++++++++++++++++++++++++++++++++8位模式
	LCDDATAPORT = cmd;					 //写入命令
	LCDEN = 1; delay_5us();				//使能LCD
	LCDEN = 0; delay_5us();				//禁止LCD
#endif
}

//向LCD1602写入数据
void LCD1602_WriteData( unsigned char dat)
{
	LCD1602_Wait();			  			//等待LCD空闲

	LCDEN = 0;	LCDRS = 1; LCDRW = 0;	//禁止LCD，选择数据寄存器，写操作

#ifdef LCD1602_MODE_4BIT				 //-----------------------------4位模式
	LCDDATAPORT = dat & 0xF0;			 //写入命令高4位
	LCDEN = 1;delay_5us(); 				 //使能LCD
	LCDEN = 0; delay_5us(); 			 //禁止LCD

	LCDDATAPORT = ((dat & 0x0F) << 4);	 //写入命令低4位
	LCDEN = 1; delay_5us();				 //使能LCD
	LCDEN = 0; delay_5us();				 //禁止LCD
#else									 //+++++++++++++++++++++++++++++8位模式
	LCDDATAPORT = dat;					 //写入命令
	LCDEN = 1; delay_5us();				 //使能LCD
	LCDEN = 0; delay_5us();				 //禁止LCD
#endif
}

//初始化LCD1602
void LCD1602_Initialize( )
{
#ifdef LCD1602_MODE_4BIT			//-----------------------------4位模式
	LCD1602_WriteCommand( LCD1602_CMD_4BIT_2LINE_5X7 ); 
#else								//+++++++++++++++++++++++++++++8位模式
	LCD1602_WriteCommand( LCD1602_CMD_8BIT_2LINE_5X7 );
#endif 
	
	delay_ms(1);
	LCD1602_WriteCommand( LCD1602_CMD_RESET ); delay_ms(1);
	LCD1602_WriteCommand( LCD1602_CMD_CURSOR_TO_RIGHT ); delay_ms(1);
	LCD1602_WriteCommand( LCD1602_CMD_LCD_ON_CURSOR_OFF_BLANK_OFF ); delay_ms(1);

}

//将自定义字符点阵数据写到CGRAM
void LCD1602_WriteCGRAM( unsigned char cgramdata[][8], unsigned char n) 
{
	unsigned char i,j;
	LCD1602_WriteCommand( 0x40 );			//设置CGRAM的地址为0x40
	for ( j = 0; j < n; j++ )
	for ( i = 0; i < 8; i++ )				//写入8个字节的自定义字模数据
		LCD1602_WriteData( cgramdata[j][i] );					   
}


//将DDRAM数据指针定位到第row行、第column列；row取1或2，column范围为1~16
void LCD1602_Locate( unsigned char row, unsigned char column )
{
	unsigned char address;
  	if( row == 1 )
  		address = 0x80 + column - 1; // - - 第一行位置
  	else
    	address = 0xc0 + column - 1; // - - 第二行位置
	
	LCD1602_WriteCommand(address);	//写入地址
}

//在第row行、第column列显示字符c,row取1或2，column范围为1~16
void LCD1602_PrintChar(  unsigned char row, unsigned char column, unsigned char c )
{
	LCD1602_Locate( row, column);			  //定位读写DDRAM指针
    LCD1602_WriteData( c );					  //写入DDRAM数据
}

//从第row行、第column列开始显示字符串str,row取1或2，column范围为1~16,str以'\0'结束
void LCD1602_PrintString(  unsigned char row, unsigned char column, unsigned char *str )
{
	unsigned int i;
	unsigned char *strpointer;			//数据指针
	unsigned char rowtmp, columntmp; 	//当前行、当前列

	//如果row、column无效则显示提示信息，并退出
	unsigned char errorstring[12] = "(1,1)~(2,16)";				
	if ( row < 1 || row > 2 || column < 1 || column > 16 )
	{
		for ( i = 0; i < 12; i++ )
			LCD1602_PrintChar( 1, i+1, errorstring[i]);	 //在第1行显示errorstring字符串
		return;											 //退出
	}
	
	rowtmp = row; columntmp = column;					//当前行、当前列分别为row、column
	strpointer = str;									//数据指针先赋值为str

	while ( *strpointer != '\0' )						//字符串是否结束？
	{
		LCD1602_PrintChar( rowtmp, columntmp, *strpointer );  //在当前行、当前列打印一个字符
		
		strpointer++;										  //修改数据指针，指向下一个要打印的字符
		columntmp++;										  //当前列行右移一次

		if ( columntmp > 16 )								  //如果到了当前行的最后一列，从下一行的第1列开始
		{
			columntmp = 1;									  //第1列

			rowtmp++;										  //下一行
			if ( rowtmp > 2 )								  //已经是第2行了，则回到第1行
				rowtmp = 1;
		}	
	}

}