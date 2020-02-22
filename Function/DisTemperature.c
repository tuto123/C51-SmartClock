/*******************************************************************************

* ����������:   �¶���ʾ

*******************************************************************************/

#include"lcd.h"
#include"temp.h"
#include"lcd1602.h"
uchar danwei[] = "T:";
void DisDate();
void LcdDisplay(int);
void DisTime();
void DisTemperture();
void DisDate();
/*******************************************************************************
* ������         : Distemperture()
* ��������		 : ��ʾ�¶�
*******************************************************************************/

void DisTemperture()
{

//	LcdInit();			 //��ʼ��LCD1602
//	LCD1602_Initialize();
    LCD1602_PrintString(2,1,danwei);
	LcdWriteCom(0xC5);	//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('C');
//	DisTime();					  //��ʾʱ��
		    
//	DisClock();					  //��ʾ�������
    
//	DisDate();					  //��ʾ���� 
	
//	while(1)
//	{

		LcdDisplay(Ds18b20ReadTemp());
		
        
//	}
}

/*******************************************************************************
* ������         : LcdDisplay()
* ��������		 : LCD��ʾ��ȡ�����¶�
*******************************************************************************/

void LcdDisplay(int temp) 	 //lcd��ʾ
{
    
  	unsigned char  datas[] = {0, 0, 0, 0, 0}; //��������
	float tp;  
	if(temp< 0)				//���¶�ֵΪ����
  	{
	  	LcdWriteCom(0xC2);		//д��ַ 80��ʾ��ʼ��ַ
		SBUF='-';//�����յ������ݷ��뵽���ͼĴ���
		while(!TI);			         //�ȴ������������
		TI=0;						 //���������ɱ�־λ
	    LcdWriteData('-');  		//��ʾ��
		//��Ϊ��ȡ���¶���ʵ���¶ȵĲ��룬���Լ�1����ȡ�����ԭ��
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ��������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
 
  	}
 	else						 //���¶�ֵΪ����
  	{			
	  	LcdWriteCom(0xC2);		//д��ַ C0��ʾ��ʼ��ַ
	    LcdWriteData('+'); 		//��ʾ��
		SBUF='+';//�����յ������ݷ��뵽���ͼĴ���
		while(!TI);			         //�ȴ������������
		TI=0;						 //���������ɱ�־λ
		tp=temp;//��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
		//����¶���������ô����ô������ԭ����ǲ���������
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ��������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//�����0.5��������С������档
	}
//	datas[0] = temp / 10000;
	datas[1] = temp % 10000 / 1000;
	datas[2] = temp % 1000 / 100;
//	datas[3] = temp % 100 / 10;
//	datas[4] = temp % 10;

/*	LcdWriteCom(0xC1);		  //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[0]); //��λ 
	SBUF = '0'+datas[0];//�����յ������ݷ��뵽���ͼĴ���
	while (!TI);			         //�ȴ������������
	TI = 0;	*/
	
	LcdWriteCom(0xC3);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[1]); //ʮλ
	SBUF = '0'+datas[1];//�����յ������ݷ��뵽���ͼĴ���
	while (!TI);			         //�ȴ������������
	TI = 0;

	LcdWriteCom(0xC4);		//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[2]); //��λ 
	SBUF = '0'+datas[2];//�����յ������ݷ��뵽���ͼĴ���
	while (!TI);			         //�ȴ������������
	TI = 0;

/*	LcdWriteCom(0xC3);		//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('.'); 		//��ʾ ��.��
	SBUF = '.';//�����յ������ݷ��뵽���ͼĴ���
	while (!TI);			         //�ȴ������������
	TI = 0;	 */

/*	LcdWriteCom(0xC3);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[3]); //��ʾС����  
	SBUF = '0'+datas[3];//�����յ������ݷ��뵽���ͼĴ���
	while (!TI);			         //�ȴ������������
	TI = 0;

	LcdWriteCom(0xC4);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[4]); //��ʾС���� 
	SBUF = '0'+datas[4];//�����յ������ݷ��뵽���ͼĴ���
	while (!TI);			         //�ȴ������������
	TI = 0;*/
/*	for(i=0; i<6; i++)
	{
	 	SBUF = CNCHAR[i];//�����յ������ݷ��뵽���ͼĴ���
		while (!TI);			         //�ȴ������������
		TI = 0;
	} */

	 
}



