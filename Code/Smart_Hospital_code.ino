#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

int TrigPin=7;
int EchoPin=8;
int RedLed=6;
int GreenLed=9;
int NurseLed=13;
int NurseButton=10;
int TempPin=A0;
int CoolingPin=A1;

long duration;
int distance;

void setup() {

pinMode(TrigPin,OUTPUT);
pinMode(EchoPin,INPUT);
pinMode(RedLed,OUTPUT);
pinMode(GreenLed,OUTPUT);
pinMode(NurseLed,OUTPUT);
pinMode(CoolingPin,OUTPUT);
pinMode(TempPin,INPUT);
pinMode(NurseButton,INPUT_PULLUP);

lcd.begin(16,2);
}

void loop() {

  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(TrigPin, LOW);

  duration = pulseIn(EchoPin, HIGH);

  distance = duration * 0.034 / 2;

  lcd.clear();

  if(distance > 15){

    lcd.print("IV Level LOW");

    digitalWrite(RedLed,HIGH);
    digitalWrite(GreenLed,LOW);

  }

  else{

    lcd.print("IV Level OK");

    digitalWrite(RedLed,LOW);
    digitalWrite(GreenLed,HIGH);

  }

  int nurseState = digitalRead(NurseButton);

  if(nurseState == LOW){

    lcd.clear();
    lcd.print("Nurse Needed");
    digitalWrite(NurseLed,HIGH);
    delay(50);
    digitalWrite(NurseLed,LOW);
    delay(50);

  }

  else{
    digitalWrite(NurseLed,LOW);
  }

  int tempValue=analogRead(TempPin);

  float voltage=tempValue*(5.0/1023.0);

  float temperature= voltage*100;

  if(temperature>30){

    digitalWrite(CoolingPin,HIGH);

  }

  else{

    digitalWrite(CoolingPin,LOW);

  }

  delay(500);
}