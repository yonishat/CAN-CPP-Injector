# 🚗 Vehicle CAN Bus Penetration Testing Tool (C++)

This project is a custom-built, Object-Oriented penetration testing tool designed to conduct cybersecurity threat analysis and vulnerability validation on automotive Electronic Control Units (ECUs). Developed in **C++** for Linux environments, it interacts directly with the lowest layers of the network via SocketCAN.

The tool was created to simulate real-world hacking scenarios on vehicle networks, specifically focusing on the Controller Area Network (CAN) bus. By utilizing a virtual vehicle environment (ICSim), this project demonstrates the complete lifecycle of a penetration test: from initial network reconnaissance and threat analysis to the development of an automated C++ script that successfully injects spoofed payloads (Replay Attacks) to manipulate vehicle actuators.

## 🔍 Reverse Engineering Methodology

**Reconnaissance:** I utilized `candump` to monitor the `vcan0` interface and establish a baseline of background CAN traffic.

<img src="https://github.com/yonishat/CAN-CPP-Injector/blob/118a5ec7c5ee77ec7605a9d7dddd3be774736178/include/Normal_ICSim-candump.png"/>

**Isolation & Fuzzing:** I used `cansniffer` to filter out static packets. By physically triggering the virtual vehicle controls (unlocking doors, spiking speedometer) while monitoring the sniffer, I was able to correlate physical actions to specific ID state changes.

**Payload Identification:** Isolated specific controller IDs, such as 0x19B for the Door Control Unit. I identified that modifying Byte 2 to `0x0E` triggered the unlock actuator.

## Key Objectives Achieved:

I built this interactive C++ tool to bypass high-level APIs to write raw binary frames directly to the network interface using Linux socket programming.

<img src="https://github.com/yonishat/CAN-CPP-Injector/blob/118a5ec7c5ee77ec7605a9d7dddd3be774736178/include/Attack_menu_1.png"/>
<img src="https://github.com/yonishat/CAN-CPP-Injector/blob/118a5ec7c5ee77ec7605a9d7dddd3be774736178/include/ICSim_attack-display.png"/>

## 🛠️ Prerequisites & Build Instructions

**Environment:**
* Linux OS (Kali Linux recommended)
* `vcan0` virtual interface enabled
* ICSim (Instrument Cluster Simulator)
* CMake & GCC/G++ Compiler

**Build Steps:**

1. `git clone https://github.com/yonishat/CAN-CPP-Injector.git`
2. `cd CAN-CPP-Injector`
3. `mkdir build && cd build`
4. `cmake ..`
5. `make`
6. `./can_injector`
