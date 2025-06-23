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
Some other codes
void setup() {
  pinMode(2, OUTPUT); // GPIO2 is the onboard LED on some ESP32 boards
}

void loop() {
  digitalWrite(2, HIGH); // turn LED on
  delay(1000);           // wait 1 second
  digitalWrite(2, LOW);  // turn LED off
  delay(1000);           // wait 1 second
}
✅ 2. Read Analog Sensor (e.g., Potentiometer)
void setup() {
  Serial.begin(115200);
}

void loop() {
  int analogValue = analogRead(34); // Use GPIO34 (input only)
  Serial.println(analogValue);
  delay(500);
}
✅ 3. Control LED with Push Button
#define LED 2
#define BUTTON 4

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BUTTON) == LOW) { // Button pressed
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
✅ 4. WiFi Connection Test
#include <WiFi.h>

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}
✅ 5. Simple Web Server (Control LED from Browser)
#include <WiFi.h>

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        client.flush();

        if (request.indexOf("/on") != -1) {
          digitalWrite(2, HIGH);
        } else if (request.indexOf("/off") != -1) {
          digitalWrite(2, LOW);
        }

        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println();
        client.println("<h1>ESP32 Web Server</h1>");
        client.println("<p><a href=\"/on\">Turn On</a></p>");
        client.println("<p><a href=\"/off\">Turn Off</a></p>");
        break;
      }
    }
    client.stop();
  }
}


