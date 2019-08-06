#include "Interface.h"


#define MicroSD_CS_SET GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define MicroSD_CS_RESET GPIO_ResetBits(GPIOB,GPIO_Pin_0)

char MicroSDDataBuff[512]={0};//һ�������Ĵ�С
typedef struct
{
	char CID[16];
	char RCA[2];
	char DSR[2];
	char CSD[16];
	char SCR[8];
	char OCR[4];
	char SSR[64];//(SD Status)
	char CSR[4];//Card Status)
	
}__MicroSDInfo;

__MicroSDInfo  MicroSDInfo={0};



char SentCommandToMicroSD(char cmd,int data,char crc)
{
	char result=0,times=0;
	
	MicroSD_CS_SET;//��ֹSD��Ƭѡ ͬ��ʱ��
	SPI1_ReadWriteByte(0xff);   
	MicroSD_CS_RESET;//��ʼ����
	SPI1_ReadWriteByte(cmd);
	for(times=0;times<4;times++)    
	{    
      SPI1_ReadWriteByte((data>>24)&0xff);
			data<<=8;
  }

  SPI1_ReadWriteByte(crc);
	SPI1_ReadWriteByte(0xff); //�˸�ʱ�� 
	times=0;
	do    
	{  //��ȡ��8λ   
		result = SPI1_ReadWriteByte(0xFF);   
		times++;   
	}
	while((result==0xff)&&(times<200));
	return result;
}

//��ʼ�������Ǻ��ȶ�Ҳ����˵���������ݿ��ܲ��Ǻ��ȶ�
char SD_Init(void)
{
	char i,temp=0;
	//char CMD[] = {0x40,0x00,0x00,0x00,0x00,0x95};
	int retry=0;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ�� 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //PB0
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOB0
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	//��ʼ��SPI1
	SPI1_Init();
	
	MicroSD_CS_SET;
	//��������74��ʱ���ź�
	for (i=0;i<0x2f;i++){SPI1_ReadWriteByte(0xff);} 
	//Ϊ���ܹ��ɹ�д��CMD0,������д200��
	do  
	{   
		temp=SentCommandToMicroSD(0x40,0,0x95);   
		retry++;   
		if(retry>800)
		{ //����200��   
		//CMD0 Error!	return(INIT_CMD0_ERROR); 
			//printf("Init MicroSD CMD0 Error!!!Back:%d\n\n",temp);
			return 0;
		}   
	}    
	while(temp!=0x01); //��Ӧ01h��ֹͣд��
	//printf("Reset MicroSD successfully!!!times:%d\n\n",retry);
	//����CMD1��SD�� 
	retry=0;   
	do  
	{
		//Ϊ���ܳɹ�д��CMD1,д100��   
		temp=SentCommandToMicroSD(0x41,0,0xff);
		retry++;   
		if(retry>800)    
		{ 
			//����100��
			//printf("Init 1MicroSD CMD1 Error!!!Back:%d\n\n",temp);
			return 0;
		}
	}
	while(temp!=0x00);//��Ӧ00hֹͣд��    
	MicroSD_CS_SET;  //Ƭѡ��Ч
	//printf("Init MicroSD sent CMD1 successfully!!!times:%d\n\n",retry);
	
	//���������SPI����
	SPI1_SetSpeed(SPI_BaudRatePrescaler_4);
	
	return 0;
}






char WriteSectorToMicroSD(long addr,char *buff) 
{     
   int tmp,retry;   
   unsigned int i;   
   addr = addr << 9; //addr = addr * 512 
   //д����24��SD����ȥ   
   retry=0;   
   do  
   {  //Ϊ�˿ɿ�д�룬д100��   
      tmp=SentCommandToMicroSD(0x58,addr,0xff);   
      retry++;   
      if(retry>800)    
      {    
				//printf("Write CMD58 Error!!!\n\r");
        return 1; //send commamd Error!   
      }   
   }   
   while(tmp!=0);
	 
   //��д֮ǰ�Ȳ���100��ʱ���ź�   
   for (i=0;i<100;i++)   
   {   
      SPI1_ReadWriteByte(0xff);   
   }   
   //д�뿪ʼ�ֽ�   
   SPI1_ReadWriteByte(0xfe);    
    
   //���ڿ���д��512���ֽ�   
   for (i=0;i<512;i++)   
   {   
      SPI1_ReadWriteByte(*buff);
			buff++;
   }
   //CRC-Byte    
   SPI1_ReadWriteByte(0xFF); //Dummy CRC   
   SPI1_ReadWriteByte(0xFF); //CRC Code
	 
   tmp=SPI1_ReadWriteByte(0xff);   // read response   
   if((tmp & 0x1F)!=0x05) // д���512���ֽ���δ������   
   {   
     MicroSD_CS_SET;
		 //printf("Write data didn't accept by MicroSD\n\r");
     return 1; //Error!   
   }   
   //�ȵ�SD����æΪֹ   
	 //��Ϊ���ݱ����ܺ�SD�����򴢴������б������   
   while (SPI1_ReadWriteByte(0xff)!=0xff);
	 
   //��ֹSD�� д��ɹ�
   MicroSD_CS_SET;
   return 0;   
}

char ReadSectorFromMicroSD(long sector,char *buffer)   
{     
   int retry;   
   //����16  
	int times=0;
  //unsigned char CMD[] = {0x51,0x00,0x00,0x00,0x00,0xFF};    
  unsigned char temp;   
   
   //��ַ�任   ���߼����ַתΪ�ֽڵ�ַ   
   sector = sector << 9; //sector = sector * 512
   //������16д��SD��   
   retry=0;   
   do  
   {  //Ϊ�˱�֤д������  һ��д100��   
      temp=SentCommandToMicroSD(0x51,sector,0xff);   
      retry++;   
      if(retry>800)    
      {   
				//printf("Read sector from MicroSD is failed!!\n\r");
        return 1; //block write Error!   
      }   
   }   
   while(temp!=0);  
   //Read Start Byte form MMC/SD-Card (FEh/Start Byte)   
   //Now data is ready,you can read it out.   
  while (SPI1_ReadWriteByte(0xff) != 0xfe);
	for(times=0;times<512;times++)
	{
		MicroSDDataBuff[times]=SPI1_ReadWriteByte(0xff);
	}
	//��ֹSD�� �������
   MicroSD_CS_SET;
	return 0;
} 

char WriteSectorsToMicroSD(long addr,char *buff,int count)
{
	WriteSectorToMicroSD(addr,buff);
	return 0;
}
char ReadSectorsFromMicroSD(long addr,char *buff,int count)
{
	ReadSectorFromMicroSD(addr,buff);
	return 0;
}

