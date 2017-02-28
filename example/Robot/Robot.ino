#include <ManualDIY.h>
#include <RF24.h>
#include <Servo.h>
#include <SPI.h>
#include<LiquidCrystal.h>                                          
#include <stdlib.h>
LiquidCrystal lcd(1, 0, A0, A1, A2, A3);   

Servo servo1;
/*************  USER Configuration *****************************/
                                          
RF24 radio(9,10);           // Set up nRF24L01 radio on SPI bus plus pins 7 & 8
ManualDIY robot;    // control robot lib             
/***************************************************************/
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x0101010101LL };   // Radio pipe addresses for the 2 nodes to communicate.
unsigned int data[3];                           //Data buffer for testing data transfer speeds
/*****************************************************************/
int LY,LX,RY,RX;      // bien doc gia tri analog
int rspd, lspd,rdir,ldir; //bien dieu khien toc do, huong quay cua dong co
int ludspd,rudspd,llrspd,rlrspd; //bien tham so toc do quay cua dong co
/**************************************************************/

void setup(void) {
  lcd.begin(16,2);
  robot.init_pin();
  servo1.attach(3);
  servo1.write(00);
  radio.begin();                           // Setup and configure rf radio
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();                 // Start listening
  radio.powerUp();                        //Power up the radio
  rspd=0;
  lspd=0;
}

void loop(void){
lcd.setCursor(0, 0);  lcd.print("robotic_starter");
lcd.setCursor(0, 1);
lcd.print("Code: A1");    
 
    if(radio.available()){       
     radio.read(&data,sizeof(data));
     LY=data[1]/256;
     LX=data[1]%256;
     RY=data[2]/256;
     RX=data[2]%256;
     Serial.print(data[0]); Serial.print(":");
     Serial.print(LY); Serial.print("-");Serial.print(LX); Serial.print(":");
     Serial.print(RY); Serial.print("-");Serial.println(RX);
//=======================So sanh gia tri nhan ve voi cac nut bam======================================================
     if((data[0]&UP)==UP){      //forward
      ludspd=250;
      rudspd=250;
      } 
     if((data[0]&RIGHT)==RIGHT){  //right
      rlrspd=-180;
      llrspd=180;
      } 
     if((data[0]&LEFT)==LEFT){   //left
      rlrspd=180;
      llrspd=-180;
      } 
     if((data[0]&DOWN)==DOWN){   //back
      rudspd=-250;
      ludspd=-250;
      } 
     if((data[0]&TamGiac)==TamGiac){
      servo1.write(0);
      delay(30);
     }
     if((data[0]&Tron)==Tron){
      servo1.write(45);
      delay(30);
     }
     if((data[0]&Nhan)==Nhan){
      servo1.write(90);
      delay(30);
     }
     if((data[0]&Vuong)==Vuong){
      servo1.write(135);
      delay(30);
     }
     if((data[0]&L1)==L1){
     }
     if((data[0]&R1)==R1){
     }
     if((data[0]&L2)==L2){
     }
     if((data[0]&R2)==R2){
     }
     if((data[0]&Start)==Start){
     }
     if((data[0]&Select)==Select){
     }
     if(LX>240){      // L analog right
      rlrspd=-180;
      llrspd=180;}
     if(LX<60){       //L analog left
     }
     if(LY>240){      //L analog down
      rudspd=-250;
      ludspd=-250;
     }
     if(LY<60){       //L analog up
      ludspd=250;
      rudspd=250;
     }
     if(RX>240){      // R analog right
      rlrspd=180;
      llrspd=-180; 
     }
     if(RX<60){       //R analog left
      
     }
     if(RY>240){      //R analog down
     }
     if(RY<60){       //R analog up
     }
     if((data[0]==0)&&(LX==128)&&(LY==128)&&(RX==128)&&(RY==128)){ // khi k nhan 1 nut nao ca
      ludspd=0;
      rudspd=0;
      llrspd=0;
      rlrspd=0;
     }
    data[0]=0;    
    }
    rspd=rudspd+rlrspd;
    lspd=ludspd+llrspd;
    if(rspd<0) {rdir=1; rspd=-rspd;} else rdir=0;
    if(lspd<0) {ldir=1; lspd=-lspd;} else ldir=0;
    robot.control_motor(0,rdir,rspd);
    robot.control_motor(1,ldir,lspd); 
}