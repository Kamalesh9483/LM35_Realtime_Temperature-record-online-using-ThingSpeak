#include "WiFi.h"
#include "ThingSpeak.h"

#define CHANNEL_ID 1388315
#define CHANNEL_API_KEY "93ISYROX1RQSQF9G"

// web related setup
String writeAPIKey = "93ISYROX1RQSQF9G";  // paste Application Programming Interface(API) write key from ThingSpeak website
const char* ssid = "JioFiber 1";// Service Set IDentifier(SSID) is the network’s name
const char* password = "Dexiatoungjio";
const char* server = "api.thingspeak.com"; // get this URL from ThingSpeak website

// Temp related setup
const int Analog_channel_pin = 33;
int input_val = 0;
float celsius = 0;
float farenheit = 0;

WiFiClient client; // instantiating the client object

void setup() {
Serial.begin(115200); // setting baud rate
WiFi.disconnect(); // disconnect any previous wifi connection
delay(10);
WiFi.begin(ssid, password); // pass SSID and password as arguments 

Serial.println();
Serial.println();
Serial.println("Connecting to Wifi...");

WiFi.begin(ssid, password); 

// loop to check status of WiFi, till WL_CONNECTED is obtained the loop runs printing "." every 500ms
// WL_CONNECTED: assigned when connected to a WiFi network
while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

// Once WiFi is connected, the SSID is printed
Serial.print("");
Serial.print("ESP 32 connected to WiFi");
Serial.print(ssid);
Serial.println();

ThingSpeak.begin(client);
}

void loop() {
input_val = analogRead(Analog_channel_pin);
celsius = (3.3*input_val*100.0)/(2048*10);                                             
farenheit = (celsius * 1.8) + 32;            // conversion for celsius to farenheit

  ThingSpeak.writeField(CHANNEL_ID, 1, celsius, CHANNEL_API_KEY); 
  ThingSpeak.writeField(CHANNEL_ID, 2, farenheit, CHANNEL_API_KEY); 
      
    Serial.print("Temperature: ");
    Serial.print(celsius);
    Serial.print("\n");
    Serial.println("Uploaded to ThingSpeak server");

 Serial.println("Waiting to upload next reading.....");
 Serial.println();
 delay(15000);  // 15 sec delay to upload the next temp data to ThingSpeak server
}
