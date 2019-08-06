#include "StringOperation.h"
//#include<stdio.h>
//#include<stdlib.h>
/*
ʱ�䣺2018 5 1
����:latefly
���ܣ�����


����Ҫʵ�ֵĺ�����
StringReverse �ַ�����ת˳��
SplitString
IntString
StringInt
FloatString
StringFloat
DoubleString
StringDouble
StringEqual
StringCopy
HasSymbol �ж��Ƿ���ĳһ���ַ���
StringTrim
StringLength
StringBuffEmpty

edit version 2018 7 23
edit version 2018 9 19
�ַ����볤�ȣ��޸Ļ������Ĵ�С
edit version 2018 9 27
�����ַ��б��ʶ
edit version 2018 10 2
���뻺������� �ܹ���ȡʹ���˶��ٵ�λ��
edit version 2018 10 4
�޸��ַ���ת����int��ʱΪ������ת������׼��

*/



#define StringOperationBuffDeep 11
#define StringOperationBuffSize 50
char StringOperation_Buff[StringOperationBuffDeep][StringOperationBuffSize]={'\0'};

void StringBuffEmpty(void)
{
    int i;
    for(i=0;i<StringOperationBuffDeep;i++)
    {
        StringOperation_Buff[i][0]='\0';
    }
}

char GetStringBuffUsedNum(void)
{
    char used=0,i=0;
    while(i<StringOperationBuffDeep)
    {
        if(StringOperation_Buff[i][0]!='\0')
        {
            used++;
        }
        i++;
    }
    return used;
}
//������һЩ�ַ����Ĳ�����صĺ���
int StringLength(char *s)
{
    int Length=0;
    while(*s!='\0')
    {
        s++;
        Length++;
    }
    return Length;
}

char StringTrim(char sysmbol,char *s)
{
    char isTrim=0;
    char *p;
    p=s;
    while(*s!='\0')
    {
        if(*p!=sysmbol)
          {
            isTrim=1;
            *s=*p;
            if(*p=='\0')break;
            s++;
            p++;
          }
        else
            p++;
    }
    *s='\0';
    return isTrim;

}

char StringCopy(char *s1,char *s2)
{
    char isCopy=1;
    while(*s1!='\0')
    {
        *s2=*s1;
        s1++;
        s2++;
    }
    //s2++;
    *s2='\0';
    return isCopy;
}
//�ַ���˳��ת
char StringReverse(char *s)
{
    char i=0,*p;
    p=StringOperation_Buff[1];
    StringCopy(s,StringOperation_Buff[1]);
    while(*p!='\0')p++;
    p--;//����������
    while(*s!='\0')
    {
        *s=*p;
        s++;
        p--;
    }
    return i;
}
//����Ժ� ������ַ���
char SplitString(char split,char *s)
{
	char i=0,j=0;
	//StringOperation_Buff[0][0]='\0';
	//StringOperation_Buff[1][0]='\0';
	while(*s!='\0')
	{
		if(*s==split)
		{
			//j++;
			if(i>StringOperationBuffDeep||j>StringOperationBuffSize)break;//�������Ʒ�ָֹ��Խ��
			StringOperation_Buff[i][j]='\0';
			i++;
			j=0;
			s++;
			continue;
		}
		StringOperation_Buff[i][j]=*s;
		j++;
		s++;
	}
	StringOperation_Buff[i][j]='\0';
	return i;
}

