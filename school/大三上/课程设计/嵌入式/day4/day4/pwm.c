#define TCNTB0   (*(volatile unsigned int *)0X139D000C)  
//  ============= 100   timer0 �ļ����Ĵ�����   �����timer 0�Ĺ���ʱ��Ӧ����40k


#define TCMPB0   (*(volatile unsigned int *)0X139D0010)  
//================70     timer0 �ıȽϼĴ���


#define TCFG0   (*(volatile unsigned int *)0X139D0000)  
//BIT7---BIT0 ���Ƶľ���timer0 ��һ����Ƶ
//=================155    


#define TCFG1   (*(volatile unsigned int *)0X139D0004)
//bit3---bit0  ========== 4��    timer0 �Ķ�����Ƶ Ϊ 16
//������Ƶ֮ǰʱ��Ӧ���� 40k * 16   =========640k


#define TCON   (*(volatile unsigned int *)0X139D0008)
//bit3==1,  ����������� 
//bit2==0,  ������岻��ת 
//bit1 =====1,   ����TCMPB0�� TCNTB0   ��   ��������ʱ���� bit1===0
//bit0==1, ������ʱ���� �������            bit0===0�� ֹͣ��ʱ���� �����



//��GPD0_0  ���ó�TOUT_0  ,         TIMER0  �����
#define GPD0CON   (*(volatile unsigned int *)0X114000A0)
//BIT3--BIT0==2,   ����gpd0_0  Ϊtimer0 �����


void pwm_init()
{
		GPD0CON = GPD0CON & ~0xf  | 2;
		TCFG0 = TCFG0 & ~(0xff);
		TCFG0 = TCFG0 | 155;
		TCFG1 = TCFG1 & ~(0xf);
		TCFG1 = TCFG1 | 4;
		
		TCNTB0 = 100;
		TCMPB0 = 70;
		
		TCON = TCON | (1<<3);
		TCON = TCON & ~(1<<2);
		TCON = TCON | (1<<1);

		TCON = TCON & ~(1<<1);
}
void pwm_start()
{
				TCON = TCON | (1<<0);

}

void pwm_stop()
{
			TCON = TCON & ~(1<<0);

}

