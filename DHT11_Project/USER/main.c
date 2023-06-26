#include "main.h"
/****全局变量******************************************/
char lcd_dat1[20];//液晶第一行
char lcd_dat2[20];//液晶第二行
char lcd_dat3[20];//液晶第三行
char lcd_dat4[20];//液晶第四行

uint16_t temp_dat;//温度变量
uint16_t hum_dat;//湿度变量
uint16_t set_temp_dat=27;//设置温度变量
uint16_t set_hum_dat=50;//设置湿度变量
uint8_t setnum;//设置变量

/**********函数申明****************************************/
void ADC1_Init(void);
uint16_t Read_Adc1(uint8_t ch);//通道采样1次
uint16_t light_intensity(uint32_t dat);//光强函数;
void KEY_IO_Init(void);//按键初始化
void EXTIx_Init(void);//外部中断
void Relay_IO_Init(void); //控制继电器引脚io初始化
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
/*****************************************
	main函数
*****************************************/
int main(void){
	uint8_t count_i;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断向量分组 2
	//按键和继电器引脚初始化
	KEY_IO_Init();
	Relay_IO_Init();
	EXTIx_Init();//外部中断初始化
  LCD_init();    //LCD1602初始化
	LCD_clr();//LCD清屏幕
	
	DHT11_Init();//温湿度传感器初始化
	
	ADC1_Init();//adc采样初始化 用于ad类型传感器
	
	
	
	while(1){	
		count_i++;
		//if(count_i>50)
		{
			//传感器数据采集
			if(DHT11_ReadData())//温湿度采集
			{
				temp_dat=DHT11_GetTem();
				temp_dat=temp_dat/256;
				delay_ms(10);
				hum_dat=DHT11_GetHum();
				hum_dat=hum_dat/256;
			}

					//液晶显示：T温度  H湿度，
			sprintf(lcd_dat1,"T:%d    H:%d \n",temp_dat,hum_dat);//转换温度，湿度
			LCD_prints(0,0,lcd_dat1);//液晶显示第一行
			if(setnum==0)
			{
				sprintf(lcd_dat2,"  %d   %d   \n",set_temp_dat,set_hum_dat);///转换设置温度，设置湿度
				LCD_prints(0,1,lcd_dat2);//液晶显示第二行
			}
				if(setnum	== 1)
			{
				sprintf(lcd_dat2,"  %d^  %d  \n",set_temp_dat,set_hum_dat);///转换设置温度，设置湿度
				LCD_prints(0,1,lcd_dat2);//液晶显示第二行
			}
			if(setnum	== 2)
			{
				sprintf(lcd_dat2,"  %d   %d^  \n",set_temp_dat,set_hum_dat);///转换设置温度，设置湿度
				LCD_prints(0,1,lcd_dat2);//液晶显示第二行
			}
			if(setnum	== 3)
			{
				sprintf(lcd_dat2,"  %d   %d   ^\n",set_temp_dat,set_hum_dat);///转换设置温度，设置湿度
				LCD_prints(0,1,lcd_dat2);//液晶显示第二行
			}
			sprintf(lcd_dat3,"");//内容
			LCD_prints(0,2,lcd_dat3);//液晶显示第三行
			
			sprintf(lcd_dat4,"");//姓名
			LCD_prints(0,3,lcd_dat4);//液晶显示第四行
		}
		if(temp_dat>set_temp_dat)//比较温度
			Relay1=1;
		else
			Relay1=0;
		if(hum_dat<set_hum_dat)//比较湿度
			Relay2=1;
		else
			Relay2=0;	
	}

}



void KEY_IO_Init(void)//按键初始化
{
   GPIO_InitTypeDef  GPIO_InitStructure;
 	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;				 //按键输入端口配置
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		
   GPIO_Init(GPIOB, &GPIO_InitStructure);	
}	
void EXTIx_Init(void)//外部中断
{
	NVIC_InitTypeDef NVIC_InitStructure;  //NVIC寄存器结构体变量
	EXTI_InitTypeDef EXTI_InitStructure;  //外部中断相关寄存器结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //使能IO复用功能时钟
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0); //
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1); //
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2); //
	
	//配置外部中断4相关寄存器
	EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1|EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&EXTI_InitStructure);
	
	//中断通道使能
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//使能外部中断通道0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //设置抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//设置响应优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
		//中断通道使能
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//使能外部中断通道1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //设置抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//设置响应优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
		//中断通道使能
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//使能外部中断通道2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //设置抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//设置响应优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	
}

void EXTI0_IRQHandler(void)
{
	setnum++;
	if(setnum	> 3)//按下次数超过3次，退出设置
	{
		setnum=0;
	}	

	EXTI_ClearITPendingBit(EXTI_Line4);//清除中断挂起标志位
}
void EXTI1_IRQHandler(void)
{
	if(setnum	== 1)
	{
		if(set_temp_dat<100)
		set_temp_dat++;
	}
	if(setnum	== 2)
	{
		if(set_hum_dat<100)
		set_hum_dat++;
	}	
	EXTI_ClearITPendingBit(EXTI_Line4);//清除中断挂起标志位
}
void EXTI2_IRQHandler(void)
{
	if(setnum	== 1)
	{
		if(set_temp_dat>0)
		set_temp_dat--;
	}
	if(setnum	== 2)
	{
		if(set_hum_dat>0)
		set_hum_dat--;
	}	
	EXTI_ClearITPendingBit(EXTI_Line4);//清除中断挂起标志位
}

void Relay_IO_Init(void) //控制继电器引脚io初始化
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;				 // 端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);	
	 GPIO_ResetBits(GPIOB,GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9); 						 //PB.789 输出低
}	


void ADC1_Init(void)//ADC初始化  单通道 单次转换。
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //配置模拟输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; //GPIOA.23
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目1
	ADC_Init(ADC1,&ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //  72/6

	ADC_Cmd(ADC1,ENABLE);//adc使能
		
	//adc校准，每次开启使用ADC都校准
	ADC_ResetCalibration(ADC1);	//使能复位校准 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
	//while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	ADC_StartCalibration(ADC1);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
}

uint16_t Read_Adc1(uint8_t ch)//通道采样1次
{
  	//设置指定ADC的规则组通道，一个序列，采样时间(ADCX_SMPRX) 
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
		//ADC1->CR2 |= 5<<20;
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
