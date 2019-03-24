void Init3DoT() {
  pinMode(7,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(encoder_PinL, INPUT_PULLUP);
  pinMode(encoder_PinR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoder_PinL), countLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_PinR), countRight, CHANGE);
};
