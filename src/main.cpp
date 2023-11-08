#include <Arduino.h>
#include <WiFiNINA.h>
#include <WiFiClient.h>
#include <ArduinoMqttClient.h>
#include <secrets.h>

void onMqttMessage(int messageSize);

int status = WL_IDLE_STATUS;
WiFiSSLClient client;
MqttClient mqttClient(client);

bool ledState = false;

void setLeds(bool state) {
  digitalWrite(LED_BUILTIN, ledState);
  digitalWrite(12, ledState);
  digitalWrite(11, ledState);
  digitalWrite(10, ledState);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  if ( status != WL_CONNECTED) {
    Serial.println("Couldn't get a WiFi connection");
    while(true);
  }
  else {
    Serial.print("Connected to WiFi. My address:");
    IPAddress myAddress = WiFi.localIP();
    Serial.println(myAddress);
    
    mqttClient.setUsernamePassword(MQTT_USER, MQTT_PASSWORD);
    Serial.println("Connecting to MQTT broker...");
    if (!mqttClient.connect(MQTT_SERVER, MQTT_PORT)) {
      Serial.print("MQTT connection failed! Error code = ");
      Serial.println(mqttClient.connectError());

      while (1);
    }
    mqttClient.onMessage(onMqttMessage);
    mqttClient.subscribe(MQTT_TOPIC);
    Serial.println("MQTT connected!");
  }
}

void loop() {
  mqttClient.poll();
}

void onMqttMessage(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    Serial.print((char)mqttClient.read());
  }
  Serial.println();
  Serial.println();
}