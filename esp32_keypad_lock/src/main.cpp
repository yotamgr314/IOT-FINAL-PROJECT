#define BLYNK_TEMPLATE_ID "TMPL61OBe7jS1"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "uxB4f9FEK9IncSHv8319K91dP7a2ydge"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define RELAY_PIN 23

// WiFi
char ssid[] = "Yotam";
char pass[] = "0545722877";

BlynkTimer timer;

// ========================
// שליטה מהאפליקציה
// ========================
BLYNK_WRITE(V0) {
  int state = param.asInt();

  Serial.print("Button State: ");
  Serial.println(state);

  if (state == 1) {
    digitalWrite(RELAY_PIN, LOW);  // פתח
  } else {
    digitalWrite(RELAY_PIN, HIGH); // סגור
  }
}

// ========================
// התחברות ל-Blynk
// ========================
BLYNK_CONNECTED() {
  Serial.println("Blynk Connected!");
}

// ========================
// טיימר (לא חובה כרגע)
// ========================
void myTimerEvent() {
  Blynk.virtualWrite(V2, millis() / 1000);
}

// ========================
// setup
// ========================
void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Relay כבוי

  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, myTimerEvent);
}

// ========================
// loop
// ========================
void loop() {
  Blynk.run();
  timer.run();
}