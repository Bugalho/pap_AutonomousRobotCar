#define led 14
void setup() {
  pinMode(led,OUTPUT);
}

void loop() {
  digitalWrite(led,LOW);
  delay(100);
  digitalWrite(led,HIGH);
  delay(100);
  
}
