#include <JoystickF.h>


int r0 = 0;      //value of select pin at the 4051 (s0)
int r1 = 0;      //value of select pin at the 4051 (s1)
int r2 = 0;      //value of select pin at the 4051 (s2)
int r3 = 0;      //value of select pin at the 4051 (s3)
int r4 = 0;      //value of select pin at the 4051 (s4)
int r5 = 0;      //value of select pin at the 4051 (s5)

int s0 = 2;
int s1 = 3;
int s2 = 4;
int s3 = 5;
int s4 = 6;
int s5 = 7;

int axisValues[80];

void setup() {
  Joystick.begin(true);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
  pinMode(s5, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void multiplexerLogic(int count){
  //1st multiplexer
  r0 = bitRead(count,0);    
  r1 = bitRead(count,1); 
  r2 = bitRead(count,2);
  //2nd multiplexer
  r3 = bitRead(count,3);       
  r4 = bitRead(count,4);       
  r5 = bitRead(count,5);       
  
  //1st multiplexer
  digitalWrite(s0, r0);    
  digitalWrite(s1, r1);
  digitalWrite(s2, r2);
  //2nd multiplexer       
  digitalWrite(s3, r3);   
  digitalWrite(s4, r4);
  digitalWrite(s5, r5);
}

void loop(){
    uint8_t multiplexerLogicCount = 0;

    for(int i = 0; i <= 8; i+=3){
      multiplexerLogic(multiplexerLogicCount);

      axisValues[i] = map(analogRead(A0),0,1023,-510,510);
      Joystick.setXAxis(axisValues[i]);

      axisValues[i+1] = map(analogRead(A1),0,1023,-510,510);
      Joystick.setXAxis(axisValues[i+1]);

      axisValues[i+2] = map(analogRead(A2),0,1023,-510,510);
      Joystick.setXAxis(axisValues[i+2]);

      multiplexerLogicCount++;
    }

    for(int i = 9; i < sizeof(axisValues) ; i++){
      multiplexerLogic(i);

      axisValues[i] = map(analogRead(A0),0,1023,-510,510);
      Joystick.setXAxis(axisValues[i]);
    }
}
