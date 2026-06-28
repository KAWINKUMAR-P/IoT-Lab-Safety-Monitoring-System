#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// WiFi
const char* ssid = "vivo v40";
const char* password = "1029384756";

// ThingSpeak
String apiKey = "76JLGHZU7SUEFCCT";

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// DHT11
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ5
#define GAS_PIN 34

// Flame Sensor
#define FLAME_PIN 19

// Ultrasonic
#define TRIG_PIN 26
#define ECHO_PIN 27

// Buzzer
#define BUZZER_PIN 18

// LEDs
#define GREEN_LED 13
#define YELLOW_LED 12
#define RED_LED 14
#define BLUE_LED 25

float referenceDistance = 0;

unsigned long lastUpload = 0;
const unsigned long uploadInterval = 20000;

// -------------------- WiFi --------------------

void connectWiFi()
{
  WiFi.begin(ssid, password);

  lcd.clear();
  lcd.print("Connecting...");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1500);
}

// -------------------- Distance --------------------

float getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  float distance = duration * 0.0343 / 2.0;

  return distance;
}

// -------------------- ThingSpeak --------------------

void sendToThingSpeak(float temp,
                      float hum,
                      int gas,
                      float distance,
                      String status)
{
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    String url =
      "http://api.thingspeak.com/update?api_key=" + apiKey +
      "&field1=" + String(temp) +
      "&field2=" + String(hum) +
      "&field3=" + String(gas) +
      "&field4=" + String(distance) +
      "&field5=" + status;

    http.begin(url);

    int httpCode = http.GET();

    Serial.print("ThingSpeak: ");
    Serial.println(httpCode);

    http.end();
  }
}

// -------------------- Setup --------------------

void setup()
{
  Serial.begin(115200);

  dht.begin();

  pinMode(FLAME_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("LAB SAFETY");
  lcd.setCursor(0,1);
  lcd.print("SYSTEM");

  delay(2000);

  connectWiFi();

  referenceDistance = getDistance();

  lcd.clear();
  lcd.print("SYSTEM READY");
  delay(1500);
}

// -------------------- Loop --------------------

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int gasValue = analogRead(GAS_PIN);

  int flameStatus = digitalRead(FLAME_PIN);

  float distance = getDistance();

  String alertStatus = "NORMAL";

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  // FIRE ALERT
  if (flameStatus == LOW)
  {
    alertStatus = "FIRE";

    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FIRE ALERT!");
    lcd.setCursor(0,1);
    lcd.print("CHECK LAB");
  }

  // GAS ALERT
  else if (gasValue > 2500)
  {
    alertStatus = "GAS";

    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GAS LEAKAGE!");
    lcd.setCursor(0,1);
    lcd.print("Value:");
    lcd.print(gasValue);
  }

  // MOVEMENT ALERT
  else if (abs(distance - referenceDistance) > 10)
  {
    alertStatus = "MOVED";

    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EQUIP MOVED");
    lcd.setCursor(0,1);
    lcd.print("D:");
    lcd.print(distance,1);
  }

  // NORMAL MODE
  else
  {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(GREEN_LED, HIGH);

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("T:");
    lcd.print(temperature,1);
    lcd.print("C");

    lcd.setCursor(9,0);
    lcd.print("H:");
    lcd.print(humidity,0);

    lcd.setCursor(0,1);
    lcd.print("G:");
    lcd.print(gasValue);
  }

  // Upload every 20 seconds
  if (millis() - lastUpload >= uploadInterval)
  {
    sendToThingSpeak(
      temperature,
      humidity,
      gasValue,
      distance,
      alertStatus
    );

    lastUpload = millis();
  }

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" Hum: ");
  Serial.print(humidity);
  Serial.print(" Gas: ");
  Serial.print(gasValue);
  Serial.print(" Dist: ");
  Serial.print(distance);
  Serial.print(" Status: ");
  Serial.println(alertStatus);

  delay(1000);
}