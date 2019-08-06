#include "Interface.h"
#include "Init.h"
#include "malloc.h"
/*********************************************************

���ڻ�����������û���ܹ���������ִ��֮ǰ���Ӳ���ĳ�ʼ������������Ҫ���¶���
һ��ͷ�ļ������Ӳ���ĳ�ʼ���Ĺ�����








*******************************************************/
char Init(void)
{
	char isInit=0;
	LEDInit();
	delay_init();
	UsartInit(115200);
	
	PS2_Init();
	SPI2_Init();
	LCDInit();
	SD_Init();
	W25QXX_Init();
	my_mem_init(SRAMIN);
	return isInit;
}


