#ifndef __LCD1602_H
#define __LCD1602_H

#include "main.h"

/***********¶Ë¿Ú¶¨Òå**********************************************************/
/*#define rs  GPIOSetValue(PORT2,0,rs)
#define rw  GPIOSetValue(PORT2,1,rw)
#define e   GPIOSetValue(PORT2,2,e)
*/

#define  LCDPORT         GPIOC


#define  RS_PIN          GPIO_Pin_8
#define  RW_PIN          GPIO_Pin_9
#define  EN_PIN          GPIO_Pin_10

#define GPIOx            GPIOC 
#define RCC_APB2Periph_GPIOx            RCC_APB2Periph_GPIOC 
#define GPIOx_Pin        GPIO_Pin_All 
#define LCD_DATA_PORT    0xff



#define LCD_RS_1 GPIO_SetBits(LCDPORT, RS_PIN) 		
#define LCD_RS_0 GPIO_ResetBits(LCDPORT, RS_PIN)
#define LCD_RW_1 GPIO_SetBits(LCDPORT, RW_PIN)		
#define LCD_RW_0 GPIO_ResetBits(LCDPORT, RW_PIN)
#define LCD_EN_1 GPIO_SetBits(LCDPORT, EN_PIN)	
#define LCD_EN_0 GPIO_ResetBits(LCDPORT, EN_PIN)






void LCD1602_PORT_Init(void);

void LCD_init(void);			        
void LCD_clr(void);			        
void LCD_cmd(uint16_t cmd);		        
void LCD_dat(uint8_t dat);		        
void LCD_pos(uint16_t x,uint16_t y);	
void LCD_Write_Char(uint8_t x,uint8_t y,uint8_t Data) ;
void LCD_printc(uint16_t x,uint16_t y,uint8_t c);	
void LCD_prints(uint16_t x,uint16_t y,char *s);	
extern void delay_nus(uint16_t us);	        
extern void delay_nms(uint16_t ms);	  

 void LCD_Write_String(uint8_t x,uint8_t y,uint8_t *s) ;
#endif
