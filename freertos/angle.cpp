#include "angle.h"
#include <Arduino.h>
#include <Stepper.h>



void angleSetup() {


}

void angleLoop() {

 
 // 读取模拟引脚A0的输入数据
   int sensorValue = analogRead(A0);
   // 将模拟信号转换成电压
   float voltage = sensorValue * (5.0 / 1023.0);
   // 打印到串口监视器
   Serial.print(voltage);
   Serial.print(" ");
  delay(5);
}


float getAngle() {
 // 读取模拟引脚A0的输入数据
  int sensorValue = analogRead(A0);
  // 将模拟信号转换成电压
  float voltage = sensorValue * (5.0 / 1023.0);
  // Serial.print(voltage);
  // Serial.print(" ");
  return voltage;
}
