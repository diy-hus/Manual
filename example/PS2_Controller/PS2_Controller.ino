#include <PS2X_lib.h>
#include <SPI.h>
#include <RF24.h>
#include <ManualDIY.h>
PS2X ps2x; // create PS2 Controller Class
RF24 radio(9,10);
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x0101010101LL };  
unsigned int data[3];
void setup(){
  Serial.begin(9600);

  ps2x.config_gamepad(7,5,6,4, false, false); 

  radio.begin();                           // Setup and configure rf radio
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
  radio.openWritingPipe(pipes[1]);
  radio.powerUp();                        //Power up the radio
}

void loop(){
    data[0]=0; data[1]=0;data[2]=0;
    ps2x.read_gamepad();  
    if(ps2x.Button(PSB_START)){                  //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
        data[0]|=Start;
    }
    if(ps2x.Button(PSB_SELECT)){
         Serial.println("Select is being held");
         data[0]|=Select;
    }
    if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
        data[0]|=UP;
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
       data[0]|=RIGHT;
     }
    if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        data[0]|=LEFT;
     }
    if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
        data[0]|=DOWN;
     }   
    if(ps2x.Button(PSB_L1)){
        Serial.println("L1 pressed");
        data[0]|=L1;
    }
    if(ps2x.Button(PSB_R1)){
        Serial.println("R1 pressed");
        data[0]|=R1;
    }
    if(ps2x.Button(PSB_L2)){
        Serial.println("L2 pressed");
        data[0]|=L2;
    }
    if(ps2x.Button(PSB_R2)){
        Serial.println("R2 pressed");
        data[0]|=R2;
    }
    if(ps2x.Button(PSB_GREEN)){
        Serial.println("Triangle pressed");  
         data[0]|=TamGiac;
    }
    if(ps2x.Button(PSB_RED)){             //will be TRUE if button was JUST pressed
         Serial.println("Circle just pressed");
         data[0]|=Tron;
    }
    if(ps2x.Button(PSB_PINK)){             //will be TRUE if button was JUST released
         Serial.println("Square just released"); 
         data[0]|=Vuong;    
    }
    if(ps2x.Button(PSB_BLUE)){            //will be TRUE if button was JUST pressed OR released
         Serial.println("X just changed");
         data[0]|=Nhan;
    }    
    data[1]=ps2x.Analog(PSS_LY)*256 + ps2x.Analog(PSS_LX); 
    data[2]=ps2x.Analog(PSS_RY)*256 + ps2x.Analog(PSS_RX); 
    radio.write(&data,sizeof(data));
    delay(50);
}
