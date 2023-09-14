#include <Arduino.h>
const int batteryPin = A0;
const int acSupplyPin = A5;
const int relay1Pin = 3;
const int relay2Pin = 13;

bool start = true;
bool timeStatus= false;
bool Reset = true;
bool generatorStatus = true;
unsigned long startTime;
const unsigned long time2hours=800000;
 unsigned long generatorRunTime;
float batteryVoltage;
bool acSupplyStatus;

void setup() {
  Serial.begin(115200);
  pinMode(acSupplyPin, INPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);

  batteryVoltage = analogRead(batteryPin) * (5.0 / 1023.0)*5;
   if(batteryVoltage < 21.5) {
   digitalWrite(relay1Pin, HIGH);
   delay(2000); // Relay 1 on for 2 seconds
   digitalWrite(relay1Pin, LOW);
   delay(5000); //hold 48 seconde
   Serial.println("Generator Start!");
   timeStatus=true; }
}

void loop() {
 
  batteryVoltage = analogRead(batteryPin) * (5.0 / 1023.0)*5;
  acSupplyStatus = digitalRead(acSupplyPin);

  // Print generator status and other relevant information
  Serial.print("Battery Voltage: ");
  Serial.print(batteryVoltage);
  
  Serial.print(" generatortime ");
  Serial.println(generatorRunTime);

  if ((acSupplyStatus || generatorRunTime > time2hours)) {
    digitalWrite(relay2Pin, HIGH);
    delay(1000); // Relay 2 on for 1 second
    digitalWrite(relay2Pin, LOW);
    delay(1000); // Relay 2 on for 1 second
    Serial.print("Generator Status: ");
    Serial.println(!generatorStatus ? "ON" : "OFF");
    generatorStatus = true;
    startTime = millis();
    Reset=true;
  }

  if (batteryVoltage < 21.5  || !Reset) {
    digitalWrite(relay1Pin, HIGH);
    delay(2000); // Relay 1 on for 2 seconds
    digitalWrite(relay1Pin, LOW);
    delay(2000);
    Serial.print("Generator Status: ");
    Serial.println(generatorStatus ? "ON" : "OFF");
    generatorStatus = false;
    Reset=true;
    timeStatus=true;
  }
  if(timeStatus) generatorRunTime = millis() - startTime;
  delay(300); 
}
