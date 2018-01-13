/**************************************************************************************
* 
* 文件描述：定义通用类型，方便移植
*
* 作者：王庆路
* 建立日期：2018.01.12
* 版本：1.0
*
* 历史记录：
* - 1.0 建立by 王庆路(2018.01.12)
*  
**************************************************************************************/
#ifndef _DEF_H
#define _DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <wiringPi.h>

#define true                (1)
#define false               (0)
#define ENABLE              (1)
#define DISABLED            (0)
//树莓派gpio口对应位
//LCD12864 控制
#define LCD_RS              (0)
#define LCD_RW              (2)
#define LCD_EN              (3)
//LCD12864 数据
#define D1                  (21)
#define D2                  (22)
#define D3                  (23)
#define D4                  (24)
#define D5                  (25)
#define D6                  (26)
#define D7                  (27)
#define D8                  (28)
//函数更名
#define delay_ms            delay
#define delay_us            delayMicroseconds
//arm 编译器 32位
typedef unsigned int        u32;
typedef unsigned short      u16;
typedef unsigned char       u8;

typedef signed int          s32;
typedef signed short        s16;
typedef signed char         s8;

typedef float               fp32;
typedef double              fp64;

#ifdef __cplusplus
}
#endif

#endif