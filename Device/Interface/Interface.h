#ifndef __INTERFACE_H
#define __INTERFACE_H
#include"Config.h"
#include"Typedefine.h"
/****************************************************KEY***********************************************/

void KeyInit(void);
char GetPressedKey(void);


/****************************************************Usart**********************************************/
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void UsartInit(u32 bound);



/****************************************************LED**********************************************/
void LEDInit(void);
void LEDOn(void);	
void LEDOff(void);


/****************************************************Delay**********************************************/

void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u16 nms);

/*****************************************************PS2**********************************************/
extern u8 Data[9];
extern u16 MASK[16];
extern u16 Handkey;

void PS2_Init(void);
u8 PS2_RedLight(void);//�ж��Ƿ�Ϊ���ģʽ
void PS2_ReadData(void);
void PS2_Cmd(u8 CMD);		  //
u8 PS2_DataKey(void);		  //��ֵ��ȡ
u8 PS2_AnologData(u8 button); //�õ�һ��ҡ�˵�ģ����
void PS2_ClearData(void);	  //������ݻ�����
/*******************************************LCD****************************************************/

void LCDInit(void);
//void LCD_Clear(u16 Color);
void LCD_DrawPoint(u16 x,u16 y,u16 Color);
/******************************************MicroSD**************************************************/

char SD_Init(void);
char WriteSectorToMicroSD(long addr,char *buff);
char ReadSectorFromMicroSD(long sector,char *buffer);

char WriteSectorsToMicroSD(long addr,char *buff,int count);
char ReadSectorsFromMicroSD(long addr,char *buff,int count);


/*******************************************SPI******************************************************/

void SPI1_Init(void);
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler);
u8 SPI1_ReadWriteByte(u8 TxData);

void SPI2_Init(void);
u8 SPI2_ReadWriteByte(u8 TxData);
u8 SPI_WriteByte(SPI_TypeDef* SPIx,u8 Byte);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);


/*******************************************W25Q128  Flash***********************************************/



extern u16 W25QXX_TYPE;					//����W25QXXоƬ�ͺ�		   

#define	W25QXX_CS_SET 		GPIO_SetBits(GPIOB,GPIO_Pin_12); 		//W25QXX��Ƭѡ�ź�
#define	W25QXX_CS_RESET 	GPIO_ResetBits(GPIOB,GPIO_Pin_12);  		//W25QXX��Ƭѡ�ź�				 

 


void W25QXX_Init(void);
u16  W25QXX_ReadID(void);  	    		//��ȡFLASH ID
u8	 W25QXX_ReadSR(void);        		//��ȡ״̬�Ĵ��� 
void W25QXX_Write_SR(u8 sr);  			//д״̬�Ĵ���
void W25QXX_Write_Enable(void);  		//дʹ�� 
void W25QXX_Write_Disable(void);		//д����
void W25QXX_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);
void W25QXX_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);   //��ȡflash
void W25QXX_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);//д��flash
void W25QXX_Erase_Chip(void);    	  	//��Ƭ����
void W25QXX_Erase_Sector(u32 Dst_Addr);	//��������
void W25QXX_Wait_Busy(void);           	//�ȴ�����
void W25QXX_PowerDown(void);        	//�������ģʽ
void W25QXX_WAKEUP(void);				//����









/*******************************************VS1053B***********************************************/

#define VS_RST      PBout(5) 	//RST
#define VS_XCS      PBout(6)  	//XCS
#define VS_DQ       PBin(7)  	//DREQ 
#define VS_XDCS     PBout(8)  	//XDCS 


__packed typedef struct 
{							  
	u8 mvol;		//������,��Χ:0~254
	u8 bflimit;		//����Ƶ���޶�,��Χ:2~15(��λ:10Hz)
	u8 bass;		//����,��Χ:0~15.0��ʾ�ر�.(��λ:1dB)
	u8 tflimit;		//����Ƶ���޶�,��Χ:1~15(��λ:Khz)
	u8 treble;		//����,��Χ:0~15(��λ:1.5dB)(ԭ����Χ��:-8~7,ͨ�������޸���);
	u8 effect;		//�ռ�Ч������.0,�ر�;1,��С;2,�е�;3,���.
	u8 speakersw;	//�������ȿ���,0,�ر�;1,�� 
	u8 saveflag; 	//�����־,0X0A,�������;����,����δ����	   
}_vs10xx_obj;

extern _vs10xx_obj vsset;		//VS10XX����



u16  VS_RD_Reg(u8 address);				//���Ĵ���
u16  VS_WRAM_Read(u16 addr);	    	//��RAM
void VS_WRAM_Write(u16 addr,u16 val);	//дRAM
void VS_WR_Data(u8 data);				//д����
void VS_WR_Cmd(u8 address,u16 data);	//д����
u8   VS_HD_Reset(void);			    	//Ӳ��λ
void VS_Soft_Reset(void);           	//��λ
u16 VS_Ram_Test(void);             		//RAM����	    
void VS_Sine_Test(void);            	//���Ҳ���
													 
u8 	 VS_SPI_ReadWriteByte(u8 data);
void VS_SPI_SpeedLow(void);
void VS_SPI_SpeedHigh(void);
void VS_Init(void);						//��ʼ��VS10XX	 
void VS_Set_Speed(u8 t);				//���ò����ٶ�
u16  VS_Get_HeadInfo(void);     		//�õ�������
u32 VS_Get_ByteRate(void);				//�õ��ֽ�����
u16 VS_Get_EndFillByte(void);			//�õ�����ֽ�
u8 	 VS_Send_MusicData(u8* buf);		//��VS10XX����32�ֽ�
void VS_Restart_Play(void);				//���¿�ʼ��һ�׸貥��	  
void VS_Reset_DecodeTime(void);			//�������ʱ��
u16  VS_Get_DecodeTime(void);   		//�õ�����ʱ��

void VS_Load_Patch(u16 *patch,u16 len);	//�����û�patch
u8 	 VS_Get_Spec(u16 *p);       		//�õ���������	   
void VS_Set_Bands(u16 *buf,u8 bands);	//��������Ƶ��
void VS_Set_Vol(u8 volx);				//����������   
void VS_Set_Bass(u8 bfreq,u8 bass,u8 tfreq,u8 treble);//���øߵ���
void VS_Set_Effect(u8 eft);				//������Ч
void VS_SPK_Set(u8 sw);					//��������������ؿ���
void VS_Set_All(void);

void vs10xx_read_para(_vs10xx_obj * vs10xxdev);
void vs10xx_save_para(_vs10xx_obj * vs10xxdev);

#endif



