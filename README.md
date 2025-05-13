# bomb-disposal-robot
Remote-controlled bomb disposal robot with metal detection, ESP32-CAM live video, and robotic arm for safe object handling.
# Bomb Disposal Robot

A multifunctional **remote-controlled bomb disposal robot** equipped with **metal detection**, **live video surveillance**, and a **robotic arm** for safe object handling. Designed for hazardous environments, this robot enhances safety and situational awareness for bomb disposal units.

---

## Key Features

- **Live Video Streaming** using ESP32-CAM
- **Metal Detection System** for identifying dangerous objects
- **Robotic Arm** for safe pickup and disposal of suspicious items
- **Wireless Control** via C6 Remote Controller or RF module
- Compact and rugged design for mobility in narrow/hostile environments

---

## Technologies & Components Used

| Module             | Tools / Components                       |
|--------------------|-------------------------------------------|
| Microcontroller    | Arduino UNO / ESP32 / NodeMCU             |
| Camera             | ESP32-CAM (for live video streaming)      |
| Metal Detection    | Inductive/Capacitive Metal Sensor         |
| Actuation          | Servo motors, DC motors, L298N motor driver |
| Robotic Arm        | Servo-based 3-DOF arm                     |
| Control System     | C6 Controller / RF Module (433 MHz)       |
| Power              | Li-ion Battery Pack, Voltage Regulator    |
| Programming        | C/C++ (Arduino IDE), MicroPython (optional) |

---

## How It Works

1. **Control**: Robot is remotely operated via C6 controller or RF receiver.
2. **Camera**: ESP32-CAM module streams live video to mobile or laptop.
3. **Detection**: Metal sensor detects objects; buzzer/LED alerts.
4. **Arm**: On command, the robotic arm grips and moves the object to a safe location.

---

## Applications

- Bomb squads and defense operations  
- Industrial safety robots  
- Disaster relief missions (handling unknown metallic objects)  

---

## Future Enhancements

- Add AI-based object recognition to identify threat levels  
- Use GPS for outdoor navigation and geofencing  
- Upgrade to LoRa or Wi-Fi mesh for long-range control  
- Integrate Cloud-based control or FPV dashboard  

---

##Complete demo video link-- https://youtu.be/GatIq7hz0es?si=Gox9diJ3SxNUf2gR


