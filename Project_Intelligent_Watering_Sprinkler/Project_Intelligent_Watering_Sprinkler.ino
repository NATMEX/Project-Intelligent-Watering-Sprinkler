//Project Intelligent Watering Sprinkler
// CRE2227 CE SSRU
// Phetcharat Sawangwong No. 61122519006
// Parinya Phonuch No. 61122519018 
// Nattapat Kerdkaew No. 61122519019

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define Pump D0
#define LED D4
#define ON LOW
#define OFF HIGH
//
char auth[] = "XdQVZU_GgZClVg3eekIoiR5R7ag38g0L";
const int sensorPin = A0; 
int sensorState; 
int lastState = 0;
//
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  Serial.print("V1 Slider value is: ");
  Serial.println(pinValue);
  if (pinValue == 1) {
    digitalWrite(Pump, ON);
  }
  else if (pinValue == 0) {
    digitalWrite(Pump, OFF);
  }
}
//
BLYNK_WRITE(V2)
{
  Serial.print("Got a value: ");
  Serial.println(param.asInt());
  
  if(param.asInt() == 0)
  {
    digitalWrite(Pump, OFF);
    Blynk.notify("Stop watering the plants");
  }
  else if(param.asInt() == 1)
  {
    digitalWrite(Pump, ON);
    Blynk.notify("Watering the plants");
  }
}
//
BLYNK_WRITE(V3)
{
  Serial.print("Got a value: ");
  Serial.println(param.asInt());
  
  if(param.asInt() == 0)
  {
    digitalWrite(Pump, OFF);
    Blynk.notify("Stop watering the plants");
  }
  else if(param.asInt() == 1)
  {
    digitalWrite(Pump, ON);
    Blynk.notify("Watering the plants");
  }
}
//
void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(Pump, OUTPUT);
  digitalWrite(Pump, OUTPUT);
  pinMode(sensorPin, INPUT);
  //
  Serial.begin(115200);
  Blynk.begin(auth, "DewZing", "12345678");
}
//
void loop()
{ 
  sensorState = analogRead(sensorPin);
  Serial.println(sensorState);

  if (sensorState > 400 && lastState == 0) {
  Serial.println("needs water, send notification");
  Blynk.notify("Help Me!!!");
  lastState = 0;
  //
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  } 
  else if (sensorState > 250 && lastState == 0) {
  Serial.println("I can endure it");
  lastState = 0;
  //
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(800);
  }
  else {
  Serial.println("I am fine");
  lastState = 0;
  //
  digitalWrite(LED, HIGH);
  delay(2000);
  digitalWrite(LED, LOW);
  delay(1000);
  }
  Blynk.run();
}
