#ifndef  __DHT11_H__
#define  __DHT11_H__
/******************************************************************************************************
========================================include head==================================================
******************************************************************************************************/
#include "main.h"

/******************************************************************************************************
========================================Define I/O==================================================
******************************************************************************************************/

//IO��������
#define DHT_W_DATA    PAout(6) //SDA	 
#define DHT_R_DATA    PAin(6)  //SDA 




/* ���� DHT11 ���� */
#define DHT_RCC			RCC_APB2Periph_GPIOA
#define DHT_GPIO		GPIOA
#define DHT_GPIO_PIN	GPIO_Pin_6

/******************************************************************************************************
========================================Define Data==================================================
******************************************************************************************************/
typedef struct _DHT11
{
	char Tem_H;		//�¶���������
	char Tem_L;		//�¶�С������
	char Hum_H;		//ʪ����������
	char Hum_L;		//ʪ��С������
	
}DHT11_TypeDef;
/******************************************************************************************************
========================================��������==================================================
******************************************************************************************************/


/******************************************************************************************************
========================================�Ӻ�������==================================================
******************************************************************************************************/
/**
  * @brief  ��ʼ��IO�ںͲ���
  * @param  none.
  * @retval none.
  */
void DHT11_Init(void);


/**
  * @brief  ��ȡ40bit����
  * @param  none.
  * @retval 1 ��ȡ�ɹ���0��ȡʧ��.
  */
int DHT11_ReadData(void);

/**
  * @brief  ��ȡ�¶�
  * @param  none.
  * @retval Temp, �¶�ֵ���߰�λΪ�������֣��Ͱ�λΪС������
  */
int DHT11_GetTem(void);

/**
  * @brief  ��ȡʪ��
  * @param  none.
  * @retval Hum,ʪ��ֵ,�߰�λΪ�������֣��Ͱ�λΪС������
  */
int DHT11_GetHum(void);
#endif

