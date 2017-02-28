#include "Arduino.h"
#include <EEPROM.h>
#include "ManualDIY.h"
//=======================================
#define PWM1 6
#define DIR1 7
#define PWM2 5
#define DIR2 4
//=======================================

//=========Khoi tao chan dieu khien dong co=================
void ManualDIY::init_pin(void){
  pinMode(DIR1,OUTPUT);  //DIR1;
  pinMode(PWM1,OUTPUT);  //PWM1
  pinMode(PWM2,OUTPUT);  //PWM2
  pinMode(DIR2,OUTPUT);  //DIR2
}
//========Ham dieu khien dong co============================
void ManualDIY::control_motor(int dc, int dir, int spd){
  switch (dc){
    case 0:{
    if(dir==0)
      {
      digitalWrite(DIR1,0);
      analogWrite(PWM1, spd);
     // digitalWrite(PWM1, 1);
      }
    else
      {
      digitalWrite(DIR1,1);
      analogWrite(PWM1, 255-spd);  
      //digitalWrite(PWM1, 0);
      }
    }
    case 1:{
    if(dir==0)
      {
      digitalWrite(DIR2,0);
      analogWrite(PWM2, spd);
     // digitalWrite(PWM2, 1);
      }
    else
      {
      digitalWrite(DIR2,1);
      analogWrite(PWM2, 255-spd);  
      //digitalWrite(PWM2, 0);
      }
    }
  }
}
