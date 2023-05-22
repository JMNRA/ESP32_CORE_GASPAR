#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const int LED1 = 12;
const int LED2 = 13;

const char *ssid = "FULLPLAY-ANGIE-973640806";
const char *pass = "angie2021y";
// Credenciales MQTT
const char *brokerUser = "dev1";
const char *brokerPass = "pass";
const char *broker = "192.168.0.110";

WiFiClient espClient;
PubSubClient client(espClient);


void setupWifi()
{
  delay(100);
  Serial.println("\nConectando a");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print("-");
  }
  Serial.print("\nConectado a");
  Serial.println(ssid);
  digitalWrite(LED2, HIGH);
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("\nConectando a");
    Serial.print(broker);
    if (client.connect("Angie", brokerUser, brokerPass))
    {
      Serial.print("\nConectado a");
      Serial.print(broker);
      digitalWrite(LED2, LOW);
      delay(500);
      digitalWrite(LED2, HIGH);
    }
    else
    {
      Serial.println("\nIntentando conectar denuevo");
      delay(5000);
      digitalWrite(LED2, LOW);

    }
  }
}

void setup() {
  setupWifi();
  client.setServer(broker, 1883); 
 

  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
     if (!client.connected())
  {
    reconnect();
  }
 
  client.loop();
}


