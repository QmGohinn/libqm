#include"reg51.h"
sbit l1=P2^0;
sbit l2=P2^6;
sbit sw2=P1^7;
sbit sw1=P1^0;
void delay(unsigned int n)
{
	
	unsigned int i=0,j=0;
	
	for(i=0;i<n;i++)
	{
	    for(j=0;j<120;j++);
	}
}  //�������ʱ�����������ʵ��led�Ƶ���˸�����ǳ����Ļ� ���Ե��ô˺�������led�Ƶ���˸


/*void shan1(int a)
{
	int b = 0; 
	int c = 0;
	for(b=0;b<a;b++)
	l1=1;
	delay(5);

}*/
void main()
{
	
	while (sw2 == 1)               {l1 = 1 ;l2 = 1;}
	
	while (sw2 == 0 && sw1 == 0)   {l2 = 0 ;delay(5);l2 = 1;delay(5); l2 = 0 ;l1 = 1;}

  while (sw2 == 0 && sw1 == 1)   {l1 = 0 ;delay(5);l1 = 1;delay(5); l1 = 0 ;l2 = 1;}


}
