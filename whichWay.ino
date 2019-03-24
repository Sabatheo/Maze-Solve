uint8_t whichWay(uint8_t dir, uint8_t room){
  boolean front = hitWall(dir, room);
  boolean left = leftWall(dir, room);
  boolean right = rightWall(dir, room);
  uint8_t roomType =  ((front << 1) + (left << 2) + right); 
  switch(roomType){
    case 0x00:
    //4-way intersection (All directions open)
    return 0x00; // Do not turn
    break;
    case 0x01:
    //T-intersection (Right blocked)
    return 0x00; // Do not turn
    break;
    case 0x02:
    //T-intersection (Front blocked)
    return 0x01; // will not be in path
    break;
    case 0x03:
    //Left corner
    return 0x02; //Turn Left
    break;
    case 0x04:
    //T-intersection (Left blocked)
    return 0x01; //Turn Right
    break;
    case 0x05:
    //Hallway
    return 0x00;  //Do not turn
    break;
    case 0x06:
    //Right corner
    return 0x01; //Turn right
    break;
    case 0x07:
    //Dead end
    return 0x03;  //Turn around
    break;    
  } 
}
boolean hitWall(uint8_t dir, uint8_t room){
  uint8_t rear_Wall=room & 0x08;  //Masks by anding with 1000
  uint8_t right_Wall=room & 0x02; //Masks by anding with 0010
  uint8_t left_Wall=room & 0x04;  //Masks by anding with 0100
  uint8_t front_Wall=room & 0x01; //Masks by anding with 0001
  if (dir==0x00 && rear_Wall==0x08){      //If facing south and there is a rear wall return 1
    return true;
  }
  else if (dir==0x01 && right_Wall==0x02){ //If facing east and there is right wall return 1
    return true;
  }
  else if (dir==0x02 && left_Wall==0x04){  //If facing west and there is left wall return 1
    return true;
  }
  else if (dir==0x03 && front_Wall==0x01){ //If facing north and there is a front wall return 1
    return true;
  }
  else{
    return false;  //otherwise return 0
  }
}

boolean leftWall(uint8_t dir, uint8_t room){
  uint8_t rear_Wall=room & 0x08;  //Masks by anding with 1000
  uint8_t right_Wall=room & 0x02; //Masks by anding with 0010
  uint8_t left_Wall=room & 0x04;  //Masks by anding with 0100
  uint8_t front_Wall=room & 0x01; //Masks by anding with 0001
  if (dir==0x00 && right_Wall==0x02){      //If facing south and there is wall on your left (right wall) return 1
    return true;
  }
  else if (dir==0x01 && front_Wall==0x01){ //If facing east and there is wall on your left (front wall) return 1
    return true;
  }
  else if (dir==0x02 && rear_Wall==0x08){  //If facing west and there is wall on your left (rear wall) return 1
    return true;
  }
  else if (dir==0x03 && left_Wall==0x04){ //If facing north and there is wall on your left (left wall) return 1
    return true;
  }
  else{
    return false;  //otherwise return 0
  }
}

boolean rightWall(uint8_t dir, uint8_t room){
  uint8_t rear_Wall=room & 0x08;  //Masks by anding with 1000
  uint8_t right_Wall=room & 0x02; //Masks by anding with 0010
  uint8_t left_Wall=room & 0x04;  //Masks by anding with 0100
  uint8_t front_Wall=room & 0x01; //Masks by anding with 0001
  if (dir==0x00 && left_Wall==0x04){      //If facing south and there is wall on your right (left wall) return 1
    return true;
  }
  else if (dir==0x01 && rear_Wall==0x08){ //If facing east and there is wall on your right (rear wall) return 1
    return true;
  }
  else if (dir==0x02 && front_Wall==0x01){  //If facing west and there is wall on your right (front wall) return 1
    return true;
  }
  else if (dir==0x03 && right_Wall==0x02){ //If facing north and there is wall on your right (right wall) return 1
    return true;
  }
  else{
    return false;  //otherwise return 0
  }
}
