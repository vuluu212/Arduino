#define PIR_PIN 33  // Chân kết nối cảm biến PIR

void setup() {
  // Khởi động giao tiếp nối tiếp (serial communication)
  Serial.begin(9600);

  // Thiết lập chân PIR_PIN là đầu vào
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  // Đọc giá trị từ cảm biến PIR
  int pirState = digitalRead(PIR_PIN);

  // Kiểm tra trạng thái của cảm biến
  if (pirState == HIGH) {
    // Cảm biến phát hiện chuyển động
    Serial.println("Motion detected!");
  } else {
    // Không phát hiện chuyển động
    Serial.println("No motion.");
  }

  // Chờ một chút trước khi đọc lại
  delay(1000);
}
