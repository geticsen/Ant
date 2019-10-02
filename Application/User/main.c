#include "Interface.h"
#include "FrameBox.h"
#include "StringOperation.h"
#include "Init.h"


//int x=0,y=0;
//u8 exfuns_init(void);

//extern char MicroSDDataBuff[512];//һ�������Ĵ�С
//u16 color=0x000;
//extern char MicroSDDataBuff[512];

//void MicroSDTest()
//{
//	//�������ڴ濨��ʼ���Ժ�Ĳ��Խ��ж�д������ɹ����ǴӶ�д���кſ�ʼ��
//	
//	 //WriteSectorToMicroSD(2,"Hello I here did you find me!!!");
//	 delay_ms(10);
//	 SD_ReadDisk((u8*)MicroSDDataBuff,2,1);
//   printf("MicroSD read is:%s!!!!\n\n",MicroSDDataBuff);
//	
//}


//void W25Q128Test()
//{
//	//char arr1[100]="this is a W25Q128 Test It works.";
//	char arr2[100]={0};
//	//W25QXX_Write((u8 *)arr1,1000,sizeof(arr1));
//	W25QXX_Read((u8 *)arr2,1000,sizeof(arr2));
//	printf("W25QRead:%s\n\n",arr2);
//}

/*******��������*****/
FIL fil;
FRESULT res;
UINT bww;
char buf[100];
 
 int main(void)
 { 	 
	u32 sd_size;	
	u32 total,free;	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2 
	UsartInit(115200);
	LEDInit();
	delay_init();
	SPI1_Init();
	SPI2_Init();
	
	//LCDInit();
	SD_Init();
	
	W25QXX_Init();
	KeyInit();
	VS_Init();
	 
 	exfuns_init();		//Ϊfatfs��ر��������ڴ�
 	mem_init();			  //��ʼ���ڴ��		
 	exfuns_init();		//Ϊfatfs��ر��������ڴ�	
	 
 	//f_mount(fs[1],"1:",1); 					//����FLASH.	 
	 f_mount(fs[0],"0:",1); 					//����SD�� 
	  
  while(exf_getfree((u8*)"0",&total,&free))	//�õ�SD������������ʣ������
	{
		printf("SD Card Fatfs Error!\n");
	}													  			    
	//���SD���ɹ� 											    
	printf("SD Card OK\n");
	printf("SD Total Size:%d MB\n",total>>10);	 
	printf("SD  Free Size:%d MB\n",free>>10); 	  

 /********************start*************************/	
	res=f_open (&fil,"0:/message.txt", FA_CREATE_ALWAYS|FA_WRITE);	
	 
	f_write (&fil, " SD_CARD test1 \r\n", sizeof("SD_CARD test1 ")+2, &bww);
	f_write (&fil, " SD_CARD test2 \r\n", sizeof("SD_CARD test2 ")+2, &bww);
	f_write (&fil, " SD_CARD test3 \r\n", sizeof("SD_CARD test3 ")+2, &bww);
	f_write (&fil, " SD_CARD test4 \r\n", sizeof("SD_CARD test4 ")+2, &bww);
	f_write (&fil, " SD_CARD test5 \r\n", sizeof("SD_CARD test5 ")+2, &bww);
	
	f_close(&fil);
	
	
	res=f_open (&fil,"0:/message.txt", FA_CREATE_ALWAYS|FA__WRITTEN);	
	 
	f_write (&fil, " SD_CARD test6 \r\n", sizeof("SD_CARD test6 ")+2, &bww+100);
	f_write (&fil, " SD_CARD test7 \r\n", sizeof("SD_CARD test7 ")+2, &bww+100);
	f_write (&fil, " SD_CARD test8 \r\n", sizeof("SD_CARD test8 ")+2, &bww+100);
	f_write (&fil, " SD_CARD test9 \r\n", sizeof("SD_CARD test9 ")+2, &bww+100);
	f_write (&fil, " SD_CARD test0 \r\n", sizeof("SD_CARD test0 ")+2, &bww+100);
	
	f_close(&fil);
	
//	res=f_open (&fil,"0:/message.txt", FA_READ);
//    
//  f_read (&fil, buf,100,&bww);	
//	
//	f_close(&fil);
//	
//  printf("д��SD�������ݣ�%s\n",buf);
/********************end***************************/  

	while(1);
}


