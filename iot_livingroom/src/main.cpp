#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Dienthoaicuabau";//SSID  wifi
const char *password = "anhbau123";//passwword wifi
const char *mqtt_server = "192.168.11.99";//địa chỉ IP MQTT Broker
const int mqtt_port = 1883;
const char *mqtt_id = "esp322";
const int potBin=34;
double quangtro=0;
long lastMsg = 0;
const int ledPin = 2;
boolean a=0;
boolean b=0;

WiFiClient client;
PubSubClient mqtt_client(client);

//thuc hien khi co message gui den topic
void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print(topic);
  String messageLight;
  
  //đọc message gán vào messageLight
    for (int i = 0; i < length; i++) {
    messageLight += (char)message[i];
  }
  //gui data  den topic de chon che do dieu khien
  if (String(topic) == "livingroom/light") {
  
    if(messageLight == "manual"){
      a=0;
      Serial.println("Mode: manual");
     
    }
    else if(messageLight == "auto"){
      Serial.println("Mode: auto");
         
      a=1;
    }
  }
  
  //gui data den topic de chon trang thai led
    if(String(topic) == "livingroom/light"){
  if(a==0){
        
        if(messageLight == "on"){
      Serial.println("Control: ON");

          digitalWrite(ledPin, HIGH);
          mqtt_client.publish("lamp","on");//publish "on" đến topic "lamp"
        } else if( messageLight == "off"){
      Serial.println("Control: OFFF");

          digitalWrite(ledPin, LOW);
          mqtt_client.publish("lamp","off");//publish "off" đến topic "lamp"
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

  mqtt_client.setServer(mqtt_server, mqtt_port);//ket noi mqtt server
  mqtt_client.setCallback(callback);

  Serial.println("Connecting to mqtt... ");
  while (!mqtt_client.connect(mqtt_id))
  {
    delay(500);
  }
  Serial.println("Connected to mqtt ");
  pinMode(ledPin, OUTPUT);
}



void loop()
{
  mqtt_client.subscribe("livingroom/light");//subcribe topic "livingroom/light"
  
  quangtro = analogRead(potBin);
  if(quangtro < 4000){
    b=0;
  }else {
    b=1;
  }
  if (a==1){
    if(b==0){
      digitalWrite(ledPin, HIGH);//den sang
      mqtt_client.publish("lamp","on");//publish message "on"đến topic "lamp"
    } else if(b==1){
      digitalWrite(ledPin, LOW);//den tat
      mqtt_client.publish("lamp","off");//publish message "off"đến topic "lamp"
    }
  }

  
  
  mqtt_client.loop();
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

    //phu thuoc anh sang de hien thi "low" hoac "high"
  if(b==0){
   mqtt_client.publish("esp32/light","low");
  }else{
    mqtt_client.publish("esp32/light","high");
  }
  }

}