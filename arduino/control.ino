#include <Servo.h> 

#define XPOS 0
#define YPOS 1

const int SERVOS = 6;
int PIN[SERVOS], value[SERVOS], idle[SERVOS], currentAngle[SERVOS], MIN[SERVOS];
int MAX[SERVOS], INITANGLE[SERVOS], previousAngle[SERVOS],ANA[SERVOS];
Servo myservo[SERVOS];


void setup() {
  Serial.begin(9600);

  //#1 서보모터
  PIN[0] = 3; //서보모터 IO를 3번핀으로 지정
  MIN[0] = 0; //서보모터 최소 회전각도
  MAX[0] = 180; //서보모터 최대 회전각도
  INITANGLE[0] = 10; //서보모터 초기각도
  ANA[0] = 0; //조이스틱스위치입력 IO를 아날로그 A0번핀으로 지정
  //#2 서보모터
  PIN[1] = 2;
  MIN[1] = 0; 
  MAX[1] = 180;
  INITANGLE[1] = 90;
  ANA[1] = 1;
  //#3 서보모터
  PIN[2] = 9;
  MIN[2] = 0;
  MAX[2] = 180;
  INITANGLE[2] = 90;
  ANA[2] = 2;
  //#4 서보모터
  PIN[3] = 8;
  MIN[3] = 0;
  MAX[3] = 180;
  INITANGLE[3] = 90;
  ANA[3] = 3;
  //#5 서보모터
  PIN[4] = 4;
  MIN[4] = 0;
  MAX[4] = 180;
  INITANGLE[4] = 80;
  ANA[4] = 4;
  //#6 서보모터
  PIN[5] = 5;
  MIN[5] = 0;
  MAX[5] = 180;
  INITANGLE[5] = 90;
  ANA[5] = 5;
  
  for (int i = 0; i < SERVOS; i++){
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
    value[i] = 0;
    idle[i] = 0;
    previousAngle[i]=INITANGLE[i];
  }
  
}
void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print("You sent me: ");
    Serial.println(data);
    
    if(data == "0"){
      delay(1000);
      myservo[0].write(10);
      for(int i = 100; i <170; i+=1){
        myservo[3].write(i);
        delay(100);
      }
      delay(1000);
      myservo[0].write(60);
      for(int i = 90; i<150; i+=1){
        myservo[5].write(i);
        delay(100);
      }
      myservo[0].write(10);
      delay(100);
      for(int i = 170; i>150; i-=1){
        myservo[3].write(i);
        delay(100);
      }
      for(int i = 150; i>100; i-=1){
        myservo[3].write(i);
        delay(100);
        myservo[5].write(i);
        delay(100);
      }
      for(int i = 100; i>90; i-=1){
        myservo[5].write(i);
        delay(100);
      }
      
      delay(1000);
    }

    else if(data == "1"){
      delay(1000);
      myservo[0].write(0);
      for(int i = 100; i <140; i+=1){
        myservo[3].write(i);
        delay(100);
      }
      delay(1000);
      for(int i = 0; i<90; i+=1){
        myservo[0].write(i);
        delay(100); 
      }
      for(int i = 90; i>30; i-=1){
        myservo[5].write(i);
        delay(100);
      }
      myservo[0].write(0);
      delay(100);
      for(int i = 140; i>100; i-=1){
        myservo[3].write(i);
        delay(100);
      }
      for(int i = 30; i<90; i+=1){
        myservo[5].write(i);
        delay(100);
      }
      delay(1000);
  
    }

    else if(data == "2"){
      delay(1000);
      myservo[0].write(10);
      for(int i = 100; i <170; i+=1){
        myservo[3].write(i);
        delay(30);
      }
      delay(1000);
  
      for(int i = 90; i>30; i-=1){
        myservo[4].write(i);
        delay(30);
        myservo[3].write(i+80);
        delay(30);
      }
      myservo[0].write(10);
      delay(100);
      for(int i = 110; i>100; i-=1){
        myservo[3].write(i);
        delay(30);
      }
      for(int i = 30; i < 90; i+=1){
        myservo[4].write(i);
        delay(30);
      }
      delay(1000);
      
     }    

    else if (data == "3"){
      for(int i = 0; i < 5; i++){
      myservo[i].write(90);
      delay(100);
      }
    }     
  }

  
  delay(500); // 로봇팔 속도조정을 위한 딜레이
 
    for (int i = 0; i < SERVOS; i++){
      value[i] = analogRead(ANA[i]);
      currentAngle[i] = myservo[i].read();
    
      if (value[i] > 612) {
        idle[i] = 0;
      
        if (currentAngle[i] < MAX[i]) ++currentAngle[i];
        if (!myservo[i].attached()){
          myservo[i].attach(PIN[i]);
        }
        myservo[i].write(currentAngle[i]);     
      } else if (value[i] < 412) {
      idle[i] = 0;
      if (currentAngle[i] > MIN[i]) --currentAngle[i];
      if (!myservo[i].attached()){
        myservo[i].attach(PIN[i]);
      }
      myservo[i].write(currentAngle[i]);    
    } else {
      ++idle[i];
    }
    if (idle[i] > 10000){
      myservo[i].detach(); //서보모터를 일정시간 사용하지 않으면 연결을 끊어둔다.
      idle[i] = 0;
    }  
  }  

}
