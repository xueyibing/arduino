#include <Arduino_FreeRTOS.h>
#include <Stepper.h>
#include <Servo.h>  
#include <Arduino.h>
#include "angle.h"
#include "l298n.h"

void TaskAngle(void *param); //声明打印任务1
void TaskSpin(void *param); //声明打印任务2



void freeRtOsSetup() {

// attachInterrupt(digitalPinToInterrupt(NOButton), handleButtonChanged, CHANGE);

// xTaskCreate(TaskAngle, "Print1", 128, NULL, 1, NULL); //创建任务1
xTaskCreate(TaskSpin, "Print2", 128, NULL, 1, NULL); //创建任务2

vTaskStartScheduler(); //启动任务调度
}

//void handleButtonChanged() {
//    int level = digitalRead(NOButton);
//    if (level == HIGH) {
//        // 输入为高电平，按钮松开，开关断开
//        Serial.println("HIGH");
//        NoState = !NoState;
//        initPropram(NoState);
//        Serial.println(NoState);
//        
//    } else if (level == LOW) {
//        // 输入为低电平，按钮按下，开关接通
//        Serial.println("LOW");
//    } else {
//        // 不知道发生了什么奇怪的问题，这种情况我们就不要管了~=￣ω￣=~
//        Serial.println("UNKNOW");
//    }
//}



void TaskAngle(void *param)
{
    Serial.println("TaskAngle");
    while (1)
    {
        delay(5);
        float an = getAngle();

    }


}

void TaskSpin(void *param)
{
    int status = 1;
    spinClockwise();

    while (1)
    {
        delay(5);
        float an = getAngle();
        Serial.print(an);
        Serial.print(status);
        Serial.print(" ");

        
        //正转过头
        if(an >= 3.8 && status == 1){
            spinUnClockwise();
            status = 2;  
            Serial.println("spinUnClockwise...>>>");


            
        }

        //反转过头
        if(an <= 1.2 && status == 2 ){
            spinClockwise();
            status = 1;
            Serial.println("spinClockwise...<<<");

        }
        spinEnable();
        
    }
}


