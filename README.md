# IoT-Based Smart Electronics Laboratory Safety & Asset Monitoring System

An ESP32-based IoT system that monitors lab conditions in real time and provides
instant alerts for fire, gas leakage, and equipment movement — with cloud monitoring
via ThingSpeak.

## Features

- 🌡️ Temperature & Humidity Monitoring (DHT11)
- 💨 Gas Leakage Detection (MQ-5)
- 🔥 Fire Detection (Flame Sensor)
- 📦 Equipment Movement Detection (HC-SR04)
- 🖥️ Live LCD Status Display (16×2 I2C)
- 🟢🟡🔴🔵 Color-Coded LED Alerts + Buzzer
- ☁️ Real-time ThingSpeak Cloud Upload via Wi-Fi

## Hardware

- ESP32 DevKit V1
- DHT11, MQ-5, Flame Sensor, HC-SR04
- 16×2 I2C LCD, Piezo Buzzer, 4× LEDs
- External 5V Power Supply

## Setup

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support via Board Manager
3. Install libraries: `LiquidCrystal_I2C`, `DHT sensor library`
4. Open `src/lab_safety_monitor.ino`
5. Fill in your Wi-Fi credentials and ThingSpeak API key
6. Upload to ESP32

## Repository Structure
