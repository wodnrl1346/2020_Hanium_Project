#include <SPI.h> // NFC 통신 라이브러리
#include <MFRC522.h> // RFID 통신 라이브러리
#include <LiquidCrystal_I2C.h>  // LCD 라이브러리
#include <SoftwareSerial.h> // 블루투스 라이브러리

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);  // Instance of the class

MFRC522::MIFARE_Key key;

LiquidCrystal_I2C lcd(0x27, 16, 2);

SoftwareSerial BTSerial(7, 6);

// Init array that will store new NUID
byte nuidPICC[4];

void setup() {
  lcd.begin();
  pinMode(3, OUTPUT); // 빨간불 신호등
  pinMode(4, OUTPUT); // 파란불 신호등
  pinMode(4, OUTPUT); // 초록불 신호등

  SPI.begin(); // Init SPI bus
  rfid.PCD_Init();  // Init MFRC552

  for (byte i = 0; i < 6; i++){
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  digitalWrite(5, High); // 초록 신호등 켜짐
  delay(3000); // 3초동안
  digitalWrite(5, Low); // 초록 신호등 꺼짐

  char data='0';
  BTSerial.write(data); // 블루투스 데이터 송신

  digitalWrite(3, High); // 빨간 신호등 켜짐
  delay(3000);
  digitalWrite(3, Low); // 빨간 신호등 꺼짐

  if ( ! rfid.PICC_IsNewCardPresent()) // 새로운 카드가 찍히지 않았을 경우 계속 반복
    return;

  // verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K ) {
    Serial.println(F("Your tag is not of type NIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0]) ||  // nfc1 카드가 찍히면 0번 배열에 저장
    rfid.uid.uidByte[1] != nuidPICC[1] || // nfc2 카드가 새로 찍히면 1번 배열에 저장 -> nfc1이 찍혔을 경우 인식X
    rfid.uid.uidByte[2] != nuidPICC[2] ||
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been deteected."))

    // store NUID into nuidPICC array
    for (byte i = 0; i<4; i++){
      nuidPICC[i] = rfid.uid.uidByte[i];
    }

    if (rfid.uid.uidByte[0] == 138 && rfid.uid.uidByte[1] == 187
        && rfid.uid.uidByte[2] == 245 && rfid.uid.uidByte[3] == 129) {    //******노인/어린이 카드 태그******
      lcd.print("Red green blind");
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH); // 파란신호등 켜짐
      delay(5000);  // 5초 동안
      digitalWrite(4, LOW);     
      lcd.clear();
        }
        
    if (rfid.uid.uidByte[0] == 167 && rfid.uid.uidByte[1] == 208
        && rfid.uid.uidByte[2] == 66 && rfid.uid.uidByte[3] == 180) {    //******노인/어린이 카드 태그******
      lcd.print("Children & Elders");
      digitalWrite(5, LOW); // 초록 신호등 켜짐
      delay(7000);  // 7초 동안
      digitalWrite(5, LOW);     
      lcd.clear();
        }

    else{
      lcd.print("Blind person");
      char data='1';
      BTSerial.write(data);    
    }    
      }

  else {
    Serial.println(F("This card is not vailable"));
  }
}
