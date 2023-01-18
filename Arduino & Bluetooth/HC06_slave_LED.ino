#include <SoftwareSerial.h> //블루투스 시리얼 통신 라이브러리 추가
SoftwareSerial BTSerial(2, 3); //블루투스 객체 선언 및 초기화 (Tx, Rx)

//LED 핀 설정
int LED1 = 13;

void setup() {
  BTSerial.begin(9600); //블루투스 통신 시작 (통신속도)
  pinMode(LED1, OUTPUT); //LED 출력으로 핀모드 설정
}

void loop() {
  if(BTSerial.available()){
    //블루투스 통신이 사용되었다면?
    char bt;
    bt = BTSerial.read(); //블루투스 통신 전달 값 입력
    if(bt == '1') { // 'bt' 변수에 전달된 값이 '1'이라면?
      digitalWrite(LED1, HIGH); //LED 켜기 'on'
    }
    else if(bt == '0'){ // 'bt' 변수에 전달된 값이 '0'이라면?
      digitalWrite(LED1, LOW); //LED 끄기 'off'
    }
  }
}
