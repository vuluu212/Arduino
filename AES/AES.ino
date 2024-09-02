#include "mbedtls/aes.h"
#include <Arduino.h>

char *key = "doanchuyennganhm";
char *inputt = "chao ban hello ";
unsigned char output[16];
unsigned char decrypted[16];
char result[33];

void encryptData(mbedtls_aes_context *aes, const char *key, const char *input, unsigned char *output, char *result) {
  mbedtls_aes_setkey_enc(aes, (const unsigned char *)key, strlen(key) * 8);
  mbedtls_aes_crypt_ecb(aes, MBEDTLS_AES_ENCRYPT, (const unsigned char *)input, output);
  for (int i = 0; i < 16; i++) {
    char str[3];
    sprintf(str, "%02x", (int)output[i]);
    strcat(result, str);
  }
}

void decryptData(mbedtls_aes_context *aes, const char *key, const unsigned char *input, unsigned char *output) {
  mbedtls_aes_setkey_dec(aes, (const unsigned char *)key, strlen(key) * 8);
  mbedtls_aes_crypt_ecb(aes, MBEDTLS_AES_DECRYPT, input, output);
}

void setup() {
  Serial.begin(115200);

  mbedtls_aes_context aes;
  mbedtls_aes_init(&aes);
  mbedtls_aes_free(&aes);
  // // Mã hóa dữ liệu
  encryptData(&aes, key, inputt, output, result);
  Serial.print("Encrypted: ");
  Serial.println(result);

  //giai ma
  String message = "03515a5cdae8072ef0c8bd1382a71c0d";//chao tat ca    |
  int numElements = message.length() / 2;
  if (numElements != 16) {
    Serial.println("Error: The input hex string must have exactly 16 elements.");
    return;
  }
  unsigned char output[numElements];
  for (int i = 0; i < numElements; i++) {
    String hex = message.substring(i * 2, i * 2 + 2);
    output[i] = strtol(hex.c_str(), NULL, 16);
  }
  
  for (int i = 0; i < numElements; i++) {
    Serial.println(output[i]);
  }

  decryptData(&aes, key, output, decrypted);
  // Chuyển mảng decrypted thành chuỗi
  char decryptedString[numElements + 1];
  for (int i = 0; i < numElements; i++) {
    decryptedString[i] = decrypted[i];
  }
  decryptedString[numElements] = '\0';
  // In ra chuỗi đã giải mã
  Serial.print("Decrypted: ");
  Serial.println(decryptedString);
}

void loop() {}