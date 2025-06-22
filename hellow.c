#include <WiFi.h>

const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

WiFiServer server(80);
#define LED_PIN 2
bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/LED=ON") != -1) {
      ledState = true;
      digitalWrite(LED_PIN, HIGH);
    } else if (request.indexOf("/LED=OFF") != -1) {
      ledState = false;
      digitalWrite(LED_PIN, LOW);
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html\r\n");
    client.println("<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>");
    client.println("<style>body{font-family:sans-serif;text-align:center;}button{font-size:30px;padding:20px;margin:20px;}</style>");
    client.println("</head><body>");
    client.println("<h2>ESP32 LED Web Controller</h2>");

    // Show status
    client.print("<p>LED is currently: <b>");
    client.print(ledState ? "ON" : "OFF");
    client.println("</b></p>");

    // Buttons
    client.println("<a href=\"/LED=ON\"><button style='background:green;color:white;'>ON</button></a>");
    client.println("<a href=\"/LED=OFF\"><button style='background:red;color:white;'>OFF</button></a>");

    client.println("</body></html>");
    client.stop();
  }
}

