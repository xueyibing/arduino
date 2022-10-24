#include "step.h"
#include <Arduino.h>
#include <Stepper.h>

// 定义电机控制用常量

// 电机内部输出轴旋转一周步数
const int STEPS_PER_ROTOR_REV = 32; 
//  减速比
const int GEAR_REDUCTION = 16;
// 电机外部输出轴旋转一周步数 （2048）
const float STEPS_PER_OUT_REV = STEPS_PER_ROTOR_REV * GEAR_REDUCTION;
 
 
// 电机控制引脚为 8,9,10,11 
// 以上引脚依次连接在ULN2003 驱动板 In1, In2, In3, In4 
Stepper steppermotor(STEPS_PER_ROTOR_REV, 8, 10, 9, 11); 

const int zsButton = 2;
const int knockPin = 4;
int suctionState = 0; //0 初始化；1：已经回退到两边；2：已经走到夹蛋位置，吸泵启动中；3：敲完蛋

void stepSetup() {


}

void stepLoop() {

 
  steppermotor.setSpeed(1000);  
  steppermotor.step(STEPS_PER_OUT_REV*10);
  delay(2000);
}
