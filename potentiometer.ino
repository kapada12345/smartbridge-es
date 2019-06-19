#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
 
#include <ThingSpeak.h>  
  
const char* ssid = "SmartBridge";  
const char* password = "smartbridge@sb";  
WiFiClient client;  
unsigned long myChannelNumber = 804477;  
const char * myWriteAPIKey = "PGRJBQVS0WEIQD2I";  
const int analogInPin = 2;  // Analog input pin that the potentiometer is attached to
const int analogOut =16; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
  pinMode(analogOut,OUTPUT);
  pinMode(analogInPin,INPUT);
}

void loop() {
  static boolean data_state = false;  
  for (int i=0;i<=10;i++)
    {
        
    int temperature = i;
  Serial.print("Temperature Value is :");  
  Serial.print(temperature);  
   
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel. Here, we write to field 1. 
   ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey);  
  
  delay(30000); // ThingSpeak will only accept updates every 15 seconds.
  // read the analog in value:
  sensorValue = analogRead(analogInPin);
  //analogWrite=(analogOutPin,sensorValue);
  // map it to the range of the analog out: 
    outputValue = (255./4096.)*sensorValue;
  // change the analog out value:
//  analogWrite(analogOut,outputValue);

  // print the results to the Serial Monitor:
  Serial.print("\n sensor = ");
  Serial.print(outputValue);
//Serial.print("\t output = ");
 // Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(50);
}
}
