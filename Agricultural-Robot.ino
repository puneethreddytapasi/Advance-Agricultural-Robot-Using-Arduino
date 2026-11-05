#include <DHT.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

// ---------- SENSOR PINS ----------
#define DHTPIN 2
#define DHTTYPE DHT11

#define TRIG_PIN 3
#define ECHO_PIN 4
#define SOIL_PIN A0

// ---------- MOTOR DRIVER ----------
#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10

// ---------- OTHER COMPONENTS ----------
#define SERVO_PIN 8
#define RELAY_PIN 12

// GPS: Nano receives GPS data on D7
SoftwareSerial gpsSerial(7, 11);
TinyGPSPlus gps;

DHT dht(DHTPIN, DHTTYPE);
Servo probeServo;

// ---------- SETTINGS ----------
const int SOIL_DRY_THRESHOLD = 600;

const int SERVO_UP = 20;
const int SERVO_DOWN = 100;

const bool ENABLE_PUMP_CONTROL = false;
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;

const int OBSTACLE_DISTANCE = 20;

// ---------- MOTOR FUNCTIONS ----------
void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// ---------- DISTANCE FUNCTION ----------
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) {
    return 999;
  }

  return duration * 0.0343 / 2;
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);

  dht.begin();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF);

  probeServo.attach(SERVO_PIN);
  probeServo.write(SERVO_UP);

  stopRobot();

  Serial.println("AGRICULTURAL ROBOT STARTED");
}

// ---------- MAIN PROGRAM ----------
void loop() {

  // Read GPS data
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  // Read sensors
  int soilValue = analogRead(SOIL_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float distance = getDistance();

  // Lower probe and take a soil reading
  probeServo.write(SERVO_DOWN);
  delay(1500);

  soilValue = analogRead(SOIL_PIN);

  probeServo.write(SERVO_UP);

  // Display readings
  Serial.println("\n----- ROBOT SENSOR DATA -----");

  Serial.print("Soil moisture value: ");
  Serial.println(soilValue);

  if (!isnan(temperature)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
  } else {
    Serial.println("Temperature sensor error");
  }

  if (!isnan(humidity)) {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("Humidity sensor error");
  }

  Serial.print("Obstacle distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);

    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
  } else {
    Serial.println("GPS: Waiting for satellite fix");
  }

  // Automatic irrigation
  if (soilValue > SOIL_DRY_THRESHOLD) {
    Serial.println("Soil is DRY");

    if (ENABLE_PUMP_CONTROL) {
      digitalWrite(RELAY_PIN, RELAY_ON);
    }
  } else {
    Serial.println("Soil moisture is sufficient");
    digitalWrite(RELAY_PIN, RELAY_OFF);
  }

  // Obstacle avoidance
  if (distance < OBSTACLE_DISTANCE) {
    stopRobot();
    delay(300);

    moveBackward();
    delay(500);

    stopRobot();
    delay(200);

    turnRight();
    delay(600);

    stopRobot();
  } else {
    moveForward();
  }

  delay(1000);
}
