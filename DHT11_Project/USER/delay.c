#include "delay.h"

//#define PRESCALER_US	1e6
//#define PRESCALER_MS	1e3	


//void delay_us(uint32_t us)
//{
//		uint32_t temp,temp1;		   
//	SysTick->LOAD=(uint32_t)us*(SystemCoreClock/PRESCALER_US);				//ʱ�����(SysTick->LOADΪ24bit)
//	SysTick->VAL =0x00;							//��ռ�����
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
//	temp1=SysTick->VAL;
//	do
//	{
//		temp=SysTick->CTRL;

//	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
//	SysTick->VAL =0X00;       					//��ռ�����	  
//}


//void delay_ms(int32_t ms){
//		uint32_t temp,temp1;		   
//	SysTick->LOAD=(uint32_t)ms*(SystemCoreClock/PRESCALER_MS);				//ʱ�����(SysTick->LOADΪ24bit)
//	SysTick->VAL =0x00;							//��ռ�����
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
//	temp1=SysTick->VAL;
//	do
//	{
//		temp=SysTick->CTRL;

//	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
//	SysTick->VAL =0X00;       					//��ռ�����	  
//}

void delay_us(uint32_t time) //3.5us+1.5us*��time-1��
{     
	time=2*time;
    while(time--)
			 ;  
}
//���뼶����ʱ
void delay_ms(int32_t time)
{    
   u16 i=0;  
   while(time--)
   {
      i=1000;  //�Լ�����
      while(i--) ;    
   }
}


