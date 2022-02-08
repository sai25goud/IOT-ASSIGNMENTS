#include  <DHT_U.h>
#include "ThingSpeak.h"
#include "WiFi.h"

char ssid[] = "R.K";
char pass[] = "20002001";

int ledPin = 13;
int PIR = 2;
int pirState = LOW;
int val = 0;
int PersonCount;
int LEDCount;
WiFiClient client;

//-------ThingSpeak Details------//
unsigned long myChannelField = 1647916;
const int ChannelField1 = 1;
const int ChannelField2 = 2;
const char * myWriteAPIKey = "3TPSCRI23HPEI77J";

void setup() {
  // put your setup code here, to run once:
pinMode(ledPin, OUTPUT); 
pinMode(ledPin, INPUT); 
Serial.begin(115200);
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);

}

void loop(){
  // -------------WiFi--------------//

  if(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print("Attempting to Connect to SSID: ");
    Serial.println(ssid);
    
  while(WiFi.status()!= WL_CONNECTED)
  {
    WiFi.begin(ssid,pass);
    Serial.print(".");
    delay(5000);
  }

  Serial.println("\nConnected");
}

val = digitalRead(PIR); // read input value
if (val == HIGH) {
// check if the input is HIGH
digitalWrite(ledPin, HIGH); // turn LED ON
if (pirState == LOW) {
// we have just turned on
Serial.println("Motion detected!");
PersonCount++;
LEDCount++;
// We only want to print on the output change, not state
pirState = HIGH;
}
} else {
digitalWrite(ledPin, LOW); // turn LED OFF
if (pirState == HIGH){
// we have just turned of
Serial.println("Motion ended!");
// We only want to print on the output change, not state
pirState = LOW;
}
}

ThingSpeak.writeField(myChannelField, ChannelField1, PersonCount, myWriteAPIKey);
ThingSpeak.writeField(myChannelField, ChannelField2, LEDCount, myWriteAPIKey);

delay(500);
}
