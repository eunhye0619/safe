#include "HUSKYLENS.h"
#include <Wire.h>

HUSKYLENS huskylens;

void setup() {
  Serial.begin(9600);
  Wire.begin();

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
        Serial.println(F("Locating survivors")); // 생존자 위치 파악
        break;
      case 2:
        Serial.println(F("Identifying the location of the fire")); // 화재 위치 파악
        break;
      case 3:
        Serial.println(F("Identifying the location of the affected areas")); // 피해 장소 위치 파악
        break;
      default:
        Serial.println(F("No damage & No casualties"));
        break;
    }
  } else {
    Serial.println(F("No object detected"));
  }

  delay(1500); // 1.5초 대기 후 출력
}
