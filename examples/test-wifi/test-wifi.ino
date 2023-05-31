#include <WiFi.h>

const char* ssid = "Your SID";
const char* password = "Your Password";

void setup() {
  Serial.begin(115200);
  while (!Serial);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
}

void loop() {
  Serial.print(WiFi.localIP());
  Serial.print(" RRSI: ");
  Serial.println(WiFi.RSSI());
  delay(3000);

}
