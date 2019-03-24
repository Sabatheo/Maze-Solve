uint8_t turnInMaze(uint8_t dir, uint8_t turn){
uint8_t index = (turn << 2) + dir;
uint8_t curr_dir = pgm_read_byte_near(turn_table + index);
return curr_dir;
}

Coord stepInMaze (Coord Step, uint8_t dir){
uint8_t index_row = dir;                                                  
uint8_t index_col = 0x04+dir;                                             //Add 4 to dir to skip the "row" part
uint8_t row = Step.row + (pgm_read_byte_near(map_table + index_row));     //Add indexes to previous coordinates
uint8_t col = Step.col + (pgm_read_byte_near(map_table + index_col));
Step.row = row;
Step.col = col;
    return Step;
}



uint8_t roomInMaze (Coord pos){
  uint16_t r_index = (21*pos.row) + pos.col;                              //Multiply index by 21*row since there are 21 columns and then add the col to move through the row
  uint8_t Roomtype = pgm_read_byte_near(theMaze+r_index);
  return Roomtype;
}

void Follow_Line(){
  double SetpointL,SetpointR,Input_L,Output_L,Input_R,Output_R;                    //PID Setup
  float Kp=2;
  float Ki=6;
  float Kd=1;
  int R_motorspeed;
  int L_motorspeed;
  PID myPIDL(&Input_L, &Output_L, &SetpointL,Kp,Ki,Kd, DIRECT);
  PID myPIDR(&Input_R, &Output_R, &SetpointR,Kp,Ki,Kd, DIRECT);
  digitalWrite(STBY,HIGH);
  Input_L=analogRead(IR_L0);
  Input_R=analogRead(IR_R0);
  SetpointL=600;
  SetpointR=600;
  myPIDL.SetMode(AUTOMATIC);
  myPIDR.SetMode(AUTOMATIC);
  myPIDL.SetOutputLimits(-20,20);          //Make PID output a value between 0 and 10
  myPIDR.SetOutputLimits(-20,20);
  myPIDL.Compute();
  myPIDR.Compute();
  R_motorspeed=base_speed_R+Output_R;          //Increase Right motor speed to turn left
  L_motorspeed=base_speed_L+Output_L;          //Increase Left motor speed to turn right
  analogWrite(PWMA,R_motorspeed);
  analogWrite(PWMB,L_motorspeed);
  
}

void countLeft() {
  enc_L++;
}

void countRight() {
  enc_R++;
}

void Turn_Right(){
  int L_count=320;
  while (enc_L<L_count){
    digitalWrite(STBY,HIGH);
    analogWrite(PWMA,0);
    analogWrite(PWMB,80);
  }
    digitalWrite(STBY,LOW);
    delay(1000);
  enc_L=0;
}

void Turn_Left(){
 int R_count=320;
  while (enc_R<R_count){
    digitalWrite(STBY,HIGH);
    analogWrite(PWMA,80);
    analogWrite(PWMB,0);
  }
    digitalWrite(STBY,LOW);
    delay(1000);
  enc_R=0;
}
int Count_intersections(){
  int intersections;
  int O_L,O_R,I_L,I_R;
  O_L=analogRead(IR_L1);      //Read outer sensors
  O_R=analogRead(IR_R1);
  I_L=analogRead(IR_L0);      //Read inner sensors
  I_R=analogRead(IR_R0);
  if (O_L,O_R,I_L,I_R >= 600){
    intersections++;
  }
  return intersections;
}
void Move_Forward(){
  int prev_intersections;
  int curr_intersections;
  int state_change;
  curr_intersections=Count_intersections();
  state_change=curr_intersections-prev_intersections;
  if (state_change>0){
    state_change=1;
  }
  else {
    state_change=0;
  }
  while (state_change==0){
    curr_intersections=Count_intersections();
    state_change=curr_intersections-prev_intersections;
    if (state_change>0){
      state_change=1;
    }
    else {
      state_change=0;
    }
      digitalWrite(STBY,HIGH);
      Follow_Line();
    }
  prev_intersections=curr_intersections;
  digitalWrite(STBY,LOW);

}
void CheckInForest(uint8_t Row,uint8_t Col){
  if (Row==0x00 && Col >= 0x14){
    digitalWrite(STBY,LOW);     //Stops robot from moving
    delay(50000);
  }
}
