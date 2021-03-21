
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo1;

char auth[] = "RapCV1Q-GjQuNDMvgXoZjmrAFoTa2ct1";

char ssid[] = "LelloisPerfect";
char pass[] = "deneme123456";

void setup() {
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  servo1.attach(D6);
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V2) {
  servo1.write(param.asInt());
}
