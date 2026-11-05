#include <DHT.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

// ---------- SENSOR PINS ----------
#define DHT_PIN 2
#define DHT_TYPE DHT11

#define TRIG_PIN 3
#define ECHO_PIN 4

#define SOIL_PIN A0

// ---------- SERVO AND RELAY ----------
#define SERVO_PIN 8
#define RELAY_PIN 12

// ---------- GPS ----------
SoftwareSerial gpsSerial(7, 11);
TinyGPSPlus gps;

// ---------- OBJECTS ----------
DHT dht(DHT_PIN, DHT_TYPE);
Servo soilServo;

// ---------- SETTINGS ----------
const int SOIL_DRY_THRESHOLD = 600;

const int SERVO_UP = 20;
const int SERVO_DOWN = 100;

// Assumes an active-LOW relay.
// Confirm your relay's trigger type before using the pump.
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;

// ---------- ULTRASONIC FUNCTION ----------
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  return duration * 0.034 / 2;
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);

  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);

  soilServo.attach(SERVO_PIN);
  soilServo.write(SERVO_UP);

  Serial.println("Agricultural Robot Sensor System Started");
}

// ---------- MAIN LOOP ----------
void loop() {

  // 1. SOIL MOISTURE
  int soilValue = analogRead(SOIL_PIN);

  Serial.print("Soil Moisture Value: ");
  Serial.println(soilValue);

  // 2. SERVO PROBE MOVEMENT
  soilServo.write(SERVO_DOWN);
  delay(1000);

  // Read soil sensor again after lowering the probe
  soilValue = analogRead(SOIL_PIN);

  soilServo.write(SERVO_UP);

  // 3. AUTOMATIC WATER PUMP
  if (soilValue > SOIL_DRY_THRESHOLD) {
    digitalWrite(RELAY_PIN, RELAY_ON);
    Serial.println("Soil is DRY - Pump ON");
  } else {
    digitalWrite(RELAY_PIN, RELAY_OFF);
    Serial.println("Soil is MOIST - Pump OFF");
  }

  // 4. TEMPERATURE AND HUMIDITY
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (!isnan(humidity) && !isnan(temperature)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("DHT11 reading error");
  }

  // 5. ULTRASONIC DISTANCE
  int distance = getDistance();

  Serial.print("Obstacle Distance: ");
  if (distance == -1) {
    Serial.println("No echo");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  // 6. GPS LOCATION
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);

    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println("Waiting for GPS signal...");
  }

  Serial.println("-----------------------------");

  delay(2000);
}
