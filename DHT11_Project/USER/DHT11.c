
/**************************************************************************************************
========================================Include Head===============================================
***************************************************************************************************/
#include "DHT11.h"
/**************************************************************************************************
========================================Program Start===============================================
***************************************************************************************************/


#define DHT_SetBit()	GPIO_SetBits(DHT_GPIO, DHT_GPIO_PIN)
#define DHT_ResetBit()	GPIO_ResetBits(DHT_GPIO, DHT_GPIO_PIN)
#define DHT_ReadBit()	GPIO_ReadInputDataBit(DHT_GPIO, DHT_GPIO_PIN)

static void DHT_Set_Output(void);			//设置为输出模式
static void DHT_Set_Input(void);			//设置为输入模式

DHT11_TypeDef DHT11;					      	//全局变量
/**************************************************************************************************
========================================DHT11 START===============================================
***************************************************************************************************/
/*******************************************************************************
* Function Name : DHT11_Init
* Description : 湿度传感器IO初始化
* Input : None
* Output : None
* Return : None
*******************************************************************************/
void DHT_Set_Output(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DHT_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(DHT_GPIO, &GPIO_InitStructure);		
	
}
void DHT_Set_Input(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DHT_GPIO_PIN;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(DHT_GPIO, &GPIO_InitStructure);	
	
}
void DHT11_Init(void)
{
	  //GPIO_InitTypeDef  GPIO_InitStructure;
 	
	 	RCC_APB2PeriphClockCmd(DHT_RCC, ENABLE);	 //使能端口时钟	
		DHT_Set_Output();
	 	DHT11.Tem_H = 0;
		DHT11.Tem_L = 0;
		DHT11.Hum_H = 0;
		DHT11.Hum_L = 0;
	
	 	//DHT_W_DATA=1;
	 		
}
/*******************************************************************************
* Function Name :  DHT11_Byte
* Description : 读取温湿度一个字节
* Input : None
* Output : None
* Return : None
*******************************************************************************/
int DH21_ReadByte(void)
{
	int data=0;
	char i;
	char cout;
	
	for(i=0; i<8; i++)
	{
		//读取50us的低电平
		cout=1;
		while(!DHT_ReadBit() && cout++);
		
		//延时30us之后读取IO口的状态
		delay_us(24);
		
		//先把上次的数据移位，再保存本次的数据位
		data = data << 1;
		
		if(DHT_ReadBit() == Bit_SET)
		{	
			data |= 1;
		}		
		
		//等待输入的是低电平，进入下一位数据接收
		cout=1;
		while(DHT_ReadBit() && cout++);
	}
	return data;
}
/*******************************************************************************
* Function Name :  DHT11_Read
* Description : 读取温湿度
* Input : None
* Output : None
* Return : None
*******************************************************************************/
int DHT11_ReadData(void)
{
	unsigned int cout = 1;
	unsigned int T_H, T_L, H_H, H_L, Check;

	//设置为IO口输出模式
	DHT_Set_Output();
	DHT_W_DATA=1;
	//1、MCU开始起始信号
	DHT_ResetBit();
	delay_ms(18);		//拉低至少18ms
	DHT_SetBit();		
	//delay_us(20);		//拉高20~40us
	
	//设置为IO口输入模式
	DHT_Set_Input();
	
	//2、读取DH21响应
	if(DHT_ReadBit() == Bit_RESET)
	{
		//等待80us的高电平
		cout = 1;
		while(DHT_ReadBit() && cout++);
		
		//等待80us的低电平
		cout = 1;
		while(!DHT_ReadBit() && cout++);
		delay_us(54);
		
		//读取8bit的湿度整数数据
		H_H = DH21_ReadByte();
		
		//读取8bit的湿度小数数据
		H_L = DH21_ReadByte();
		
		//读取8bit的温度整数数据
		T_H = DH21_ReadByte();
		
		//读取8bit的温度小数数据
		T_L = DH21_ReadByte();
		
		//读取8bit的校验和
		Check = DH21_ReadByte();
		
		if(Check == (H_H + H_L + T_H + T_L))
		{
			DHT11.Hum_H = H_H;
			DHT11.Hum_L = H_L;
			DHT11.Tem_H = T_H;
			DHT11.Tem_L = T_L;	
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

/**
  * @brief  获取温度
  * @param  none.
  * @retval Temp, 温度值
  */
int DHT11_GetTem(void)
{
	return (DHT11.Tem_H << 8 | DHT11.Tem_L);
}

/**
  * @brief  获取湿度
  * @param  none.
  * @retval Hum,湿度值
  */
int DHT11_GetHum(void)
{
	return (DHT11.Hum_H << 8 | DHT11.Hum_L);
}

/**************************************************************************************************
========================================DHT11 END===============================================
***************************************************************************************************/
/******************* (C)***Program End************文件结束*****************************************/

