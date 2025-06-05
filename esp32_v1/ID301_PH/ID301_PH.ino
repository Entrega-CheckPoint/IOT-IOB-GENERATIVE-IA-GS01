#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <iostream>
#include <ctime>

//----------------------------------------------------------
// Definições e configurações

#define boardLED 2  // LED onboard

// Identificadores
const char *ID = "1";
const char *moduleID = "301";
const int IdSensor = 301;

// Wi-Fi
const char *SSID = "Francescos";
const char *PASSWORD = "frankeko";

// MQTT Broker
const char *BROKER_MQTT = "104.41.50.45";
const int BROKER_PORT = 1883;
const char *mqttUser = "";
const char *mqttPassword = "";

// Tópico MQTT
#define TOPICO_PUBLISH "/iot/dados"

//----------------------------------------------------------
// Variáveis globais

WiFiClient espClient;
PubSubClient MQTT(espClient);
char buffer[256];
int contagem = 0;

//----------------------------------------------------------
// Conexão Wi-Fi

void initWiFi() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void reconectaWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconectando Wi-Fi...");
    initWiFi();
  }
}

//----------------------------------------------------------
// Conexão MQTT

void initMQTT() {
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  while (!MQTT.connected()) {
    Serial.println("Conectando ao Broker MQTT...");
    if (MQTT.connect(moduleID, mqttUser, mqttPassword)) {
      Serial.println("Conectado ao Broker!");
    } else {
      Serial.print("Falha na conexão. Estado: ");
      Serial.println(MQTT.state());
      delay(2000);
    }
  }
}

void verificaConexoesWiFiEMQTT() {
  reconectaWiFi();
  if (!MQTT.connected()) {
    initMQTT();
  }
  MQTT.loop();
}

//----------------------------------------------------------
// Envio e feedback

void enviaEstadoOutputMQTT() {
  MQTT.publish(TOPICO_PUBLISH, buffer);
  Serial.println("Mensagem publicada com sucesso!");
}

void piscaLed() {
  digitalWrite(boardLED, HIGH);
  delay(300);
  digitalWrite(boardLED, LOW);
}

//----------------------------------------------------------
// Setup inicial

void setup() {
  Serial.begin(115200);
  pinMode(boardLED, OUTPUT);
  digitalWrite(boardLED, LOW);
  initWiFi();
  initMQTT();

  configTime(-3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < 100000) {
    delay(100);
  }
}

//----------------------------------------------------------
// Loop principal

void loop() {
  // Verifica e mantém conexões ativas com Wi-Fi e MQTT
  verificaConexoesWiFiEMQTT();

  // Montagem do documento JSON
  StaticJsonDocument<300> doc;

  time_t now = time(nullptr);
  char dtRegistro[25];
  strftime(dtRegistro, sizeof(dtRegistro), "%Y-%m-%dT%H:%M:%S", localtime(&now));

  // 1. Registro
  doc["dtRegistro"] = dtRegistro;
  doc["resultado"] = random(6500, 8500) / 1000.0;
  doc["idSensor"] = IdSensor;

  // Serializa JSON para string
  serializeJson(doc, buffer);

  // Exibe no monitor serial
  Serial.println(buffer);

  // Envia via MQTT
  enviaEstadoOutputMQTT();

  // Feedback visual
  piscaLed();

  // Intervalo de envio
  delay(10000);
}