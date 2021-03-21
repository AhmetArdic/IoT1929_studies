
int led[] = {2,3,4,5,6};

void setup()
{
  pinMode(led[5], OUTPUT);
}

void loop()
{
  for(int i=0 ; i<5 ; i++){
    digitalWrite(led[i], HIGH);
    delay(500);
    digitalWrite(led[i], LOW);
  }
  for(int i=4 ; i>=0 ; i--){
    digitalWrite(led[i], HIGH);
    delay(500);
    digitalWrite(led[i], LOW);
  }
}
