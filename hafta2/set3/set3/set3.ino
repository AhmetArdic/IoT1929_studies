
#include <Servo.h>
#include <Joystick.h>

Joystick_ joystick;
Servo servo0;
Servo servo1;

#define pot0 A0
#define pot1 A1
#define servo_pin0 5
#define servo_pin1 6 

void setup() {
  Serial.begin(9600);
  joystick.begin();
  servo0.attach(servo_pin0);
  servo1.attach(servo_pin1);
}

void loop() {
  joystick.setXAxis(analogRead(pot0));
  joystick.setYAxis(analogRead(pot1));
  int aci90 = map(joystick.getXAxis(), 0, 1023, 0, 90);
  int aci180 = map(joystick.getYAxis(), 0, 1023, 0, 180);

  servo0.write(aci90);
  servo1.write(aci180);
  delay(100);
}
