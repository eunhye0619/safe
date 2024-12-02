 #include <Adafruit_NeoPixel.h>

#define NUMPIXELS      8    // 네오픽셀 링의 LED 개수
#define BRIGHTNESS     50   // LED 밝기 (0에서 255 사이의 값)
#define Red      0
#define White    1

int Led = 6;
int echo = 8;
int trig = 12;
int buzzer = 3;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, Led, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo,INPUT);
  pinMode(Led,OUTPUT);
  pinMode(buzzer, OUTPUT);
  strip.begin();              // 네오픽셀 초기화
  strip.setBrightness(BRIGHTNESS); // 밝기 설정
  strip.show();
  setAllWhite(Red);              // 모든 LED를 빨간색으로 설정
}

void loop() {
  float cycl;
  float dist;

  digitalWrite(trig, LOW);
  delay(2);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);

  cycl = pulseIn(echo, HIGH);

  dist = ((340*cycl)/10000)/2;

  Serial.print(dist);
  Serial.println("cm");
  delay(500);

  if(dist <= 20){
    setAllWhite(White);
    tone(buzzer, 65);
    delay(100);
  }
  else{
    setAllWhite(Red);
    noTone(buzzer);
    delay(100);
  }
}

void setAllWhite(int color) {
  if(color == 0){
    for(int i=0; i<NUMPIXELS; i++) {
      strip.setPixelColor(i, strip.Color(255, 0, 0)); // LED 색상을 하얀색으로 설정
    }
  }
  else if(color==1){
    for(int i=0; i<NUMPIXELS; i++) {
      strip.setPixelColor(i, strip.Color(255, 255, 255)); // LED 색상을 빨간색으로 설정
    }
  }
  
}
