#include <Arduino.h>

#include <WiFiClient.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>



const char *ssid = "Dienthoaicuabau";//SSID wifi
const char *password = "anhbau123";//password wifi
const char *mqtt_server = "192.168.11.99";//IPv4 address
const int mqtt_port = 1883;
const char *mqtt_id = "esp32";
long lastMsg = 0;
const int ledPin = 2;
boolean a=0;

#define DHTPIN 4 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


WiFiClient client;
PubSubClient mqtt_client(client);

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print(topic);
  String messageTem;
  
    for (int i = 0; i < length; i++) {
    messageTem += (char)message[i];
  }
  if (String(topic) == "bedroom/fan") {
  
    if(messageTem == "manual"){
      a=0;
      Serial.println("Mode: manual");
     
    }
    else if(messageTem == "auto"){
      Serial.println("Mode: auto");
         
      a=1;
    }
  }
  Serial.println(a);
    if(String(topic) == "bedroom/fan"){
  if(a==0){
        
        if(messageTem == "on"){
      Serial.println("Control: ON");

          digitalWrite(ledPin, HIGH);
          mqtt_client.publish("fan","on");
        } else if( messageTem == "off"){
      Serial.println("Control: OFF");

          digitalWrite(ledPin, LOW);
          mqtt_client.publish("fan","off");
        }
       }
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.print("Connecting to Wifi... ");
  Serial.print(ssid);
  Serial.println();
  WiFi.begin(ssid, password);//ket noi wifi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to Wifi ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());
  Serial.println();
  delay(1000);

  mqtt_client.setServer(mqtt_server, mqtt_port);//ket noi server mqtt
  mqtt_client.setCallback(callback);

  Serial.println("Connecting to mqtt... ");
  while (!mqtt_client.connect(mqtt_id))
  {
    delay(500);
  }
  Serial.println("Connected to mqtt ");
  pinMode(ledPin, OUTPUT);
  dht.begin();
  }

void loop()
{
  mqtt_client.subscribe("bedroom/fan");//subcribe topic 
  float h = dht.readHumidity();//doc gia tri do am
  float t = dht.readTemperature();//doc gia tri nhiet do

  if (a==1){
    if(t > 20){
      digitalWrite(ledPin, HIGH);//bat den
      mqtt_client.publish("fan","on");//publish data den topic
    } else if(t<20){
      digitalWrite(ledPin, LOW);//tat den
      mqtt_client.publish("fan","off");
    }
  }
   mqtt_client.loop();
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
 }

 //chuyen doi gia tri nhiet do sang mang char
  char tempString[8];
dtostrf(t, 1, 2, tempString);
Serial.print("Temperature: ");
Serial.println(tempString);
mqtt_client.publish("esp32/temp", tempString);
// chuyen doi gia tri do am sang mang char
char humString[8];
dtostrf(h, 1, 2, humString);
Serial.print("Humidity: ");
Serial.println(humString);
mqtt_client.publish("esp32/hum", humString);
  }
 
}