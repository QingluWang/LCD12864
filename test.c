#include <wiringPi.h>
#define LED 0

int main(){
    wiringPiSetup();
    pinMode(0, PWM_OUTPUT);
    int i;
    for(i = 0; i < 1024; i++){
        pwmWrite(LED,i);
        delay(12);
    }
    for(i = 1023; i >= 0; i--){
        pwmWrite(LED,i);
        delay(12);
    }
    return 0;
}