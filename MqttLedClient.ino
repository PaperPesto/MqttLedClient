#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "LedArray.h"

#define LED0 16
#define LED1 5
#define LED2 4
#define LED3 0
#define LED4 2

// Configurazione Wifi
const char *ssid = "***";
const char *password = "****";

// Configurazione MQTT
const char* mqttServer = "***";
const int mqttPort = ***;
const char* mqttClientId = "***";
const char* mqttUsername = "***";
const char* mqttPassword = "";

// Topic MQTT
const char* topicLed0 = "qiot/things/paperpesto/librerialed/led0";
const char* topicLed1 = "qiot/things/paperpesto/librerialed/led1";
const char* topicLed2 = "qiot/things/paperpesto/librerialed/led2";
const char* topicLed3 = "qiot/things/paperpesto/librerialed/led3";
const char* topicLed4 = "qiot/things/paperpesto/librerialed/led4";

// Network status
bool wifiConnection_Status = false;
bool brokerConnection_Status = false;

// Ledarray
LedArray ledarray(LED0, LED1, LED2, LED3, LED4);

int led0 = 0;
int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;

WiFiClient espClient;
PubSubClient client(espClient);

IPAddress ip;

void setup()
{

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  ip = WiFi.localIP();
  Serial.print("Ip: ");
  Serial.println(ip);

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");

    if (client.connect(mqttClientId, mqttUsername, mqttPassword))
    {
      Serial.println("Connected to broker");

      //client.publish("esp/test", "Hello from ESP8266");
      client.subscribe(topicLed0);
      client.subscribe(topicLed1);
      client.subscribe(topicLed2);
      client.subscribe(topicLed3);
      client.subscribe(topicLed4);
    }
    else
    {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.println("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i], BIN);
    Serial.print(" - ");
    Serial.println((char)payload[i], HEX);
  }

  // Creazione stringa ---
  // alla fine della stringa devo avere un \0 per terminare la stringa
  // altrimenti println() continua a leggere finché non trova '\0'
  char *bufferString;
  bufferString = (char *)malloc(length + 1);
  Serial.print("Indirizzo bufferString: ");
  Serial.println(*bufferString, HEX);
  for (int i = 0; i < length; i++)
  {
    bufferString[i] = (char)payload[i];
  }
  bufferString[length] = '\0';
  Serial.print("Buffer string: ");
  Serial.println(bufferString);

  if (strcmp(topic, topicLed0) == 0)
  {
    led0 = atoi(bufferString);
  }

  if (strcmp(topic, topicLed1) == 0)
  {
    led1 = atoi(bufferString);
  }

  if (strcmp(topic, topicLed2) == 0)
  {
    led2 = atoi(bufferString);
  }

  if (strcmp(topic, topicLed3) == 0)
  {
    led3 = atoi(bufferString);
  }

  if (strcmp(topic, topicLed4) == 0)
  {
    led4 = atoi(bufferString);
  }

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

  Serial.println("-----------------------");
}

void loop()
{
  //client.publish("aaa/test", "Publishing, cane");
  client.loop();
}