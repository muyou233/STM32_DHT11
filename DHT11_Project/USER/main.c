#include "main.h"
/****ȫ�ֱ���******************************************/
char lcd_dat1[20];//Һ����һ��
char lcd_dat2[20];//Һ���ڶ���
char lcd_dat3[20];//Һ��������
char lcd_dat4[20];//Һ��������

uint16_t temp_dat;//�¶ȱ���
uint16_t hum_dat;//ʪ�ȱ���
uint16_t set_temp_dat=27;//�����¶ȱ���
uint16_t set_hum_dat=50;//����ʪ�ȱ���
uint8_t setnum;//���ñ���

/**********��������****************************************/
void ADC1_Init(void);
uint16_t Read_Adc1(uint8_t ch);//ͨ������1��
uint16_t light_intensity(uint32_t dat);//��ǿ����;
void KEY_IO_Init(void);//������ʼ��
void EXTIx_Init(void);//�ⲿ�ж�
void Relay_IO_Init(void); //���Ƽ̵�������io��ʼ��
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
/*****************************************
	main����
*****************************************/
int main(void){
	uint8_t count_i;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�ж��������� 2
	//�����ͼ̵������ų�ʼ��
	KEY_IO_Init();
	Relay_IO_Init();
	EXTIx_Init();//�ⲿ�жϳ�ʼ��
  LCD_init();    //LCD1602��ʼ��
	LCD_clr();//LCD����Ļ
	
	DHT11_Init();//��ʪ�ȴ�������ʼ��
	
	ADC1_Init();//adc������ʼ�� ����ad���ʹ�����
	
	
	
	while(1){	
		count_i++;
		//if(count_i>50)
		{
			//���������ݲɼ�
			if(DHT11_ReadData())//��ʪ�Ȳɼ�
			{
				temp_dat=DHT11_GetTem();
				temp_dat=temp_dat/256;
				delay_ms(10);
				hum_dat=DHT11_GetHum();
				hum_dat=hum_dat/256;
			}

					//Һ����ʾ��T�¶�  Hʪ�ȣ�
			sprintf(lcd_dat1,"T:%d    H:%d \n",temp_dat,hum_dat);//ת���¶ȣ�ʪ��
			LCD_prints(0,0,lcd_dat1);//Һ����ʾ��һ��
			if(setnum==0)
			{
				sprintf(lcd_dat2,"  %d   %d   \n",set_temp_dat,set_hum_dat);///ת�������¶ȣ�����ʪ��
				LCD_prints(0,1,lcd_dat2);//Һ����ʾ�ڶ���
			}
				if(setnum	== 1)
			{
				sprintf(lcd_dat2,"  %d^  %d  \n",set_temp_dat,set_hum_dat);///ת�������¶ȣ�����ʪ��
				LCD_prints(0,1,lcd_dat2);//Һ����ʾ�ڶ���
			}
			if(setnum	== 2)
			{
				sprintf(lcd_dat2,"  %d   %d^  \n",set_temp_dat,set_hum_dat);///ת�������¶ȣ�����ʪ��
				LCD_prints(0,1,lcd_dat2);//Һ����ʾ�ڶ���
			}
			if(setnum	== 3)
			{
				sprintf(lcd_dat2,"  %d   %d   ^\n",set_temp_dat,set_hum_dat);///ת�������¶ȣ�����ʪ��
				LCD_prints(0,1,lcd_dat2);//Һ����ʾ�ڶ���
			}
			sprintf(lcd_dat3,"");//����
			LCD_prints(0,2,lcd_dat3);//Һ����ʾ������
			
			sprintf(lcd_dat4,"");//����
			LCD_prints(0,3,lcd_dat4);//Һ����ʾ������
		}
		if(temp_dat>set_temp_dat)//�Ƚ��¶�
			Relay1=1;
		else
			Relay1=0;
		if(hum_dat<set_hum_dat)//�Ƚ�ʪ��
			Relay2=1;
		else
			Relay2=0;	
	}

}



void KEY_IO_Init(void)//������ʼ��
{
   GPIO_InitTypeDef  GPIO_InitStructure;
 	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;				 //��������˿�����
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		
   GPIO_Init(GPIOB, &GPIO_InitStructure);	
}	
void EXTIx_Init(void)//�ⲿ�ж�
{
	NVIC_InitTypeDef NVIC_InitStructure;  //NVIC�Ĵ����ṹ�����
	EXTI_InitTypeDef EXTI_InitStructure;  //�ⲿ�ж���ؼĴ����ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); //ʹ��IO���ù���ʱ��
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0); //
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1); //
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2); //
	
	//�����ⲿ�ж�4��ؼĴ���
	EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1|EXTI_Line2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	
	EXTI_Init(&EXTI_InitStructure);
	
	//�ж�ͨ��ʹ��
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//ʹ���ⲿ�ж�ͨ��0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //������ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//������Ӧ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
		//�ж�ͨ��ʹ��
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//ʹ���ⲿ�ж�ͨ��1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //������ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//������Ӧ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
		//�ж�ͨ��ʹ��
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//ʹ���ⲿ�ж�ͨ��2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //������ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;//������Ӧ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
	
}

void EXTI0_IRQHandler(void)
{
	setnum++;
	if(setnum	> 3)//���´�������3�Σ��˳�����
	{
		setnum=0;
	}	

	EXTI_ClearITPendingBit(EXTI_Line4);//����жϹ����־λ
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
	EXTI_ClearITPendingBit(EXTI_Line4);//����жϹ����־λ
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
	EXTI_ClearITPendingBit(EXTI_Line4);//����жϹ����־λ
}

void Relay_IO_Init(void) //���Ƽ̵�������io��ʼ��
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;				 // �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);	
	 GPIO_ResetBits(GPIOB,GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9); 						 //PB.789 �����
}	


void ADC1_Init(void)//ADC��ʼ��  ��ͨ�� ����ת����
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOA,ENABLE);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; //����ģ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; //GPIOA.23
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	ADC_DeInit(ADC1);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ1
	ADC_Init(ADC1,&ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //  72/6

	ADC_Cmd(ADC1,ENABLE);//adcʹ��
		
	//adcУ׼��ÿ�ο���ʹ��ADC��У׼
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼ 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	//while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
}

uint16_t Read_Adc1(uint8_t ch)//ͨ������1��
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��(ADCX_SMPRX) 
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
		//ADC1->CR2 |= 5<<20;
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}
