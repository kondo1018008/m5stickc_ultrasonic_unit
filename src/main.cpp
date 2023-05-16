#include <M5StickCPlus.h>
#include <Unit_Sonic.h>

// UltrasonicユニットをGROVEポートに接続します
SONIC_I2C sonic;

// 物体がこの距離以内に入ったら挨拶を表示します
const float greetingDistance = 40.0; // cm

// 前回のループで物体が近くにいたかどうかを追跡します
bool objectWasNear = false;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextSize(4);
  sonic.begin();
}

void loop() {
  float distance = sonic.getDistance()/10;
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  // M5.Lcd.printf("Distance: %.2f cm", distance/10);

   if (distance < greetingDistance) {
    // 物体が近くにある場合
    if (!objectWasNear) {
      // 前回のループで物体が近くになかった場合は、挨拶を表示します
      M5.Lcd.println("Hello, there!");
      objectWasNear = true;
    }
  } else {
    // 物体が遠くにある場合
    if (objectWasNear) {
      // 前回のループで物体が近くにいた場合は、"Goodbye!"を表示します
      M5.Lcd.println("Goodbye!");
      objectWasNear = false;
    }
  }

  delay(500);
}