#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "AIE_509_2.4G";
const char *password = "addinedu_class1";
const int LED = 21;

AsyncWebServer server(80); // port number. (webserver = 8080 or 80)


const char html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <body>
  <center>
  <h1>Hello, MinSeop's ESP32 Web Server - Async2</h1>
  <div>LED PIN 21 :
  <input type="checkbox" onchange="toggleCheckBox(this)" />
  </div>
  <script>
  function toggleCheckBox(element) {
    var req = new XMLHttpRequest();
    if (element.checked)
    {
      req.open("GET", "/on", true);
    }
    else
    {
      req.open("GET", "/off", true);
    }
    req.send();
  }
  </script>
  </center>
  </body>
  </html>
  )rawliteral";

String processor(const String& var)
{
  Serial.println(var);
  return var;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("ESP32 Web Server Start");
  Serial.println(ssid);
  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();

  Serial.print("IP addess: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *req){
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/on", HTTP_GET, [] (AsyncWebServerRequest *req){
    digitalWrite(LED, HIGH);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/off", HTTP_GET, [] (AsyncWebServerRequest *req){
    digitalWrite(LED, LOW);
    req->send_P(200, "text/html", html, processor);
  });
  server.begin();

  Serial.println("HTTP Server Started!");
  delay(100);
}



void loop() {
  // put your main code here, to run repeatedly
}