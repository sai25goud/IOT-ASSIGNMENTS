const int buzzer = 22;
void setup() {
  // put your setup code here, to run once:
pinMode(buzzer,OUTPUT);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(buzzer,HIGH);
Serial.println("BUZZER ON\n");
delay(2000);

digitalWrite(buzzer,LOW);
Serial.println("BUZZER OFF\n");
delay(2000);
}
