#ifndef __STRINGOPERATION_H
#define __STRINGOPERATION_H

/***************************************************************************************************
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

******************************************************************************************************/

/*******************************************������**************************************************/
#define TypeError 0x01







/****************************************************************************************************/
//�������ַ��ж�����
#define IsCharacter(x) ((x>='a'&&x<='z')||(x>='A'&&x<='Z'))
#define IsNum(x)       (x>='0'&&x<='9')
#define IsSign(x)     ((IsNum(x))||(IsCharacter(x))||(x=='_'))
#define IsDefine(x)     (x=='#')
//#define IsBoundStart(x)      (*(x)=='/'&&(*(x++)=='*'||*(x++)=='/'))
//#define IsBoundEnd(x)          (*(x)=='*'&&*(x++)=='/')
#define IsOperator(x)   (x=='+'||x=='-'||x=='*'||x=='/')
//���ڱ�����




void StringBuffEmpty(void);
char GetStringBuffUsedNum(void);
int StringLength(char *s);
char StringTrim(char sysmbol,char *s);
char StringCopy(char *s1,char *s2);
char StringReverse(char *s);
char SplitString(char split,char *s);
char StringEqual(char *s1,char *s2);
char HasSymbol(char symbol,char *s);
int IntString(char *s);
char StringInt(int num);
float FloatString(char *s);
char StringFloat(float number);
double DoubleString(char *s);
char StringDouble(double number);














#endif // __STRINGOPERATION_H


















