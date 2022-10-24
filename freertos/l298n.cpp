#include "step42.h"
#include <Arduino.h>
#include <AccelStepper.h>
#include <Stepper.h>


int En = 5;    
int In1 = 2;   
int In2 = 3;  
 


 // Number of steps per output rotation
// const int stepsPerRevolution = 200;

// // Create Instance of Stepper library
// Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void l298nSetup() {

  pinMode( En,  OUTPUT ); 
  pinMode( In1,  OUTPUT );
  pinMode( In2,  OUTPUT );
 
}


void l298nLoop() {

  Serial.println("l298nLoop..");
  analogWrite(En,200);
  digitalWrite(In1, HIGH);   //方向初始化
  digitalWrite(In2, LOW);
  delay(5000);

  Serial.println("l298nLoop...>>>");

  analogWrite(En,255);
  digitalWrite(In1, LOW);   //方向初始化
  digitalWrite(In2, HIGH);
  delay(5000);


}

void spinClockwise() {
  digitalWrite(In1, HIGH);   
  digitalWrite(In2, LOW);

}

void spinUnClockwise() {
  digitalWrite(In1, LOW);   
  digitalWrite(In2, HIGH);
}

void spinEnable(){
  analogWrite(En,255);
}