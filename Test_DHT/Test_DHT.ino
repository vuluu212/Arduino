#include <DHT.h>

// Chân kết nối DHT
#define DHTPIN 33
// Loại cảm biến DHT
#define DHTTYPE DHT11

// Khởi tạo DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Khởi động giao tiếp nối tiếp (serial communication)
  Serial.begin(9600);
  
  // Khởi tạo cảm biến DHT
  dht.begin();
}

void loop() {
  // Chờ một chút giữa các lần đọc dữ liệu
  delay(2000);

  // Đọc giá trị độ ẩm
  float h = dht.readHumidity();
  // Đọc giá trị nhiệt độ (độ C)
  float t = dht.readTemperature();

  // Kiểm tra nếu việc đọc dữ liệu thất bại và hiển thị thông báo lỗi
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Hiển thị giá trị độ ẩm và nhiệt độ lên Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
}

