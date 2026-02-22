#include "CANClient.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>

// Constructor initializes the socket file descriptor to -1 (invalid)
CANClient::CANClient(const std::string& interface_name) 
    : ifname(interface_name), socket_fd(-1) {}

// Destructor automatically cleans up
CANClient::~CANClient() {
    if (socket_fd >= 0) {
        close(socket_fd);
        std::cout << "[SYSTEM] Socket " << socket_fd << " closed securely." << std::endl;
    }
}

bool CANClient::init() {
    socket_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (socket_fd < 0) {
        std::cerr << "Failed to open socket!" << std::endl;
        return false;
    }

    struct ifreq ifr;
    std::strncpy(ifr.ifr_name, ifname.c_str(), IFNAMSIZ - 1);
    
    if (ioctl(socket_fd, SIOCGIFINDEX, &ifr) < 0) {
        std::cerr << "Could not find interface: " << ifname << std::endl;
        return false;
    }

    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        std::cerr << "Failed to bind socket to " << ifname << "!" << std::endl;
        return false;
    }

    std::cout << "Successfully bound to " << ifname << " on socket " << socket_fd << std::endl;
    return true;
}

bool CANClient::send_frame(uint32_t id, const std::vector<uint8_t>& data) {
    if (data.size() > 8) {
        std::cerr << "CAN payload cannot exceed 8 bytes!" << std::endl;
        return false;
    }

    struct can_frame frame;
    frame.can_id = id;
    frame.can_dlc = data.size();
    
    // Fill the frame with our vector data
    for (size_t i = 0; i < data.size(); ++i) {
        frame.data[i] = data[i];
    }

    if (write(socket_fd, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        std::cerr << "Failed to inject frame!" << std::endl;
        return false;
    }

    std::cout << "Injected ID: 0x" << std::hex << id << std::dec << " | Bytes: " << data.size() << std::endl;
    return true;
}
