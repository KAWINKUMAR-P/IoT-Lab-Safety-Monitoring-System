# Pin Connection Details

| Component       | Pin           | ESP32 GPIO |
|-----------------|---------------|------------|
| DHT11           | DATA          | GPIO 4     |
| MQ-5            | AO (Analog)   | GPIO 34    |
| Flame Sensor    | DO (Digital)  | GPIO 19    |
| HC-SR04         | TRIG          | GPIO 26    |
| HC-SR04         | ECHO          | GPIO 27    |
| LCD I2C (16x2)  | SDA           | GPIO 21    |
| LCD I2C (16x2)  | SCL           | GPIO 22    |
| Buzzer          | +             | GPIO 18    |
| Green LED       | Anode (220Ω)  | GPIO 13    |
| Yellow LED      | Anode (220Ω)  | GPIO 12    |
| Red LED         | Anode (220Ω)  | GPIO 14    |
| Blue LED        | Anode (220Ω)  | GPIO 25    |

> ⚠️ HC-SR04 ECHO pin outputs 5V. Use a voltage divider (1kΩ + 2kΩ)
> to bring it down to 3.3V before connecting to ESP32.
