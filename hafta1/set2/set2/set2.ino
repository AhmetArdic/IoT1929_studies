#define sari 7
#define kirmizi 6
#define yesil 5

#define delay10 10000

int switchh(int led) {
  switch (led) {
    case 1:
      digitalWrite(kirmizi, HIGH);
      delay(delay10);
      return 1;
    case 2:
      digitalWrite(sari, HIGH);
      digitalWrite(kirmizi, HIGH);
      delay(delay10);
      return 0;
    case 3:
      digitalWrite(sari, LOW);
      digitalWrite(kirmizi, LOW);
      delay(delay10 / 5);

      digitalWrite(yesil, HIGH);
      delay(delay10 / 2);
      digitalWrite(yesil, LOW);
  }
}
void setup() {
  pinMode(sari, OUTPUT);
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil, OUTPUT);
}
void loop() {
  int kirmizi_sure = switchh(1);
  if (kirmizi_sure) {
    switchh(2);
  }
  switchh(3);
}
