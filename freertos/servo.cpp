#include "servo.h"
#include <Servo.h>//定义头文件，这里有一点要注意，可以直接在Arduino 软件菜单栏单击Sketch>Importlibrary>Servo,调用Servo 函数，也可以直接输入#include <Servo.h>，但是在输入时要注意在#include 与<Servo.h>之间要有空格，否则编译时会报错。
#include <Arduino.h>

int servopin = 9; //定义数字接口9 连接伺服舵机信号线
int myangle;      //定义角度变量
int pulsewidth;   //定义脉宽变量
int val;

Servo myservo2;//定义舵机变量名



void servoSetup()
{
    Serial.begin(9600);        //连接到串行端口，波特率为9600


    pinMode(servopin, OUTPUT); //设定舵机接口为输出接口

    // myservo.attach(servopin); 
    // myservo.write(0);

    Serial.println("servo=o_seral_simple ready");


}

void servoLoop() //将0 到9 的数转化为0 到180 角度，并让LED 闪烁相应数的次数
{


    // servoLoopSlow();
        servoLoop1();
}


void servopulse(int myangle) //定义一个脉冲函数
{
    int pulsewidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值
    digitalWrite(servopin, HIGH);      //将舵机接口电平至高
    delayMicroseconds(pulsewidth);     //延时脉宽值的微秒数
    digitalWrite(servopin, LOW);       //将舵机接口电平至低
    delay((20 - pulsewidth / 1000)*1);
}

void servoLoop1() //将0 到9 的数转化为0 到180 角度，并让LED 闪烁相应数的次数
{


    int val = 80;
    Serial.print("moving servo to ");
    Serial.print(val, DEC);
    Serial.println();


 for (int i = 0; i <= 180; i++)
    {

 servopulse(i); //引用脉冲函数
 delay(30);
    }

   
    

    delay(3000);


    servopulse(0); //引用脉冲函数
    

     delay(3000);
    
}


void servoLoopSlow() //将0 到9 的数转化为0 到180 角度，并让LED 闪烁相应数的次数
{

    for (int i = 0; i <= 90; i++)
    {
        myservo2.write(i);
        delay(30);
        Serial.println("servo");
        Serial.println(i);

    }
    
    delay(2000);
    for (int i = 90; i >= 0; i--)
    {
        myservo2.write(i);
        delay(30);
        Serial.println("servo");
        Serial.println(i);
    }
    delay(5000);
}