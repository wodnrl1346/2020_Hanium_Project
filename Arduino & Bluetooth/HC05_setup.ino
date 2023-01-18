#include <SoftwareSerial.h> //일반 입출력 데이터 핀을 TX, RX핀으로 동작할 수 있게 해주는 라이브러리
SoftwareSerial BTSerial(7, 6); //Create a Bluetooth module Object. BTSerial(Tx pin, Rx pin);

int ENpin = 2;

void setup() {
  pinMode(ENpin, OUTPUT); //Set to ENpin Number OUTPUT
  digitalWrite(ENpin,HIGH); // HIGH: AT mode, LOW: Normal mode
  
  Serial.begin(9600); //Start serial communication
  BTSerial.begin(9600); //Start bluetooth communication
  Serial.println("ATcommand"); //ATcommand Start 
}

void loop() {
  //if there is a data vlue being sent to Bluetooth.
  if (BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  //if there is a data vlue being sent to Serial communication  
  if (Serial.available()) {
    BTSerial.write(Serial.read());
  }  
}
