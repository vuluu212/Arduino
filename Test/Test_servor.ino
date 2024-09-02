#include <ESP32Servo.h>

Servo myservo;

int pos;   // Vị trí
int count = 0;  
bool direction = true;

void setup() {
  myservo.attach(12); // Attach servo to GPIO 12
  myservo.write(0);
  delay(5000);
}

void loop() {
  if (count == 0) {
    // Chạy servo lên đầu tiên
    for (pos = 60; pos <= 110; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
    count++;
  }

  // Vẫy tay (đưa qua lại)
  if (direction) {
    for (pos = 110; pos >= 60; pos -= 1) {
      myservo.write(pos);
      delay(10);
    }
    direction = false;
  } else {
    for (pos = 60; pos <= 110; pos += 1) {
      myservo.write(pos);
      delay(10);
    }
    direction = true;
  }
}