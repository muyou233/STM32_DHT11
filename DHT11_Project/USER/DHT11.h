#ifndef  __DHT11_H__
#define  __DHT11_H__
/******************************************************************************************************
========================================include head==================================================
******************************************************************************************************/
#include "main.h"

/******************************************************************************************************
========================================Define I/O==================================================
******************************************************************************************************/

//IO操作函数
#define DHT_W_DATA    PAout(6) //SDA	 
#define DHT_R_DATA    PAin(6)  //SDA 




/* 定义 DHT11 引脚 */
#define DHT_RCC			RCC_APB2Periph_GPIOA
#define DHT_GPIO		GPIOA
#define DHT_GPIO_PIN	GPIO_Pin_6

/******************************************************************************************************
========================================Define Data==================================================
******************************************************************************************************/
typedef struct _DHT11
{
	char Tem_H;		//温度整数部分
	char Tem_L;		//温度小数部分
	char Hum_H;		//湿度整数部分
	char Hum_L;		//湿度小数部分
	
}DHT11_TypeDef;
/******************************************************************************************************
========================================变量定义==================================================
******************************************************************************************************/


/******************************************************************************************************
========================================子函数声明==================================================
******************************************************************************************************/
/**
  * @brief  初始化IO口和参数
  * @param  none.
  * @retval none.
  */
void DHT11_Init(void);


/**
  * @brief  读取40bit数据
  * @param  none.
  * @retval 1 读取成功，0读取失败.
  */
int DHT11_ReadData(void);

/**
  * @brief  获取温度
  * @param  none.
  * @retval Temp, 温度值，高八位为整数部分，低八位为小数部分
  */
int DHT11_GetTem(void);

/**
  * @brief  获取湿度
  * @param  none.
  * @retval Hum,湿度值,高八位为整数部分，低八位为小数部分
  */
int DHT11_GetHum(void);
#endif


