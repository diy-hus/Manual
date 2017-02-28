 
#ifndef ManualDIY_h
#define ManualDIY_h

#include "Arduino.h"
#include "RF24.h"
//=======================================
#define PWM1 6
#define DIR1 7
#define PWM2 5
#define DIR2 4
//=======================================
#ifdef RF_Atmega8
#define UP      17
#define RIGHT   20
#define LEFT    18
#define DOWN    19
#define TamGiac 21
#define Tron    22
#define Nhan    23
#define Vuong   24
#define L2      27
#define R2      28
#define L1      25
#define R1      26
#define Start   32
#define Select  29
#define lj_up     9
#define lj_down   11  
#define lj_left   13  
#define lj_right  15   
#define rj_up     1
#define rj_down   3
#define rj_left   5
#define rj_right  7
#else
#define UP      1
#define RIGHT   2
#define LEFT    4
#define DOWN    8
#define TamGiac 16
#define Tron    32
#define Nhan    64
#define Vuong   128
#define L2      256
#define R2      512
#define L1      1024
#define R1      2048
#define Start   4096
#define Select  8192
#endif
class ManualDIY
{
  public:
	void init_pin();
	void control_motor(int dc, int dir, int spd);  
};

#endif