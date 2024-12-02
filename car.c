#define ENA 10   // 속도 제어 핀 (앞쪽 모터들)
#define ENB 11   // 속도 제어 핀 (앞쪽 모터들)
#define IN1 2    // 앞쪽 왼쪽 휠 제어 핀
#define IN2 3    // 앞쪽 오른쪽 휠 제어 핀
#define IN3 4    // 뒤쪽 왼쪽 휠 제어 핀 (제어하지 않음)
#define IN4 5    // 뒤쪽 오른쪽 휠 제어 핀 (제어하지 않음)
#define ENC 12   // 속도 제어 핀 (뒤쪽 모터들)
#define END 13   // 속도 제어 핀 (뒤쪽 모터들)
#define IN6 6    // 앞쪽 왼쪽 휠 제어 핀
#define IN7 7    // 앞쪽 오른쪽 휠 제어 핀
#define IN8 8    // 뒤쪽 왼쪽 휠 제어 핀 (제어하지 않음)
#define IN9 9    // 뒤쪽 오른쪽 휠 제어 핀 (제어하지 않음)

// 속도 설정 (0 ~ 255)
int speed = 255; // 50% 속도 (0 ~ 255 범위)

void setup() {
  // 모터 핀을 출력으로 설정
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENC, OUTPUT);
  pinMode(END, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(IN9, OUTPUT);
}

void loop() {
  // 앞쪽 왼쪽 휠: 반시계 방향 회전 (후진)
  digitalWrite(IN1, HIGH);  
  digitalWrite(IN2, LOW);

  // 앞쪽 오른쪽 휠: 시계 방향 회전 (후진)
  digitalWrite(IN3, LOW);  
  digitalWrite(IN4, HIGH);

  // 뒤쪽 왼쪽 휠: 반시계 방향 회전 (후진)
  digitalWrite(IN6, HIGH);  
  digitalWrite(IN7, LOW);

  // 뒤쪽 오른쪽 휠: 시계 방향 회전 (후진)
  digitalWrite(IN8, LOW);  
  digitalWrite(IN9, HIGH);

  // 모터 속도 설정
  analogWrite(ENA, speed);  // 앞쪽 휠의 속도 설정
  analogWrite(ENB, speed);  // 앞쪽 휠의 속도 설정
  analogWrite(ENC, speed);  // 뒤쪽 휠의 속도 설정
  analogWrite(END, speed);  // 뒤쪽 휠의 속도 설정

  // 후진으로 7초간 이동
  delay(7000);
  //stopMotors();
  delay(3000);
}
