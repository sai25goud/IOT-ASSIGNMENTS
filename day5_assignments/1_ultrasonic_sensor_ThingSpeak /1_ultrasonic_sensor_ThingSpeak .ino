#include "ThingSpeak.h"
#include "WiFi.h"

//-------Enter your WiFi Details------//
char ssid[] = "R.K";  //SSID
char pass[] = "20002001";  //Password
//-----------------------------------//

const int trigger = 5;
const int echo = 18;
long T;
float distanceCM;
WiFiClient client;

//-------------ThingSpeak Details-----------------//
unsigned long myChannelField = 1646356; //Channel ID
const int ChannelField1 = 1; //for distanceCM
const int ChannelField2 = 2; //for T
const char * myWriteAPIKey = "VJZ4PBAP49RP0ZQA"; //Your Write API Key
//-----------------------------------------------//

void setup() {
  Serial.begin(115200);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
}

void loop() 
{
  //-----------------WiFi Setup-------------------//
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
  Serial.println("\nConnected.");
  }

  digitalWrite(trigger,LOW);
  delay(1);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  T = pulseIn(echo,HIGH);
  distanceCM = (T * 0.034)/2;
  Serial.print("Distance in cm:");
  Serial.println(distanceCM);
      
  //-------------Sending Data to ThingSpeak Cloud---------------//
  ThingSpeak.writeField(myChannelField,ChannelField1, distanceCM, myWriteAPIKey);
  ThingSpeak.writeField(myChannelField,ChannelField2, T, myWriteAPIKey);
  delay(1000);  
}
