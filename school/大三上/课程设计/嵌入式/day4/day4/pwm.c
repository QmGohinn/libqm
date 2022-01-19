#define TCNTB0   (*(volatile unsigned int *)0X139D000C)  
//  ============= 100   timer0 的计数寄存器，   推算出timer 0的工作时钟应该是40k


#define TCMPB0   (*(volatile unsigned int *)0X139D0010)  
//================70     timer0 的比较寄存器


#define TCFG0   (*(volatile unsigned int *)0X139D0000)  
//BIT7---BIT0 控制的就是timer0 的一级分频
//=================155    


#define TCFG1   (*(volatile unsigned int *)0X139D0004)
//bit3---bit0  ========== 4，    timer0 的二级分频 为 16
//二级分频之前时钟应该是 40k * 16   =========640k


#define TCON   (*(volatile unsigned int *)0X139D0008)
//bit3==1,  输出连续脉冲 
//bit2==0,  输出脉冲不翻转 
//bit1 =====1,   更新TCMPB0， TCNTB0   ，   在启动定时器后， bit1===0
//bit0==1, 启动定时器， 输出脉冲            bit0===0， 停止定时器， 不输出



//把GPD0_0  配置成TOUT_0  ,         TIMER0  的输出
#define GPD0CON   (*(volatile unsigned int *)0X114000A0)
//BIT3--BIT0==2,   配置gpd0_0  为timer0 的输出


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

