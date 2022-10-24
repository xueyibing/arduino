#include "step42.h"
#include <Arduino.h>
#include <AccelStepper.h>


int EN_PIN = 8;    //使能引脚
int DIR_PIN = 5;   //方向引脚
int STEP_PIN = 2;  //脉冲引脚
 

void step42Setup() {


  pinMode( EN_PIN,  OUTPUT ); 
  pinMode( DIR_PIN,  OUTPUT );
  pinMode( STEP_PIN,  OUTPUT );
  digitalWrite(EN_PIN, LOW);    //使能步进电机
  digitalWrite(DIR_PIN, LOW);   //方向初始化
  digitalWrite(STEP_PIN, LOW);

}


void step42Loop() {

    Serial.println("step42Loop..");

    digitalWrite(STEP_PIN, HIGH);
    // delayMicroseconds(5000);
    digitalWrite(STEP_PIN, LOW);

    // delay(1000);


}
