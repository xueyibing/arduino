#include <Stepper.h>
#include <Arduino_FreeRTOS.h>
#include <Servo.h>  

void TaskPrint1(void *param); //声明打印任务1
void TaskPrint2(void *param); //声明打印任务2


// 定义电机控制用常量
 
// 电机内部输出轴旋转一周步数
const int STEPS_PER_ROTOR_REV = 32; 
 
//  减速比
const int GEAR_REDUCTION = 64;

// 电机外部输出轴旋转一周步数 （2048）
const float STEPS_PER_OUT_REV = STEPS_PER_ROTOR_REV * GEAR_REDUCTION;
 
// 定义电机控制用变量
// 电机旋转步数
int StepsRequired;
 
// 建立步进电机对象
// 定义电机控制引脚以及电机基本信息。
// 电机控制引脚为 8,9,10,11 
// 以上引脚依次连接在ULN2003 驱动板 In1, In2, In3, In4 
 
Stepper steppermotor2(STEPS_PER_ROTOR_REV, 8, 10, 9, 11); 

const int NOButton = 2;
const int knockPin = 4;
const int baseServoPin = 9;
Servo myservo;    

int NoState = 0;
int suctionState2 = 0; //0 初始化；1：已经回退到两边；2：已经走到夹蛋位置，吸泵启动中；3：敲完蛋


void setup() {

  Serial.begin(9600);
  while (!Serial);//等待串口连接后执行
//  pinMode(NOButton, INPUT);
//  pinMode(baseServoPin, OUTPUT);
//  pinMode(knockPin, INPUT);
//  myservo.attach(baseServoPin); 

// attachInterrupt(digitalPinToInterrupt(NOButton), handleButtonChanged, CHANGE);

  xTaskCreate(TaskMoveSuction, "Print1", 128, NULL, 1, NULL); //创建任务1
//  xTaskCreate(TaskSuction, "Print2", 128, NULL, 1, NULL); //创建任务2
//  xTaskCreate(TaskBase, "base", 128, NULL, 1, NULL); //创建任务2
Serial.println("Lll");

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


void initPropram(int s){

  if(s == 1){
    myservo.write(90);
    Serial.println("90");
  }else{
    myservo.write(0);
     Serial.println("0");
  }
//  myservo.write(90);
//  Serial.println("30");
////  myservo.write(0);
//  Serial.println("0");
//  int v =  myservo.read();
//  
//   Serial.println(v);

}

void TaskMoveSuction(void *param)
{
  Serial.println("vvvv");

    // 快速逆时针旋转一圈
  StepsRequired  =  STEPS_PER_OUT_REV;   
  steppermotor2.setSpeed(200);  
  steppermotor2.step(StepsRequired);

}



void TaskSuction(void *param)
{
  while (1)
  {
    if(suctionState2 == 2 || suctionState2 == 3  ){
      digitalWrite(3, HIGH);
    }else{
      digitalWrite(3, LOW);
    }
   delay(10);
  }
}

void TaskBase(void *param)
{
  int s = 0;
  while (1)
  {
    Serial.print("NoState:");
    Serial.println(NoState);
    
    delay(1000);
    if(NoState){
        s = 0;
        myservo.write(s);
        delay(1000);
        s = 60;
        myservo.write(s);
    }


//
//  for(int pos = 0; pos < 180; pos += 1){    // 舵机从0°转到180°，每次增加1°          
//      myservo.write(pos);           // 给舵机写入角度   
//      delay(100);                    // 延时15ms让舵机转到指定位置
//   }
//    for(int pos = 180; pos>=1; pos-=1) {    // 舵机从180°转回到0°，每次减小1°                               
//       myservo.write(pos);        // 写角度到舵机     
//       delay(200);                 // 延时15ms让舵机转到指定位置
//    } 

       
  }
}



void loop() {

}
