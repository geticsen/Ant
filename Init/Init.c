#include "Interface.h"
#include "Init.h"
#include "malloc.h"
/*********************************************************

���ڻ�����������û���ܹ���������ִ��֮ǰ���Ӳ���ĳ�ʼ������������Ҫ���¶���
һ��ͷ�ļ������Ӳ���ĳ�ʼ���Ĺ�����








*******************************************************/
typedef struct{
	void *Function;
	char Info[50];
	void *CallBack;
	char CallBackInfo[50];
}__InitStep;
#define InitStepSize	10


__InitStep InitStep[InitStepSize]={
	{UsartInit,"Uart has Init!\n\r",0,0},
	{delay_init,"delay_init!\n\r",0,0},
	{SPI1_Init,"LED has Init!\n\r",0,0},
	{SPI2_Init,"LED has Init!\n\r",0,0},
	{MicroSDInit,"MicroSD has Init!\n\r",0,0},
	{VS_Init,"LED has Init!\n\r",0,0},
	{KeyInit,"KEY has Init!\n\r",0,0},
	{LEDInit,"LED has Init!\n\r",0,0,},
	//{LCDInit,"LED has Init!\n\r",0,0},
};
/*

	UsartInit(115200);
	LEDInit();
	delay_init();
	SPI2_Init();
	SPI1_Init();
	
	//LCDInit();
	SD_Init();
	VS_Init();
	W25QXX_Init();
	KeyInit();
	//my_mem_init(SRAMIN);
*/
char Init(void)
{
	char isInit=0;
//	char Step=0;
//	for(Step=0;Step<InitStepSize;Step++)
//	{
//		if(InitStep[Step].Function!=0)
//		{
//			(*(void(*)())InitStep[Step].Function)();
//			printf("%s",InitStep[Step].Info);
//				if(InitStep[Step].CallBack!=0)
//				{
//					(*(void(*)())InitStep[Step].CallBack)();
//					printf("%s",InitStep[Step].CallBackInfo);
//				}
//		}
		
//	}
	SPI2_Init();
	SPI1_Init();
	UsartInit(115200);
	delay_init();
	KeyInit();
	LEDInit();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	KeyInit();					//��ʼ������
	LCD_Init();			   	//��ʼ��LCD     
	W25QXX_Init();				//��ʼ��W25Q128
 	VS_Init();	  				//��ʼ��VS1053 
 	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
	//my_mem_init(SRAMIN);
	return isInit;
}


