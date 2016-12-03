#define M1 2
#define E1 3
#define M2 4
#define E2 5

int pins[4] = {9,10,11,12};
bool readPins[4];
int runState = 0;
int perference = 0 ;
bool status = false;
bool swStatus = true;
int delayTime = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=2;i<6;++i) pinMode(i,OUTPUT);
  for(int i=0;i<4;++i) pinMode(pins[i],INPUT);
  pinMode(8,INPUT);
  digitalWrite(M1,LOW);
  digitalWrite(M2,HIGH);
  
}

void loop() {
  for(int i=0;i<4;++i){
    readPins[i] = digitalRead(pins[i]);
  }
  
  if(readPins[3] == LOW){
    perference = 1;
  }else if(readPins[3] ==HIGH && perference == 1){
    perference = 0;
  }else if(readPins[0] == HIGH && perference == -1){
    perference = 0;
  }else if(readPins[0] ==LOW){
    perference = -1;
  }

  if(digitalRead(8) == LOW && swStatus == true){
    status = !status;
    swStatus = false;
  }else if(digitalRead(8) == HIGH && swStatus == false){
    swStatus = true;
  }
  
  if(status){
     if((readPins[0] == HIGH && readPins[1]==HIGH && readPins[2]==HIGH && readPins[3]==HIGH)  || (readPins[0] == HIGH && readPins[1] == LOW && readPins[2] == LOW && readPins[3] == HIGH))
    {
      goFoward();
    }else
    if(readPins[0] ==LOW || readPins[3] == LOW)  // 맨 오른쪽 센서(A0)에 라인이 감지된 경우
    {
      if(perference == -1) turn(70,120,HIGH,HIGH);
      else if(perference == 1)turn(120,70,LOW,LOW);
    }
    else if(readPins[1] ==LOW)  // 오른쪽에서 두 번째 센서(A1)에 라인이 감지된 경우
    {
      turn(90,120,LOW,HIGH); 
    }
    else if(readPins[2] ==LOW)  // 왼쪽에서 두 번째 센서(A4)에 라인이 감지된 경우
    {
      turn(120,90,LOW,HIGH);
    }
    else
    {
      turn(120,70,LOW,LOW);
    }
  }else if(status == false){
    Stop();
  }
  //알고리즘 끝
  delay(10);
   
}

void Stop(){
    digitalWrite(E2,LOW);
    digitalWrite(E1,LOW);
}
void goFoward(){
    analogWrite(E1,120);
    analogWrite(E2,120);
}
void turn(int l,int r,bool l2 ,bool r2 ){
    digitalWrite(M1,l2);
    digitalWrite(M2,r2);
    analogWrite(E1,l);
    analogWrite(E2,r);
}

