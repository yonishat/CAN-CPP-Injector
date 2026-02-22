# 🚗 Vehicle CAN Bus Penetration Testing Tool (C++)
This project is a custom-built, Object-Oriented penetration testing tool designed to conduct cybersecurity threat analysis and vulnerability validation on automotive Electronic Control Units (ECUs). Developed in **C++** for Linux environments, it interacts directly with the lowest layers of the network via SocketCAN.
The tool was created to simulate real-world hacking scenarios on vehicle networks, specifically focusing on the Controller Area Network (CAN) bus. By utilizing a virtual vehicle environment (ICSim), this project demonstrates the complete lifecycle of a penetration test: from initial network reconnaissance and threat analysis to the development of an automated C++ script that successfully injects spoofed payloads (Replay Attacks) to manipulate vehicle actuators.

## 🔍 Reverse Engineering Methodology

**Reconnaissance:** I utilized `candump` to monitor the `vcan0` interface and establish a baseline of background CAN traffic.
<img width="1091" height="387" alt="vcan0_CAN-dump" src="https://github.com/user-attachments/assets/8959e93c-3ae5-4439-8b89-ed52c0e26c0f" />

**Isolation & Fuzzing:** I used `cansniffer` to filter out static packets. By physically triggering the virtual vehicle controls (unlocking doors, spiking speedometer) while monitoring the sniffer, I was able to correlate physical actions to specific ID state changes.
**Payload Identification:** for example the ID `0x19B` was isolated as the Door Control Unit. I identified that modifying Byte 2 to `0x0E` triggered the unlock actuator.

## Key Objective Achieved:
I built this interactive C++ tool to bypass high-level APIs to write raw binary frames directly to the network interface using Linux socket programming.
<img width="401" height="282" alt="attacking" src="https://github.com/user-attachments/assets/5cc00754-480f-4130-bf8f-b0fad182e107" /> <img width="696" height="366" alt="attacked-door" src="https://github.com/user-attachments/assets/dd624e5b-0602-451e-83cb-ca5bf6f25fe9" />
