#include <Arduino.h>

#define RELAY_PIN 23

void setup() {
  Serial.begin(115200);
  
  pinMode(RELAY_PIN, OUTPUT);

  // ברירת מחדל - כבוי
  digitalWrite(RELAY_PIN, HIGH);

  Serial.println("Lock system started");
}

void loop() {
  Serial.println("Opening lock...");
  
  digitalWrite(RELAY_PIN, LOW); // פתיחה (לרוב Relay עובד הפוך)
  delay(3000); // המנעול פתוח 3 שניות

  Serial.println("Closing lock...");
  
  digitalWrite(RELAY_PIN, HIGH); // סגירה
  delay(3000); // המנעול סגור 3 שניות
}