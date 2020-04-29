#include <Arduino.h>
#include <Credentials.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <MQTTCredentials.h>

#define relay D7


WiFiClient espClient;
PubSubClient client(espClient);

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.print(topic);
    payload[length] = '\0';
    String s = String((char *)payload);
    Serial.println(s);

    if (s.equals(String("ON"))) {
        digitalWrite(relay, LOW);
    } else {
        digitalWrite(relay, HIGH);
    }
};

void connect() {
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    while(!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP1", mqttUser, mqttPassword)) {
            Serial.println("connected");
            client.subscribe("****************Your topic name***************");
        }
        else {
            Serial.println("failed with state: ");
            Serial.print(client.state());
            Serial.println("trying again in 5 seconds");
            delay(5000);
        }
    }
};

void setup()
{
// initialize digital pin 13 as an output.
Serial.begin(115200);
pinMode(relay, OUTPUT);

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

// the loop function runs over and over again forever
void loop()
{
     if (!client.connected()){
        connect();
    }
    client.loop();
}