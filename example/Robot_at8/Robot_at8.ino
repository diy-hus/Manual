#define RF_Atmega8        //Dinh nghia su dung thu vien danh cho tay cam atmega8
//================================
#include <Servo.h>
#include <SPI.h>
#include <RF24.h>
#include <ManualDIY.h>
// servo D3
Servo servo1;
/*************  USER Configuration *****************************/
                                          // Hardware configuration
RF24 radio(9,10);                        // Set up nRF24L01 radio on SPI bus plus pins 7 & 8
ManualDIY robot;

/***************************************************************/

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0xA4A4A4A4A4LL };   // Radio pipe addresses for the 2 nodes to communicate.
unsigned char pad;
/***************************************************************/
void setup(void) {
  Serial.begin(115200);
  robot.init_pin();
  servo1.attach(3);
  servo1.write(00);
  radio.begin();                           // Setup and configure rf radio
  radio.setChannel(2);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setPayloadSize(1); 
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();                 // Start listening
  radio.powerUp();                        //Power up the radio
}

void loop(void){ 
    if(radio.available()){       
     radio.read(&pad,1);
     Serial.println(pad);
//==================================================================================
     if(pad==UP){      //forward
      robot.control_motor(0,0,250);
      robot.control_motor(1,0,250);
      } 
     if(pad==RIGHT){  //right
      robot.control_motor(0,1,250);
      robot.control_motor(1,0,250);
      } 
     if(pad==LEFT){   //left
      robot.control_motor(0,0,250);
      robot.control_motor(1,1,250);
      } 
     if(pad==DOWN){   //back
      robot.control_motor(0,1,250);
      robot.control_motor(1,1,250);
      } 
     if(pad==TamGiac){
      servo1.write(0);
      delay(30);
     }
     if(pad==Tron){
      servo1.write(45);
      delay(30);
     }
     if(pad==Nhan){
      servo1.write(90);
      delay(30);
     }
     if(pad==Vuong){
      servo1.write(135);
      delay(30);
     }
     if(pad==L1){
     }
     if(pad==R1){
     }
     if(pad==L2){
     }
     if(pad==R2){
     }
     if(pad==Start){
     }
     if(pad==Select){
     }
     if(pad==lj_up){     // analog trai
      robot.control_motor(0,0,250);
      robot.control_motor(1,0,250);
	 }
     if(pad==lj_down){
      robot.control_motor(0,1,250);
      robot.control_motor(1,1,250);
	 }
     if(pad==lj_left){
      robot.control_motor(0,0,250);
      robot.control_motor(1,1,250);
	  }
     if(pad==lj_right){
      robot.control_motor(0,1,250);
      robot.control_motor(1,0,250);
	 }
     if(pad==rj_up){     //analog phai
     }
     if(pad==rj_down){
     }
     if(pad==rj_left){
     }
     if(pad==rj_right){
     }
     if(pad==0){
     robot.control_motor(0,0,0);
     robot.control_motor(1,0,0);
     }
    }
}

