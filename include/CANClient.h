#ifndef CANCLIENT_H
#define CANCLIENT_H

#include <string>
#include <vector>
#include <cstdint>
#include <linux/can.h>

class CANClient {
public:
    // Constructor: Takes the name of the interface (e.g., "vcan0")
    explicit CANClient(const std::string& interface_name);
    
    // Destructor: Automatically closes the socket when done (RAII)
    ~CANClient();

    // Initializes the socket and binds it to the interface
    bool init();

    // Sends a crafted CAN frame
    bool send_frame(uint32_t id, const std::vector<uint8_t>& data);

private:
    std::string ifname;
    int socket_fd;
};

#endif // CANCLIENT_H
