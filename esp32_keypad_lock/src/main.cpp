#define BLYNK_TEMPLATE_ID "TMPL61OBe7jS1"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "uxB4f9FEK9IncSHv8319K91dP7a2ydge"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Keypad.h>

#define RELAY_PIN 23

// WiFi
char ssid[] = "Yotam";
char pass[] = "0545722877";

BlynkTimer timer;

// ========================
// Keypad
// ========================
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {17, 5, 18, 19};
byte colPins[COLS] = {15, 21, 4, 16};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ========================
// סיסמה
// ========================
String correctCode = "321";
String inputCode = "";

// ========================
// שליטה מהאפליקציה
// ========================
BLYNK_WRITE(V0) {
  int state = param.asInt();

  Serial.print("Button State: ");
  Serial.println(state);

  if (state == 1) {
    Serial.println("🔓 OPEN (App)");
    digitalWrite(RELAY_PIN, LOW);
  } else {
    Serial.println("🔒 CLOSE (App)");
    digitalWrite(RELAY_PIN, HIGH);
  }
}

// ========================
// התחברות ל-Blynk
// ========================
BLYNK_CONNECTED() {
  Serial.println("Blynk Connected!");
}

// ========================
// setup
// ========================
void setup() {
  Serial.begin(115200);
  delay(2000);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

// ========================
// loop
// ========================
void loop() {
  Blynk.run();

  // ===== Keypad Logic =====
  char key = keypad.getKey();

  if (key) {
    Serial.print("Pressed: ");
    Serial.println(key);

    if (key == '#') {
      Serial.print("Entered Code: ");
      Serial.println(inputCode);

      if (inputCode == correctCode) {
        Serial.println("✅ Correct Code → OPEN");

        digitalWrite(RELAY_PIN, LOW);
        delay(3000);   // פתוח ל-3 שניות
        digitalWrite(RELAY_PIN, HIGH);

      } else {
        Serial.println("❌ Wrong Code");
      }

      inputCode = "";
    }

    else if (key == '*') {
      inputCode = "";
      Serial.println("🔄 Reset Input");
    }

    else {
      inputCode += key;
      Serial.print("Current Input: ");
      Serial.println(inputCode);
    }
  }
}

