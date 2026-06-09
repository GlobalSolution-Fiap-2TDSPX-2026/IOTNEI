#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// ======================
// WIFI
// ======================

const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ======================
// LCD
// ======================

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ======================
// SERVER
// ======================

WebServer server(80);

// ======================
// PINOS
// ======================

#define TRIG_PIN 5
#define ECHO_PIN 18

#define BUTTON_PIN 19

#define GREEN_LED 12
#define RED_LED 14

// ======================
// VARIÁVEIS NASA
// ======================

String asteroidName = "NONE";
String riskLevel = "SAFE";

float asteroidDistance = 0;

// ======================
// HC-SR04
// ======================

float readDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);

  float distance = duration * 0.034 / 2;

  return distance;
}

// ======================
// ENDPOINT /status
// ======================

void handleStatus() {

  StaticJsonDocument<300> doc;

  doc["asteroid"] = asteroidName;
  doc["risk"] = riskLevel;
  doc["distance"] = asteroidDistance;

  doc["sensor_distance"] = readDistance();

  doc["button"] = digitalRead(BUTTON_PIN);

  String response;

  serializeJson(doc, response);

  server.send(200, "application/json", response);
}

// ======================
// ENDPOINT /nasa-data
// ======================

void handleNASAData() {

  if(server.method() != HTTP_POST) {

    server.send(405, "text/plain", "Method Not Allowed");
    return;
  }

  StaticJsonDocument<300> doc;

  DeserializationError error =
    deserializeJson(doc, server.arg("plain"));

  if(error) {

    server.send(400, "text/plain", "JSON Error");
    return;
  }

  asteroidName =
    doc["asteroid"].as<String>();

  asteroidDistance =
    doc["distance"];

  riskLevel =
    doc["risk"].as<String>();

  // LEDs

  if(riskLevel == "DANGER") {

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

  } else {

    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }

  // LCD

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("ASTEROIDE:");

  lcd.setCursor(0, 1);

  if(riskLevel == "DANGER") {

    lcd.print("PERIGO");

  } else {

    lcd.print("SEGURO");
  }

  server.send(200, "text/plain", "OK");
}

// ======================
// SETUP
// ======================

void setup() {

  Serial.begin(115200);

  // LCD

  Wire.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("NASA NEO");

  // PINOS

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // WIFI

  WiFi.begin(ssid, password);

  lcd.setCursor(0, 1);
  lcd.print("Conectando");

  while(WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");

  Serial.println(WiFi.localIP());

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("WiFi OK");

  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  // ENDPOINTS

  server.on("/status", HTTP_GET, handleStatus);

  server.on("/nasa-data", HTTP_POST, handleNASAData);

  server.begin();

  Serial.println("Servidor iniciado");
}

// ======================
// LOOP
// ======================

void loop() {

  server.handleClient();

  // ALERTA MANUAL

  if(digitalRead(BUTTON_PIN) == LOW) {

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("ALERTA MANUAL");

    lcd.setCursor(0, 1);
    lcd.print("ATIVADO");

    delay(1000);
  }
}
