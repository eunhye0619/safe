#include "HUSKYLENS.h"
#include <Wire.h>

HUSKYLENS huskylens;

// 모터 핀 정의
#define ENA 10   // 속도 제어 핀 (앞쪽 모터들)
#define ENB 11   // 속도 제어 핀 (앞쪽 모터들)
#define IN1 9    // 앞쪽 왼쪽 휠 제어 핀
#define IN2 8    // 앞쪽 오른쪽 휠 제어 핀
#define IN3 12    // 뒤쪽 왼쪽 휠 제어 핀 (제어하지 않음)
#define IN4 13   // 뒤쪽 오른쪽 휠 제어 핀 (제어하지 않음)

// 속도 설정 (0 ~ 255)
int speed = 255; // 50% 속도 (0 ~ 255 범위
void setup() {
  // 시리얼 통신 시작
  Serial.begin(9600);
  Wire.begin();

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // 모터 속도 설정
  analogWrite(ENA, speed);  // 앞쪽 휠의 속도 설정

  // HUSKYLENS 시작 (I2C 모드)
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1. Protocol Type >> I2C"));
    Serial.println(F("2. Connection check"));
    delay(100);
  }
  Serial.println(F("HUSKYLENS ready!"));
}

void loop() {

  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);

  // 앞쪽 오른쪽 휠: 반시계 방향 회전
  digitalWrite(IN3, HIGH);  
  digitalWrite(IN4, LOW);
  
  Serial.println("motor start");
  
  // HUSKYLENS 데이터 요청
  if (!huskylens.request()) {
    Serial.println(F("Request failed"));
    return;
  }

  // 학습된 물체가 있는지 확인
  if (!huskylens.isLearned()) {
    Serial.println(F("No objects learned"));
    return;
  }

  // 물체를 인식했는지 확인
  if (huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();
    Serial.print(F("Detected ID: "));
    Serial.println(result.ID); // 인식된 ID 값 출력

    // ID 값에 따라 다른 메시지 출력
    switch (result.ID) {
      case 1:
        Serial.println(F("Locating survivors")); //생존자 위치 파악
        digitalWrite(IN1, LOW);  
        digitalWrite(IN2, LOW);
      
        // 앞쪽 오른쪽 휠: 반시계 방향 회전
        digitalWrite(IN3, LOW);  
        digitalWrite(IN4, LOW);
        
        Serial.println("motor stop");
        break;
      case 2:
        Serial.println(F("Identifying the location of the fire")); //화재 위치 파악
        digitalWrite(IN1, LOW);  
        digitalWrite(IN2, LOW);
      
        // 앞쪽 오른쪽 휠: 반시계 방향 회전
        digitalWrite(IN3, LOW);  
        digitalWrite(IN4, LOW);
        
        Serial.println("motor stop");
        break;
      case 3:
        Serial.println(F("Identifying the location of the affected areas")); //피해 장소 위치 파악
        digitalWrite(IN1, LOW);  
        digitalWrite(IN2, LOW);
      
        // 앞쪽 오른쪽 휠: 반시계 방향 회전
        digitalWrite(IN3, LOW);  
        digitalWrite(IN4, LOW);
        
        Serial.println("motor stop");
        break;
      default:
        Serial.println(F("No damage & No casualties"));
        digitalWrite(IN1, HIGH);  
        digitalWrite(IN2, LOW);

        // 앞쪽 오른쪽 휠: 반시계 방향 회전
        digitalWrite(IN3, HIGH);  
        digitalWrite(IN4, LOW);
        
        Serial.println("motor start");
        break;
    }
  } else {
    Serial.println(F("No object detected"));
  }

  delay(1500); // 1.5초 대기 후 출력
}
