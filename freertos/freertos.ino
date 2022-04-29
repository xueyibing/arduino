#include <Arduino_FreeRTOS.h>
#include <Stepper.h>

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
 
Stepper steppermotor(STEPS_PER_ROTOR_REV, 8, 10, 9, 11); 

const int zsButton = 2;
const int knockPin = 4;
int suctionState = 0; //0 初始化；1：已经回退到两边；2：已经走到夹蛋位置，吸泵启动中；3：敲完蛋

void setup() {

  Serial.begin(9600);
  while (!Serial);//等待串口连接后执行

  pinMode(zsButton, INPUT);
  pinMode(3, OUTPUT);
  pinMode(knockPin, INPUT);

  xTaskCreate(TaskMoveSuction, "Print1", 128, NULL, 1, NULL); //创建任务1
  xTaskCreate(TaskCheckSide, "Print2", 128, NULL, 1, NULL); //创建任务2
  xTaskCreate(TaskSuction, "Print2", 128, NULL, 1, NULL); //创建任务2

  vTaskStartScheduler(); //启动任务调度
}




void TaskMoveSuction(void *param)
{

    // 快速逆时针旋转一圈
  StepsRequired  =  -STEPS_PER_OUT_REV;   
  steppermotor.setSpeed(800);  
  steppermotor.step(StepsRequired/4);
  while (1)
  {
    Serial.println(suctionState);
    switch(suctionState){
    case 0:
      StepsRequired  =  STEPS_PER_OUT_REV;   
      steppermotor.setSpeed(800);  
      steppermotor.step(StepsRequired/64); 
      break;
    case 1:
      //往中间走
      StepsRequired  =  - STEPS_PER_OUT_REV;   
      steppermotor.setSpeed(800);  
      steppermotor.step(StepsRequired/2);
      suctionState = 2;
      break; 
    case 3:
      //往两边走
      StepsRequired  =  STEPS_PER_OUT_REV;   
      steppermotor.setSpeed(800);  
      steppermotor.step(StepsRequired/4);
      break; 
    default : 
    break;
    }
    delay(10);
  }
}

void TaskCheckSide(void *param)
{
  while (1)
  {
    int buttonState = digitalRead(zsButton);
    if (buttonState == HIGH) {
       suctionState = 1;
   } 

    int knockState = digitalRead(knockPin);
    if (knockState == HIGH) {
       suctionState = 3;
   } 
   delay(10);
  }
}

void TaskSuction(void *param)
{
  while (1)
  {
    if(suctionState == 2 || suctionState == 3  ){
      digitalWrite(3, HIGH);
    }else{
      digitalWrite(3, LOW);
    }
   delay(10);
  }
}




void loop() {

}
