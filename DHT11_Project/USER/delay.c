#include "delay.h"

//#define PRESCALER_US	1e6
//#define PRESCALER_MS	1e3	


//void delay_us(uint32_t us)
//{
//		uint32_t temp,temp1;		   
//	SysTick->LOAD=(uint32_t)us*(SystemCoreClock/PRESCALER_US);				//时间加载(SysTick->LOAD为24bit)
//	SysTick->VAL =0x00;							//清空计数器
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
//	temp1=SysTick->VAL;
//	do
//	{
//		temp=SysTick->CTRL;

//	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
//	SysTick->VAL =0X00;       					//清空计数器	  
//}


//void delay_ms(int32_t ms){
//		uint32_t temp,temp1;		   
//	SysTick->LOAD=(uint32_t)ms*(SystemCoreClock/PRESCALER_MS);				//时间加载(SysTick->LOAD为24bit)
//	SysTick->VAL =0x00;							//清空计数器
//	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
//	temp1=SysTick->VAL;
//	do
//	{
//		temp=SysTick->CTRL;

//	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
//	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
//	SysTick->VAL =0X00;       					//清空计数器	  
//}

void delay_us(uint32_t time) //3.5us+1.5us*（time-1）
{     
	time=2*time;
    while(time--)
			 ;  
}
//毫秒级的延时
void delay_ms(int32_t time)
{    
   u16 i=0;  
   while(time--)
   {
      i=1000;  //自己定义
      while(i--) ;    
   }
}


