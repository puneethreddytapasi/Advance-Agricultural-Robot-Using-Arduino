# 🌱 Advance Agricultural Robot Using Arduino

An Arduino-based smart agricultural robot designed to assist agricultural monitoring through soil moisture sensing, environmental monitoring, GPS tracking, obstacle detection and automated movement.

## 📌 Project Overview

The **Advance Agricultural Robot Using Arduino** is designed to support smart farming by integrating multiple sensors and robotic components into a mobile agricultural platform.

The robot collects soil and environmental information, monitors its surroundings, and uses GPS to obtain its geographical coordinates. It also uses an ultrasonic sensor for obstacle detection and a servo-controlled probe mechanism for soil measurement.

## 🎯 Objectives

- Monitor soil moisture conditions.
- Measure environmental temperature and humidity.
- Obtain geographical coordinates using GPS.
- Detect obstacles and perform basic obstacle avoidance.
- Develop a mobile robotic platform for agricultural applications.
- Provide a foundation for future automated irrigation.

## ⚙️ Key Features

| Feature | Component |
|---|---|
| Soil moisture monitoring | Soil Moisture Sensor |
| Temperature measurement | DHT11 |
| Humidity monitoring | DHT11 |
| Obstacle detection | HC-SR04 Ultrasonic Sensor |
| GPS tracking | GPS Module |
| Soil probe movement | Servo Motor |
| Robot movement | DC Motors and Motor Driver |
| Irrigation control interface | Relay Module |

## 🔩 Hardware Requirements

1. Arduino Nano
2. DHT11 Temperature and Humidity Sensor
3. Soil Moisture Sensor
4. HC-SR04 Ultrasonic Sensor
5. GPS Module
6. Servo Motor
7. Motor Driver Module
8. DC Motors and Robot Chassis
9. Relay Module
10. Water Pump (optional)
11. Battery and connecting wires

## 💻 Software Requirements

- Arduino IDE
- Embedded C / Arduino Programming
- DHT Sensor Library
- Servo Library
- SoftwareSerial Library
- TinyGPSPlus Library

## 🔌 Pin Configuration

| Component | Arduino Nano Pin |
|---|---|
| DHT11 Data | D2 |
| Ultrasonic TRIG | D3 |
| Ultrasonic ECHO | D4 |
| Soil Sensor AO | A0 |
| Motor IN1 | D5 |
| Motor IN2 | D6 |
| GPS RX (Arduino receives) | D7 |
| Servo Signal | D8 |
| Motor IN3 | D9 |
| Motor IN4 | D10 |
| GPS TX (Arduino transmits) | D11 |
| Relay IN | D12 |

**Note:** GPS wiring is described from the Arduino's perspective. Connect GPS TX to Arduino D7 and GPS RX to Arduino D11.

## 🔄 Working Methodology

### 1. Soil Moisture Monitoring
The soil moisture sensor measures the soil condition and sends analog readings to the Arduino Nano. The program uses a threshold value of 600 to classify dry soil.

### 2. Temperature and Humidity Monitoring
The DHT11 sensor measures the surrounding temperature and humidity and sends the readings to the Arduino.

### 3. GPS Tracking
The GPS module provides geographical coordinates. TinyGPSPlus processes the received GPS data and displays latitude and longitude through the Serial Monitor when a valid location fix is available.

### 4. Obstacle Detection
The HC-SR04 ultrasonic sensor measures the distance between the robot and nearby obstacles.

When an obstacle is detected within 20 cm, the robot:
- Stops moving.
- Moves backward.
- Stops briefly.
- Turns right.
- Resumes its movement.

### 5. Servo-Controlled Soil Probe
The servo motor moves the soil probe downwards to take a soil moisture reading and then returns it to its initial position.

### 6. Irrigation Control
The program includes relay-based irrigation control. Pump activation is currently disabled by default and can be enabled after proper hardware testing.

## 🧠 System Workflow

```text
          START
            |
            v
       Arduino Nano
            |
     Read Sensor Data
            |
    +-------+--------+
    |       |        |
    v       v        v
  Soil    DHT11     GPS
 Sensor   Sensor   Module
    |       |        |
    +-------+--------+
            |
            v
     Display Readings
            |
            v
   Check Soil Condition
            |
            v
     Check Obstacles
            |
       +----+----+
       |         |
   Obstacle   No Obstacle
    Found         |
       |          |
       v          v
   Stop Robot   Move Forward
       |
       v
  Reverse and Turn
       |
       +------> Repeat
```

## 📦 Installation and Setup

1. Install Arduino IDE.
2. Connect the Arduino Nano to your computer.
3. Install the required libraries using Arduino Library Manager:
   - DHT sensor library
   - TinyGPSPlus
4. Open `Agricultural-Robot.ino`.
5. Select the appropriate Arduino Nano board and COM port.
6. Upload the program.
7. Open Serial Monitor at 9600 baud.
8. Connect and test the hardware components.

## 🧪 Testing and Results

The project is designed to demonstrate:

- Soil moisture readings.
- Temperature and humidity measurements.
- GPS location output when satellite fix is available.
- Obstacle detection and avoidance.
- Servo-controlled soil probe operation.
- Relay control logic.

Actual experimental readings and hardware photographs will be added after testing.

## 🌾 Applications

- Smart agriculture.
- Soil condition monitoring.
- Agricultural field inspection.
- Automated farming research.
- Precision agriculture development.

## 🚀 Future Scope

- Fully automated irrigation using soil moisture conditions.
- IoT-based remote monitoring.
- Live GPS location tracking through a mobile application.
- Advanced obstacle avoidance using additional sensors.
- Crop health monitoring using cameras and AI.
- Weather-based agricultural decision support.
- Solar-powered agricultural robot.

## 👨‍💻 Project Team

**Subject:** 21CSE305P – SerBot: Project-Based Learning in Robotics

| Team Member | Registration Number |
|---|---|
| Tapasi Puneeth Reddy | RA241103011495 |
| Vigneshwaran B | RA2411026011367 |
| Drona R | RA2411026011380 |

**Faculty Guide:** Dr. R. Kayalvizhi

## 🏛️ Institutional Affiliation

Department of Networking and Communications  
School of Computing  
Faculty of Engineering and Technology  
SRM Institute of Science and Technology  
Kattankulathur, Tamil Nadu, India

## 📂 Repository Structure

```text
Advance-Agricultural-Robot-Using-Arduino/
│
├── Agricultural-Robot.ino
├── README.md
├── .gitignore
│
└── docs/
    ├── circuit-diagram.png
    ├── system-architecture.png
    └── project-images
