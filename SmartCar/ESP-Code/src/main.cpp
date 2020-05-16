#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <Credentials.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

#define RightMotorSpeed 5
#define RightMotorPin 0
#define LeftMotorSpeed 4
#define LeftMotorPin 2

void forward()
{
  digitalWrite(RightMotorPin, HIGH);
  digitalWrite(LeftMotorPin, HIGH);
  digitalWrite(RightMotorSpeed, HIGH);
  digitalWrite(LeftMotorSpeed, HIGH);
}

void reverse()
{
  digitalWrite(RightMotorPin, LOW);
  digitalWrite(LeftMotorPin, LOW);
  digitalWrite(RightMotorSpeed, HIGH);
  digitalWrite(LeftMotorSpeed, HIGH);
}

void stop()
{
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
}

void left()
{
  digitalWrite(RightMotorPin, HIGH);
  digitalWrite(LeftMotorPin, LOW);
  digitalWrite(RightMotorSpeed, HIGH);
  digitalWrite(LeftMotorSpeed, LOW);
}
void right()
{
  digitalWrite(RightMotorPin, LOW);
  digitalWrite(LeftMotorPin, HIGH);
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, HIGH);
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived in topic: ");
  Serial.print(topic);
  payload[length] = '\0';
  String s = String((char *)payload);
  Serial.println(s);

  if (s.equals(String("forward")))
  {
    forward();
  }
  else if (s.equals(String("back")))
  {
    reverse();
  }
  else if (s.equals(String("left")))
  {
    left();
  }
  else if (s.equals(String("right")))
  {
    right();
  }
  else if (s.equals(String("stop")))
  {
    stop();
  }
}

void connect()
{
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP2", mqttUser, mqttPassword))
    {
      Serial.println("connected");
      client.subscribe("**********");
    }
    else
    {
      Serial.println("failed with state: ");
      Serial.print(client.state());
      Serial.println("trying again in 5 seconds");
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);

  digitalWrite(5, 0);
  digitalWrite(4, 0);
  digitalWrite(0, 1);
  digitalWrite(2, 1);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("waiting for wifi to be connected");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

   connect();
}

void loop()
{
  if (!client.connected())
  {
    connect();
  }
  client.loop();
}