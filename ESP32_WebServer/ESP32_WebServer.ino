#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "AIE_509_2.4G";
const char *password = "addinedu_class1";
const int LED = 23;

WebServer server(80); // port number. (webserver = 8080 or 80)
void handle_root(); // respond the page request.

const char html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <body>
  <center>
  <h1>Hello, MinSeop's ESP32 Web Server!</h1>
  <a href="on"><button>LED ON</button></a> 
  <a href="off"><button>LED OFF</button></a>
  </center>
  </body>
  </html>
  )rawliteral";

void LED_ON()
{
  Serial.println("ON");
  digitalWrite(LED, HIGH);
  server.send(200, "text/html", html);
}

void LED_OFF()
{
  Serial.println("Off");
  digitalWrite(LED, LOW);
  server.send(200, "text/html", html);
}

void handle_root()
{
  server.send(200, "text/html", html);
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

  server.on("/", handle_root);
  server.on("/on", HTTP_GET, LED_ON);
  server.on("/off", HTTP_GET, LED_OFF);
  server.begin();

  Serial.println("HTTP Server Started!");
  delay(100);
}



void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
