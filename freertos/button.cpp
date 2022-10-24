#include "button.h""
#include <Arduino.h>
#include <Stepper.h>



void buttonSetup() {
  pinMode(13,INPUT);

}

void buttonLoop() {
  int buttonState = digitalRead(13); 
  if (buttonState == HIGH) {
    Serial.println("down");
  } else {
   Serial.println("up");
  }
 
  delay(100);
}
