#include <WiFi.h>
#include <Arduino.h>
#include <ESP32Servo.h>

Servo servoIn, servoOut;
int servoGateInput = 19;   // Chân số 3 của ESP32
int servoGateOutput = 18;  // Chân số 3 của ESP32

const char* ssid = "VU LUU";
const char* password = "vuluu0905491690";
// const char *ssid = "Hong Be Oii";
// const char *password = "khongchodau";
const uint16_t port = 8090;
const char* host = "192.168.1.4";

#define ir_in1 26
#define ir_in2 25
#define ir_out1 33
#define ir_out2 32

void processResponse(int& i) {
  i = 0;
}

WiFiClient client;
int i = 0;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  servoIn.attach(servoGateInput);    // Khởi tạo servo
  servoOut.attach(servoGateOutput);  // Khởi tạo servo
  servoIn.write(0);                  // Đưa servo về vị trí ban đầu (0 độ)
  servoOut.write(0);                 // Đưa servo về vị trí ban đầu (0 độ)
  pinMode(ir_in1, INPUT);
  pinMode(ir_in2, INPUT);
  pinMode(ir_out1, INPUT);
  pinMode(ir_out2, INPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  delay(1000);  // Chờ servo ổn định
}

void gateInput() {
  servoIn.write(90);
  delay(5000);
  servoIn.write(0);
}

void gateOutput() {
  servoOut.write(90);
  delay(5000);
  servoOut.write(0);
}

void ir_InOut(int& i) {
  //Reading Sensor Values
  int A = digitalRead(ir_in1);
  int B = digitalRead(ir_in2);
  int C = digitalRead(ir_out1);
  int D = digitalRead(ir_out2);
  // Serial.println(A);
  // Serial.println(B);
  // Serial.println(C);
  // Serial.println(D);
  A = 1;
  if (A == 1) {
    if (i == 0) {
      client.print("Request");
      client.println();
      Serial.println("gui yeu cau doc bien so len server");
      client.print(1);
      Serial.println("Message sent to server");
      i++;  // Tăng biến đếm sau khi gửi yêu cầu
    }

    while (client.available()) {  // Đọc dữ liệu từ server
      String message = client.readStringUntil('\n');
      Serial.println(message);
      processResponse(i);         // Xử lý phản hồi
      if (message == "mocong") {  //yeucau_mocongvao
        Serial.println("mo cong vao");
        gateInput();
        Serial.println("dong cong vào");
        return;
      }
    }
  }
  if (C == 1) {
    Serial.println("gui yeu cau doc bien so CONGRA len server");
    client.print(11);  // Gửi dữ liệu đến server
    Serial.println("Message sent to server");
    while (client.available()) {  // Đọc dữ liệu từ server
      String message = client.readStringUntil('\n');
      Serial.println(message);
      if (message == "mocong") {  //yeucau_mocong_ra
        Serial.println("mo cong ra");
        gateOutput();
        Serial.println("dong cong ra");
        return;
      }
    }
  }
}

void loop() {
  if (!client.connect(host, port)) {
    Serial.println("Connection to host failed");
    delay(1000);
    return;
  }
  Serial.println("Connected to server successful!");
  while (true) {
    if (!client.connected()) {
      Serial.println("Server disconnected");
      client.stop();
      delay(1000);
      break;
    }
    ir_InOut(i);
    delay(1000);
  }
}