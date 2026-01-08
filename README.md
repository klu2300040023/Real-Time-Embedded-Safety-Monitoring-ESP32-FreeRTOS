# Real-Time Embedded Safety Monitoring System

## Overview
This project implements a real-time embedded firmware system using ESP32 and FreeRTOS.  
It monitors environmental parameters, computes a hazard severity level using sensor fusion, and performs time-critical actuation.  
Live system data is uploaded to ThingSpeak for visualization and monitoring.

This project focuses on embedded firmware concepts such as RTOS task scheduling, peripheral interfacing, and hardware–software co-design.

---

## Objectives
- Design a real-time embedded system using FreeRTOS  
- Implement parallel RTOS tasks with defined priorities  
- Interface sensors using ADC, GPIO, PWM, and timers  
- Compute hazard severity using sensor fusion logic  
- Perform automatic load control using relay and motor  
- Reduce wiring complexity using a custom ESP32 shield PCB  

---

## System Architecture
Sensors → ESP32 (FreeRTOS)
              |
      -------------------
      |   Decision     |
      |   Engine       |
      -------------------
        |           |
   Actuators     Cloud
 (Relay/Motor)  ThingSpeak

---

## FreeRTOS Task Design
| Task Name | Description |
|----------|-------------|
| Sensor Task | Periodic sensor data acquisition |
| Decision Task | Hazard severity computation |
| Control Task | Relay and motor actuation |
| Display Task | LCD status updates |
| Cloud Task | Data upload to ThingSpeak |

---

## Hardware Components
- ESP32 WROOM-32  
- MQ-2 Smoke Sensor  
- DHT11 Temperature & Humidity Sensor  
- PIR Motion Sensor  
- Ultrasonic Sensor  
- LDR  
- Relay Module  
- DC Motor + Fan  
- LCD 16×2 (I2C)  
- Buzzer and Status LEDs  

---

## Software & Tools
- Embedded C / C++  
- FreeRTOS  
- ESP32 Arduino Core  
- ThingSpeak IoT Platform  
- EasyEDA (PCB Design)

---

## PCB Design
- Modular ESP32 shield PCB  
- Separate zones for sensors, control, and actuators  
- Common ground plane and optimized power routing  
- Improved reliability and clean hardware layout  

PCB schematic and layout files are included in this repository.

---

## Cloud Integration (ThingSpeak)
The following parameters are uploaded:
- Temperature  
- Humidity  
- Smoke Level  
- Hazard Severity Index  
- Load Status  

This enables remote monitoring and basic data analysis.

---

## Repository Structure
Real-Time-Embedded-Safety-Monitoring-ESP32-FreeRTOS/
│
├── src/
│   └── main.ino
├── pcb/
│   ├── schematic.pdf
│   ├── pcb_layout.png
│   └── gerber_files.zip
├── images/
│   ├── hardware_setup.jpg
│   ├── thingspeak_dashboard.png
│
└── README.md

---

## Skills Demonstrated
- Embedded firmware development  
- RTOS task scheduling  
- Peripheral interfacing (ADC, GPIO, PWM, Timers)  
- Hardware–software integration  
- PCB design and debugging  

---

## Author
Ponamala Gayathri  
B.Tech ECE (Honours)  
Embedded Systems & Firmware Enthusiast
