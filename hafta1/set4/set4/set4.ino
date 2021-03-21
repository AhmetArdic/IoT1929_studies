#define led 2
#define pot A0
#define dc 3

#define LIMIT 4000


void setup()
{
  Serial.begin(9600); 
  pinMode(led, OUTPUT);
  pinMode(dc, OUTPUT);
}

void loop()
{
  int pot_deger = analogRead(pot);
  int motor = map(pot_deger,0,1023,0,255);
  analogWrite(dc, motor);
  int rpm = map(motor,0,255,0,5555);
  if(rpm > LIMIT){
  	digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
  }
}
