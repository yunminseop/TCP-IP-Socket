#include <WiFi.h>

// setup
const char* ssid = "wifi SSID";  // WIFI
const char* password = "password";   // WIFI 비밀번호

void setup() {
  Serial.begin(115200);  // Serial Monitor begins

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Wifi connecting...");
  }

  Serial.println("success");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // ESP32 IP address

  server.begin();  // server begins
}

void loop() {
  WiFiClient client = server.available();

  while (client.connected())
  {
    client.setTimeout(20);
    String data = client.readStringUntil('\n'); // read string until ("\n")
    data.trim(); // trim empty space in front of /rear of the data.
    
    
    // for example,
    if data == '1':
    	client.print('connect') // send message to client.
    	Serial.println('connect') // print message on my monitor.
   }

    
}
