#ifndef __MAIN_H
#define __MAIN_H



#include <stm32f10x.h>
#include "stdint.h"
#include "stdio.h"
#include "stm32f10x_conf.h"

#include "delay.h"
#include "stm32f10x_it.h"
#include "sys.h"
#include "LCD1602.h"
#include "DHT11.H"

#define 	KEY1 PBin(0)
#define 	KEY2 PBin(1)
#define 	KEY3 PBin(2)

#define 	Relay1 PBout(7)    //
#define 	Relay2 PBout(8)      //
#define 	Relay3 PBout(9)      //
#define 	buzzer PBout(10)      //
#endif      


