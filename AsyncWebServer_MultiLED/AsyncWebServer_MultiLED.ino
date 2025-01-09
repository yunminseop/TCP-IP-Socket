#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "AIE_509_2.4G";
const char *password = "addinedu_class1";
const int RED = 21;
const int YELLOW = 22;
const int GREEN = 23;

AsyncWebServer server(80); // port number. (webserver = 8080 or 80)


const char html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <body>
  <center>
  <h1>Hello, MinSeop's ESP32 Web Server - Async3</h1>
  <div>LED PIN 21 :
  <input type="checkbox" onchange="toggleCheckBox1(this)" />
  </div><br>
  <div>LED PIN 22 :
  <input type="checkbox" onchange="toggleCheckBox2(this)" />
  </div><br>
  <div>LED PIN 23 :
  <input type="checkbox" onchange="toggleCheckBox3(this)" />
  </div>
  <script>
  function toggleCheckBox1(element) {
    var req = new XMLHttpRequest();
    if (element.checked)
    {
      req.open("GET", "/on1", true);
    }
    else
    {
      req.open("GET", "/off1", true);
    }
    req.send();
  }
  function toggleCheckBox2(element) {
    var req = new XMLHttpRequest();
    if (element.checked)
    {
      req.open("GET", "/on2", true);
    }
    else
    {
      req.open("GET", "/off2", true);
    }
    req.send();
  }
  function toggleCheckBox3(element) {
    var req = new XMLHttpRequest();
    if (element.checked)
    {
      req.open("GET", "/on3", true);
    }
    else
    {
      req.open("GET", "/off3", true);
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
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

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
  server.on("/on1", HTTP_GET, [] (AsyncWebServerRequest *req){
    digitalWrite(RED, HIGH);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/off1", HTTP_GET, [] (AsyncWebServerRequest *req){
    digitalWrite(RED, LOW);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/on2", HTTP_GET, [] (AsyncWebServerRequest *req){
    digitalWrite(YELLOW, HIGH);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/off2", HTTP_GET, [] (AsyncWebServerRequest *req){
    digitalWrite(YELLOW, LOW);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/on3", HTTP_GET, [] (AsyncWebServerRequest *req){
    digitalWrite(GREEN, HIGH);
    req->send_P(200, "text/html", html, processor);
  });
  server.on("/off3", HTTP_GET, [] (AsyncWebServerRequest *req){
    digitalWrite(GREEN, LOW);
    req->send_P(200, "text/html", html, processor);
  });
  server.begin();

  Serial.println("HTTP Server Started!");
  delay(100);
}



void loop() {
  // put your main code here, to run repeatedly
}