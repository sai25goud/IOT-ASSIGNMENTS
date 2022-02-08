const int ldr=14;
const int LED = 22;
int val;
void setup() {
  // put your setup code here, to run once:
pinMode(ldr,INPUT);
pinMode(LED,OUTPUT);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
val=analogRead(ldr);
//Serial.println(brightness level);
Serial.println(val);
if(val>=1500)
{
  digitalWrite(LED,HIGH);
  delay(1000);
}
else
{
  digitalWrite(LED,LOW);
  delay(1000);
}
}