char StringEqual(char *s1,char *s2)
{
	char isSame=1;
	while(*s1!='\0'&&*s2!='\0')
	{
		if(*s1-*s2)
		{
			isSame=0;
			break;
		}
		s1++;
		s2++;
	}
	if(*s1!='\0'||*s2!='\0')
	{
		isSame=0;
	}
	return isSame;
}
char HasSymbol(char symbol,char *s)
{
	char isHave=0;
	while(*s!='\0')
	{
		if(*s==symbol)
		{
			isHave=1;
			break;
		}
		s++;
	}
	return isHave;
}
int IntString(char *s)
{
	int num=0;
	while(*s!='\0')
	{
		if(*s-'0'>=0&&*s-'0'<=9)
		{
			num*=10;
			num+=(int)(*s-'0');
		}
		else
        {
            s++;
            if(*s!='\0')//�����ַ�ת�����ṩ����
                return 0;
            else
            {
                s--;
                return *s;//����ֻ�Ƕ�Ӧ�������ַ�ת���ĵĽ��
            }
        }

		s++;
	}
	return num;
}
//ת����������⻹δ���
char StringInt(int num)
{
	char i=0;
	while(num)
    {
        StringOperation_Buff[0][i]=num%10+'0';
        i++;
        num/=10;
    }
    StringOperation_Buff[0][i]='\0';
    StringReverse(StringOperation_Buff[0]);
	return i;//��ʾ�м������ݱ��������
}
float FloatString(char *s)
{
	float result=0;
	float num=0,pointer=0;
	while(*s!='\0')
	{
        if(*s=='.')
        {
            break;
        }
        if(*s-'0'>=0&&*s-'0'<=9)
        {
            num*=10;
            num+=(float)(*s-'0');
        }
        else
        {
            result=0;//TypeError
            return result;
        }
		s++;
	}
	if(HasSymbol('.',s))
    {
        while(*s!='\0')s++;//����β
        s--;//������\0��
        while(*s!='.')
        {
            if(*s-'0'>=0&&*s-'0'<=9)
            {
                pointer/=10;
                pointer+=(double)((*s-'0')/10.0);
            }
            else
            {
                result=0;
                return result;
            }
            s--;
        }
    }
    result=num+pointer;
    return result;
}
//�˷���������
char StringFloat(float number)
{
    char j=0;
    int num=(int)number;
    float pointer=number-num;
    while(num)
    {
        StringOperation_Buff[0][j]=num%10+'0';
        j++;
        num/=10;
    }
    StringOperation_Buff[0][j]='\0';
    StringReverse(StringOperation_Buff[0]);
    if(pointer)
    StringOperation_Buff[0][j]='.';
    while(pointer)
    {
        pointer*=10;
        num=(int)pointer;
        pointer-=num;
        j++;
        if(j>40)
        {
            break;
        }
        StringOperation_Buff[0][j]=num+'0';
    }
    j++;
    StringOperation_Buff[0][j]='\0';
    return j;//����ע��
}
double DoubleString(char *s)
{
	double result=0;
	double num=0,pointer=0;
	while(*s!='\0')
	{
        if(*s=='.')
        {
            break;
        }
        if(*s-'0'>=0&&*s-'0'<=9)
        {
            num*=10;
            num+=(double)(*s-'0');
        }
        else
        {
            result=0;//TypeError
            return result;
        }
		s++;
	}
	if(HasSymbol('.',s))
    {
        while(*s!='\0')s++;//����β
        s--;//������\0��
        while(*s!='.')
        {
            if(*s-'0'>=0&&*s-'0'<=9)
            {
                pointer/=10;
                pointer+=(double)((*s-'0')/10.0);
            }
            else
            {
                result=0;
                return result;
            }
            s--;
        }
    }
    result=num+pointer;
    return result;
}
char StringDouble(double number)
{
    char j=0;
    int num=(int)number;
    double pointer=number-num;
    while(num)
    {
        StringOperation_Buff[0][j]=num%10+'0';
        j++;
        num/=10;
    }
    StringOperation_Buff[0][j]='\0';
    StringReverse(StringOperation_Buff[0]);
    if(pointer)
    StringOperation_Buff[0][j]='.';
    while(pointer)
    {
        pointer*=10;
        num=(int)pointer;
        pointer-=num;
        if(j>40)
        {
            break;//��ֹԽ��
        }
        j++;
        StringOperation_Buff[0][j]=num+'0';
    }
    j++;
    StringOperation_Buff[0][j]='\0';
    return j;
}

/*

 b=FloatString(arr);
        printf("%f\n",b);
        StringFloat(b);
        a=IntString(arr);
        printf("%d\n",a);
        StringInt(a);
        printf("%s\n",StringOperation_Buff[0]);
		//printf("trans:%f\n",a);
		//printf("%s\n",StringOperation_Buff[0]);
int main()
{
    //int a;
    float b;
    int a;
    char arr[70];
    while(1)
    {
        scanf("%s",arr);
        if(StringEqual("exit",arr))
        {
            break;
        }
        b=DoubleString(arr);
        printf("%lf\n",b);
        StringDouble(b);
        //StringReverse(arr);
        printf("%s\n",StringOperation_Buff[0]);

    }
    return  0;
}
*/




