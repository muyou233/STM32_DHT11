
#include "main.h"


void LCD1602_PORT_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx,ENABLE);	 //使能PC端口时钟	
	GPIO_InitStructure.GPIO_Pin = GPIOx_Pin;				               //端口配置 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		         //IO口速度为10MHz
  GPIO_Init(GPIOx, &GPIO_InitStructure);					               //根据设定参数初始化
}



void delay_nus(uint16_t n)//微妙级延时，通常情况此函数可以不用更改
{
  uint16_t i;
  while(n--)
  {
    i=20;
    while(i--);
  }
}




void delay_nms(uint16_t n) //毫秒级延时，保通常情况此函数可以不用更改
{
    while(n--)
      delay_nus(1100);
}

void LCD_init(void) //初始化,通常情况此函数可以不用更改
{
		LCD1602_PORT_Init(); //LCD 1602使用的PC口初始化
    LCD_RS_0;
    LCD_RW_0; 
    LCD_EN_0; 

    delay_nms(5);
    LCD_cmd(0x38);//16*2显示,5*7点阵,8数据
    delay_nms(1);
    LCD_cmd(0x38);//16*2显示,5*7点阵,8数据
    delay_nms(1);
    LCD_cmd(0x38);//16*2显示,5*7点阵,8数据
    delay_nms(1);
    LCD_cmd(0x08);//先关显示，后开显示
    delay_nms(1);
    LCD_cmd(0x01);//清屏
    delay_nms(1);
    LCD_cmd(0x06);//写命令，注意
    delay_nms(1);   
    LCD_cmd(0x0c);//显示开，关光标
    delay_nms(1);
}

void LCD_clr(void)  //清屏
{
    LCD_cmd(0x01);
}

void LCD_cmd(uint16_t cmd)//写命令
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

void LCD_dat(uint8_t dat)//写数据
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

//写字符串

 void LCD_Write_String(uint8_t x,uint8_t y,uint8_t *s) 
{     
  if (y == 0) 
 	{     
	   LCD_cmd(0x80 + x);     //第一行
 	}
                 else if(y == 1)
 	{      
 	   LCD_cmd(0xC0 + x);      //第二行
 	} 
								 else	if(y == 2)
 	{      
 	   LCD_cmd(0x94 + x);      //第三行
 	} 
   							 else
 	{      
 	   LCD_cmd(0xD4 + x);      //第四行
 	}                
                  
                 while (*s) 
 	{     
                     LCD_dat( *s);     
                      s ++;     
 	}
 }
//写字符

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



void LCD_pos(uint16_t x,uint16_t y)//显示位置
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

void LCD_printc(uint16_t x,uint16_t y,uint8_t c)//显示字符
{
    LCD_pos(x,y);
    LCD_dat(c);
}

void LCD_prints(uint16_t x,uint16_t y,char *s)//显示字符串
{
    LCD_pos(x,y);
    while(*s!='\0')
    {
        LCD_dat(*s);
        s++;
        //delay_nms(1);
    }
}
