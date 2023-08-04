


const char* apiServer = "https://node-api-v2-ti2z.onrender.com/api/products"; // Replace with your API server URL

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "AIFARM ROBOTICS FACTORY";
const char* password = "@AIFARM2022";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void loop() {
  StaticJsonDocument<200> jsonDoc;

  jsonDoc["name"] = "Lily";
  jsonDoc["quantity"] = 2;
  jsonDoc["price"] = 4;
  jsonDoc["image"] = "https://images.pexels.com/photos/945443/pexels-photo-945443.jpeg?auto=compress&cs=tinysrgb&w=800";

  String payload;
  serializeJson(jsonDoc, payload);

  HTTPClient http;
  http.begin("https://node-api-v2-ti2z.onrender.com/api/products/");

  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.println("Error on sending request.");
  }

  http.end();

  delay(5000);  // Wait for 5 seconds before sending the next request
}
