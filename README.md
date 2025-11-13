# Smart Garage Parking Assistant

This project demonstrates an Automated Garage Parking Assistant built using the Benewake TFmini Plus LiDAR sensor and a WS2812B RGB LED strip.

The system measures the distance between the top of the car and the ceiling-mounted LiDAR sensor, effectively taking up no floor space. As the car moves forward, the detected distance decreases due to higher parts of the vehicle (the windshield or roof) approaching the sensor.  

This change correlates to the car’s closing distance toward the wall, providing color-based LED guidance on the wall in real time.  

---

## Demo Video

[![Watch the demo](https://img.youtube.com/vi/wNS5gxbRVsM/hqdefault.jpg)](https://youtu.be/wNS5gxbRVsM?si=g-67zj3yJi1HfWGF)  
YouTube Link: [Smart Garage Parking Assistant Demo](https://youtu.be/wNS5gxbRVsM?si=g-67zj3yJi1HfWGF)

---

## LED Feedback Logic

| LED Color | Condition | Meaning |
|------------|------------|----------|
| 🟩 Green | Distance < 100 in (254 cm) | Safe distance — hood of car |
| 🟨 Yellow | Distance < 83 in (210.82 cm) OR Distance == 0 | Getting close — Distance feeback is 0 when sensor detects windshield|
| 🟥 Red | Distance < 66 in (167.64 cm) | Perfect parking range |

After the car remains parked for 3 seconds, the LED strip automatically turns off to conserve power. When the car moves again, the system detects motion and reactivates LED feedback.

---

## Features

- Ceiling-mounted setup
- Accurate LiDAR distance measurement with the TFmini Plus
- RGB LED guidance based on distance thresholds
- Automatic functionality for energy efficiency
- Ideal for tight garage spaces and DIY smart home integrations

---

## Components & Supplies

| Item | Quantity | Description |
|------|-----------|-------------|
| 830-point Solderless Breadboard | 1 | For circuit prototyping |
| USB-C Cable (Power) | 1 | Powers Arduino Nano ESP32 |
| Benewake TFmini Plus LiDAR Sensor (Waterproof IP65) | 1 | Distance measurement (UART) |
| Resistor (330 Ω) | 1 | Data line protection for LED strip |
| BTF-LIGHTING WS2812B RGB LED Strip (3.28 ft, 60 LEDs) | 1 | Individually addressable RGB strip |
| 22 AWG Wire | 3-4 color variations | For general wiring connections |
| BTF-LIGHTING 3-Pin JST SM LED Connector (20AWG) | 1 | Two meter extension cable for WS2812B LED strip|
| Capacitor (1000 µF) | 1 | Prevents voltage spikes for LEDs |
| Arduino Nano ESP32 with Headers [ABX00083] | 1 | Microcontroller with Wi-Fi support |

### Tools & Assembly Materials

| Tool / Material | Quantity | Purpose |
|------------------|-----------|----------|
| Double-Sided Tape | 1 | Used for minor connections like the sensor on the doorstop |
| Wire Stripper & Cutter (22–10 AWG) | 1 | For trimming and connecting wires |
| Velcro Strips | 1 | Mounts components to ceiling |

---
## Code
Language: C/C++

Platform: Arduino IDE

Board: Arduino Nano ESP32 (ABX00083)

Note: Feel free to reference the source code that is titled parking-system-code.ino under the folder, arduino-code. You can easily adjust distance thresholds and LED brightness to make the project work for different cars and situations. To upload the updated code, plug your device into the microcontroller by USB-C connection.

## Required Libraries

Install these libraries from Arduino IDE → Sketch → Include Library → Manage Libraries

| Library | Author | Purpose | 
|----------|---------|----------|
| Adafruit NeoPixel | Adafruit | Controls WS2812B RGB LEDs | 
| TFMPlus | Bud Ryerson | Interfaces with TFmini Plus LiDAR | 

---

## Circuit Wiring

| Component | Arduino Pin | Notes |
|------------|--------------|-------|
| TFmini Plus TX | RX0 (GPIO43) | UART communication |
| TFmini Plus RX | TX1 (GPIO44) | UART communication |
| WS2812B LED Data | D2 (GPIO5) | Defined as `LED_PIN` in code |
| Power (VCC) | VBUS | Provides 5V shared between LiDAR and LED strip |
| Ground (GND) | Blank white pin | Common ground connection |

![Wiring Diagram](images/wiring-diagram.jpeg)
![Final Installation](images/ceiling-setup.jpeg)

MIT License  
© 2025 Noah Barkol
