//Saba Theodory
//014146312
//Lab 6
//Mission
#include "maze.h"
#include <PID_v1.h>
#include <avr/pgmspace.h>
const int IR_R0 = A0;   //PF7
const int IR_L0 = A3;   //PF4
const int IR_R1 = A1;   //PF6
const int IR_L1 = A2;   //PF5  The sensor pins were changed slightly
const int AIN1 = 7;     //     This pin was changed from PD6 because the pro micro didnt have a pin for that
const int AIN2 = 4;     //PD4
const int BIN1 = 9;     //PB5
const int BIN2 = 5;     //PC6 
const int PWMA = 6;     //PD7  Right motor
const int PWMB = 10;    //PB6  Left motor
const int STBY = 8;     //PB5
const int encoder_PinL = 2; //Encoder interrupt pin L
const int encoder_PinR = 3; //Encoder interrupt pin R
volatile unsigned long enc_L = 0;
volatile unsigned long enc_R = 0;
const int base_speed_R = 105;              //Initial speed for motors. After direction has been adjusted they return to this speed
const int base_speed_L = 110;
void setup() {
  Init3DoT();
  Serial.begin(9600);
  delay(3000);                             //3 Second delay for setup before robot starts moving
  digitalWrite(STBY,HIGH);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH); 
}
void loop() {
  static MyRobot Robot{0x03,0x01,0x00,0x00,0x12,0x00}; //Initializes robot to bottom left corner
  Robot.dir = turnInMaze(Robot.dir, Robot.turn);
  Robot.maze = stepInMaze(Robot.maze,Robot.dir);
  uint8_t Roomtype = roomInMaze(Robot.maze);
  Robot.room = Roomtype & 0b00001111;                 //Clears 4 MSBs from variable
  Robot.bees = Roomtype >> 4;                         //Clears 4 LSBs from variable
  CheckInForest(Robot.maze.row,Robot.maze.col);       //Checks if maze is solved
  Robot.turn = whichWay(Robot.dir,Robot.room);
  if (Robot.turn == 0x01){
    Turn_Right();
  }
  else if (Robot.turn == 0x02){
    Turn_Left();
  }
  else if (Robot.turn == 0x03){
    //Move_Forward();
  }
  digitalWrite(STBY,HIGH);
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);              //Setup to make the motors move CCW which is forward in my case
  Move_Forward();
  }
