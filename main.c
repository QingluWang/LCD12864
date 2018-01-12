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
    digitalWrite(LCD_RS,DISABLE);
    digitalWrite(LCD_RW,ENABLE);
    digitalWrite(LCD_EN,DISABLE);
    BusWrite(0xff);
    pinMode(D8, INPUT);
    while(digitalRead(D8));//lcd12864不忙时D8为低电平
    pinMode(D8, OUTPUT);
    digitalWrite(LCD_EN,DISABLE);
}
void WriteCmd(u8 cmdCode){
    digitalWrite(LCD_RS,DISABLE);
    digitalWrite(LCD_RW,DISABLE);
    digitalWrite(LCD_EN,ENABLE);
    delay(5);
    BusWrite(cmdCode);
    digitalWrite(LCD_EN,DISABLE);
    delay(5);
}
void WriteData(u8 dispData){
    printf("1\n");
    ChkBusy();
    printf("2\n");
    digitalWrite(LCD_RS,ENABLE);
    digitalWrite(LCD_RW,DISABLE);
    digitalWrite(LCD_EN,ENABLE);
    printf("3\n");
    delay(5);
    BusWrite(dispData);
    printf("4\n");
    digitalWrite(LCD_EN,DISABLE);
    delay(5);
}
void WriteWord(u8 pos,unsigned char* data){
    WriteCmd(pos);
    while(*data > 0){
        WriteData(*data);
        data++;
    }
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
    WriteCmd(0x38);
    delay(20);
    WriteCmd(0x01);
    delay(20);
    WriteCmd(0x0c);
    delay(20);
}
int main(){
    wiringPiSetup();
    Init();

    WriteCmd(0x01);
    WriteWord(0x80,"Hello,wql");
    return 0;
}