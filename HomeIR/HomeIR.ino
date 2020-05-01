#include <IRremote.h>
int RELAY1 = 4;
int RELAY2 = 5;
int RECV_PIN = 2; // 使用數位腳位2接收紅外線訊號
IRrecv irrecv(RECV_PIN); // 初始化紅外線訊號輸入
decode_results results; // 儲存訊號的結構
int x = true;
void setup()
{
  Serial.begin(9600);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);
//  irrecv.blink13(true); // 設為true的話，當收到訊號時，腳位13的LED便會閃爍
  irrecv.enableIRIn(); // 啟動接收
}

void loop() {
  if (irrecv.decode(&results)) { // 接收紅外線訊號並解碼
    Serial.print("results value is "); // 輸出解碼後的資料
    Serial.println(results.value, HEX);
    if (results.value != 0xffffffff) {
      if (x == true) {
        x = false;
        digitalWrite(RELAY1, HIGH);
        Serial.println("open");
      } else {
        x = true;
        digitalWrite(RELAY1, LOW);
        Serial.println("close");
      }
      delay(600);
      Serial.print("set x");
      Serial.println(x);
    }

    irrecv.resume(); // 準備接收下一個訊號
  }
}
