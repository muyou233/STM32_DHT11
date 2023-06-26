
#include "main.h"


void LCD1602_PORT_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx,ENABLE);	 //ʹ��PC�˿�ʱ��	
	GPIO_InitStructure.GPIO_Pin = GPIOx_Pin;				               //�˿����� 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		         //IO���ٶ�Ϊ10MHz
  GPIO_Init(GPIOx, &GPIO_InitStructure);					               //�����趨������ʼ��
}



void delay_nus(uint16_t n)//΢���ʱ��ͨ������˺������Բ��ø���
{
  uint16_t i;
  while(n--)
  {
    i=20;
    while(i--);
  }
}




void delay_nms(uint16_t n) //���뼶��ʱ����ͨ������˺������Բ��ø���
{
    while(n--)
      delay_nus(1100);
}

void LCD_init(void) //��ʼ��,ͨ������˺������Բ��ø���
{
		LCD1602_PORT_Init(); //LCD 1602ʹ�õ�PC�ڳ�ʼ��
    LCD_RS_0;
    LCD_RW_0; 
    LCD_EN_0; 

    delay_nms(5);
    LCD_cmd(0x38);//16*2��ʾ,5*7����,8����
    delay_nms(1);
    LCD_cmd(0x38);//16*2��ʾ,5*7����,8����
    delay_nms(1);
    LCD_cmd(0x38);//16*2��ʾ,5*7����,8����
    delay_nms(1);
    LCD_cmd(0x08);//�ȹ���ʾ������ʾ
    delay_nms(1);
    LCD_cmd(0x01);//����
    delay_nms(1);
    LCD_cmd(0x06);//д���ע��
    delay_nms(1);   
    LCD_cmd(0x0c);//��ʾ�����ع��
    delay_nms(1);
}

void LCD_clr(void)  //����
{
    LCD_cmd(0x01);
}

void LCD_cmd(uint16_t cmd)//д����
{   
		LCD_RS_0;        
		delay_nus(1);   
		LCD_RW_0;     
		delay_nus(1);   
		LCD_EN_0;      
		delay_nus(1);
		GPIO_SetBits(LCDPORT, LCD_DATA_PORT & cmd);
		GPIO_ResetBits(LCDPORT, LCD_DATA_PORT &(~cmd));
		LCD_EN_1;
		delay_nus(1);    
		LCD_EN_0;     
}

void LCD_dat(uint8_t dat)//д����
{
    delay_nms(1);   
    LCD_RS_1;
    delay_nus(1);  		 
    LCD_RW_0;       	       
    delay_nus(1);
    LCD_EN_0;                  
    delay_nus(1);
		GPIO_SetBits(LCDPORT, LCD_DATA_PORT & dat);
		GPIO_ResetBits(LCDPORT, LCD_DATA_PORT &(~dat));

    LCD_EN_1;       	   
    delay_nus(1);   
    LCD_EN_0;       	 
}

//д�ַ���

 void LCD_Write_String(uint8_t x,uint8_t y,uint8_t *s) 
{     
  if (y == 0) 
 	{     
	   LCD_cmd(0x80 + x);     //��һ��
 	}
                 else if(y == 1)
 	{      
 	   LCD_cmd(0xC0 + x);      //�ڶ���
 	} 
								 else	if(y == 2)
 	{      
 	   LCD_cmd(0x94 + x);      //������
 	} 
   							 else
 	{      
 	   LCD_cmd(0xD4 + x);      //������
 	}                
                  
                 while (*s) 
 	{     
                     LCD_dat( *s);     
                      s ++;     
 	}
 }
//д�ַ�

void LCD_Write_Char(uint8_t x,uint8_t y,uint8_t Data) 
{     
                  if (y == 0) 
 	{     
											LCD_cmd(0x80 + x);     
 	}    
                  else if(y == 1)
 	{     
											LCD_cmd(0xC0 + x);     
 	}
                  else if(y == 2)
 	{     
											LCD_cmd(0x94 + x);     
 	}       
									else 
 	{     
											LCD_cmd(0xD4 + x);     
 	}        	 	
                    LCD_dat( Data);  
}



void LCD_pos(uint16_t x,uint16_t y)//��ʾλ��
{
     if(y == 0)
     LCD_cmd(x | 0xC0);
   	 else if(y == 1)
     LCD_cmd(x | 0x80);
		 else if(y == 2)
     LCD_cmd(x | 0x94);
		 else
		 LCD_cmd(x | 0xD4);
}

void LCD_printc(uint16_t x,uint16_t y,uint8_t c)//��ʾ�ַ�
{
    LCD_pos(x,y);
    LCD_dat(c);
}

void LCD_prints(uint16_t x,uint16_t y,char *s)//��ʾ�ַ���
{
    LCD_pos(x,y);
    while(*s!='\0')
    {
        LCD_dat(*s);
        s++;
        //delay_nms(1);
    }
}
