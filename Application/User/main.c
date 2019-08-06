#include "Interface.h"
#include "FrameBox.h"
#include "StringOperation.h"
#include "Init.h"
#include "ff.h"	
#include "malloc.h"
int x=0,y=0;

void drawParten(void);
u8 exfuns_init(void);
extern char MicroSDDataBuff[512];//һ�������Ĵ�С
u16 color=0x000;
extern char MicroSDDataBuff[512];

FATFS *fs[_VOLUMES];//�߼����̹�����.	 
FIL *file;	  		//�ļ�1
FIL *ftemp;	  		//�ļ�2.
UINT br,bw;			//��д����
FILINFO fileinfo;	//�ļ���Ϣ
DIR dir;  			//Ŀ¼

u8 *fatbuf;			//SD�����ݻ�����


void MicroSDTest()
{
	//�������ڴ濨��ʼ���Ժ�Ĳ��Խ��ж�д������ɹ����ǴӶ�д���кſ�ʼ��
	
	 //WriteSectorToMicroSD(2,"Hello I here did you find me!!!");
	 //delay_ms(200);
	 ReadSectorFromMicroSD(2,MicroSDDataBuff);
   printf("MicroSD read is:%s!!!!\n\n",MicroSDDataBuff);
	
}

void W25Q128Test()
{
	char arr[100]={0};
	W25QXX_Read((u8 *)arr,1024,sizeof(arr));
	printf("W25QRead:%s\n\n",arr);
}

void FrameTest()
{
	/*
void FrameClear(u16 Color);
void FrameFullAera(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void FrameDrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 Color);
void FrameDrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 Color);
void FrameDrawCircle(u16 x0,u16 y0,u8 r,u16 Color);
void FrameShowChar(u16 x,u16 y,u8 num,u8 size,u16 Color);
void FrameShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p,u16 Color);
	*/
	 FrameClear(YELLOW);
	 FrameFullAera(50,50,100,100,BLUE);
	 FrameDrawRectangle(25,25, 125, 125,RED);
	 FrameDrawCircle(100,100,50,BLACK);
	 FrameShowString(0,200,240,16,16,(u8 *)"this is Frame Test!!!",BLACK);
	
}
int main()
{
	
	int times=0;
	FIL *fp;
	Init();
	delay_ms(200);
	printf("I am working now!\n\r");
	if(!PS2_RedLight()){
		printf("Gamehandle is aredly in RedLight\n\r");
	}else{
		printf("not in game mode\n\r");
	}
	MicroSDTest();
	W25Q128Test();
	FrameTest();
	/*
	FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);			
	FRESULT f_close (FIL* fp);											
	FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);		
	FRESULT f_write (FIL* fp, const void* buff, UINT btw, UINT* bw);	
	*/
	exfuns_init();
	
	f_open (fp, "/aaa.txt", 1);	
	f_write (fp, "this is test",0, 0);
	f_close (fp);
	while(1)
	{
			times++;
		  drawParten();
			delay_ms(20);
		
			if(times<100)
			{
				LEDOn();
			}else if(times<200){
				LEDOff();
			}else
				times=0;
		
	}
	
}

void drawParten(void)
{
	char key;
	PS2_ClearData();  //�������
	PS2_ReadData();	   //������
	key=PS2_DataKey();
	if(key!=0)
	{
		switch(key){
			case PSB_CIRCLE:FrameClear(YELLOW);break;
			case PSB_PAD_UP:y-=5;break;
			case PSB_PAD_DOWN:y+=5;break;
			case PSB_PAD_LEFT:x-=5;break;
			case PSB_PAD_RIGHT:x+=5;break;
		}
		if(x==0)x=240;
		if(x>=240)x=0;
		if(y==0)y=320;
		if(y>320)y=0;
		FrameFullAera(x,y,x+10,y+10,0x0f0f);
	}
}



u8 exfuns_init(void)
{
	u8 i;
	for(i=0;i<_VOLUMES;i++)
	{
		fs[i]=(FATFS*)mymalloc(SRAMIN,sizeof(FATFS));	//Ϊ����i�����������ڴ�	
		if(!fs[i])break;
	}
	file=(FIL*)mymalloc(SRAMIN,sizeof(FIL));		//Ϊfile�����ڴ�
	ftemp=(FIL*)mymalloc(SRAMIN,sizeof(FIL));		//Ϊftemp�����ڴ�
	fatbuf=(u8*)mymalloc(SRAMIN,512);				//Ϊfatbuf�����ڴ�
	if(i==_VOLUMES&&file&&ftemp&&fatbuf)return 0;  //������һ��ʧ��,��ʧ��.
	else return 1;	
}

