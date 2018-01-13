/**************************************************************************************
* 
* 文件描述：调用各个模块功能，实现LCD12864显示字符
*
* 作者：王庆路
* 建立日期：2018.01.12
* 版本：1.0
*
* 历史记录：
* - 1.0 建立by 王庆路(2018.01.12)
*  
**************************************************************************************/
#include "def.h"

u32 hehehe = 0;
u8 teststr[] = {
    0x00,0x00,0x00,0x60,0x60,0x7C,0x66,0x66,0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x3C,0x66,0x66,0x7E,0x60,0x60,0x3C,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x3C,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x1C,0x0C,0x18,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x63,0x6B,0x6B,0x6B,0x6B,0x36,0x36,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x3E,0x66,0x66,0x66,0x66,0x66,0x3E,0x06,0x06,0x06,0x00,
    0x00,0x00,0x00,0x78,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x7E,0x00,0x00,0x00,0x00
};
void BusWrite(u8 data){
    int t[10],i;
    for(i = 0; i < 8; i++){
        t[i] = data % 2;
        data /= 2;
    }
    digitalWrite(D1,t[0]);
    digitalWrite(D2,t[1]);
    digitalWrite(D3,t[2]);
    digitalWrite(D4,t[3]);
    digitalWrite(D5,t[4]);
    digitalWrite(D6,t[5]);
    digitalWrite(D7,t[6]);
    digitalWrite(D8,t[7]);
}
void ChkBusy(){
        u8 a;
        digitalWrite(LCD_RS,DISABLED);
        digitalWrite(LCD_RW,ENABLE);
        digitalWrite(LCD_EN,DISABLED);
        BusWrite(0xff);
        digitalWrite(LCD_EN,ENABLE);
        pinMode(D8, INPUT);
        while(1){
            digitalWrite(LCD_EN,DISABLED);
            if(digitalRead(D8)==0){
                break;//lcd12864不忙时D8为低电平
            }
            digitalWrite(LCD_EN,ENABLE);
            a++;
            if(a>10){
                break;//防止陷入死循环
            }
        }
        pinMode(D8, OUTPUT);
}
void WriteCmd(u8 cmdCode){
    ChkBusy();
    digitalWrite(LCD_RS,DISABLED);
    digitalWrite(LCD_RW,DISABLED);
    digitalWrite(LCD_EN,ENABLE);
    BusWrite(cmdCode);
    digitalWrite(LCD_EN,DISABLED);
    delay_us(1);
}
void WriteData(u8 dispData){
    ChkBusy();
    digitalWrite(LCD_RS,ENABLE);
    digitalWrite(LCD_RW,DISABLED);
    digitalWrite(LCD_EN,ENABLE);
    BusWrite(dispData);
    digitalWrite(LCD_EN,DISABLED);
    delay_us(1);
}
void WriteWord(u8 pos,unsigned char* data){
    WriteCmd(pos);
    //while(*data >= 0){
    //    WriteData(*data);
    //    data++;
    //}
    WriteData(teststr[0]);
    WriteData(teststr[1]);
    WriteData(teststr[2]);
    WriteData(teststr[3]);
}
void Init(){
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D4, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    pinMode(D8, OUTPUT);
    pinMode(LCD_RS, OUTPUT);    
    pinMode(LCD_RW, OUTPUT);    
    pinMode(LCD_EN, OUTPUT);
    WriteCmd(0x30);
    delay_us(4);
    WriteCmd(0x0c);
    delay_us(10);
    WriteCmd(0x01);
    delay(10);
}
int main(){
    wiringPiSetup();
    Init();
    while(1){
        WriteWord(0x80,teststr);
        delay_ms(500);
    }
    return 0;
}