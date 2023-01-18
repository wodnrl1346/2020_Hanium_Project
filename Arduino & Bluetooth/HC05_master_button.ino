#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);   //bluetooth module Tx:Digital 2 Rx:Digital 3

int btn = 13;
void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(8,HIGH);
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(btn, INPUT);
}
void loop() {
  char data;
  int value;
  value = digitalRead(btn);
  if(value == 1){
    data = '1';
  }else{
    data = '0';
  }
  BTSerial.write(data);
  Serial.println(data);
}
