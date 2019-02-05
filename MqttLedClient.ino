#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "LedArray.h"

#define LED0 16
#define LED1 5
#define LED2 4
#define LED3 0
#define LED4 2

// Configurazione Wifi
const char* ssid = "***";
const char* password =  "***";

// Configurazione MQTT
const char* mqttServer = "***";
const int mqttPort = 000;
const char* mqttUser = "***";
const char* mqttPassword = "***";
// Network status
bool wifiConnection_Status = false;
bool brokerConnection_Status = false;

// Ledarray
LedArray ledarray (LED0,LED1,LED2,LED3,LED4);

WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("esp/test");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  StaticJsonBuffer<200> jsonBuffer;
 
  Serial.println("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i], BIN);
    Serial.print(" - ");
    Serial.println((char)payload[i], HEX);
  }

  // Creazione stringa ---
  // alla fine della stringa devo avere un \0 per terminare la stringa
  // altrimenti println() continua a leggere finché non trova '\0'
  char* bufferString;
  bufferString = (char*) malloc (length + 1);
  Serial.print("Indirizzo bufferString: ");
  Serial.println(*bufferString, HEX);
  for (int i = 0; i < length; i++) {
    bufferString[i] = (char)payload[i];
  }
  bufferString[length] = '\0';
  Serial.print("Buffer string: ");
  Serial.println(bufferString);
  
  // Conversione stringa -> json ---
  JsonObject& root = jsonBuffer.parseObject(bufferString);
  // Test if parsing succeeds.
  if (!root.success()) {
    Serial.println("parseObject() failed");
  }
  else {
    Serial.println("parseObject() success");

    const float led0 = root["led0"];
    const float led1 = root["led1"];
    const float led2 = root["led2"];
    const float led3 = root["led3"];
    const float led4 = root["led4"];

    // Print values
    Serial.println("led0: " + String(led0));
    Serial.println("led1: " + String(led1));
    Serial.println("led2: " + String(led2));
    Serial.println("led3: " + String(led3));
    Serial.println("led4: " + String(led4));

    // Conversion from percentage to 0:1023
    int cled0 = map(led0, 0, 100, 0, 1023);
    int cled1 = map(led1, 0, 100, 0, 1023);
    int cled2 = map(led2, 0, 100, 0, 1023);
    int cled3 = map(led3, 0, 100, 0, 1023);
    int cled4 = map(led4, 0, 100, 0, 1023);

    // Print converted values
    Serial.println("Converted values");
    Serial.println("led0: " + String(cled0));
    Serial.println("led1: " + String(cled1));
    Serial.println("led2: " + String(cled2));
    Serial.println("led3: " + String(cled3));
    Serial.println("led4: " + String(cled4));

    // Sending to LedArray
    ledarray.Pwm(cled0, cled1, cled2, cled3, cled4);
  }
  free(bufferString);
  
  Serial.println("-----------------------");
}
 
void loop() {
  //client.publish("aaa/test", "Publishing, cane");
  client.loop();
}
