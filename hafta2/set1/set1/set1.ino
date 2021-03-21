
#define BLYNK_PRINT Serial

#define led1 D0
#define led2 D1
#define led3 D2

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "RapCV1Q-GjQuNDMvgXoZjmrAFoTa2ct1";
char ssid[] = "LelloisPerfect";
char pass[] = "deneme123456";

void blink_led(int led_pin) {
  digitalWrite(led_pin, HIGH);
  delay(5000);
  digitalWrite(led_pin, LOW);
}

BLYNK_WRITE(V1) {
  int pinValue = param.asInt();

  if (pinValue) {
    blink_led(led1);
    blink_led(led2);
    blink_led(led3);
  }
}

void setup(){
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop(){
  Blynk.run();
}
