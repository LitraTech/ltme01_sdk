#include "ltme01_sdk/Device.h"
#include "ltme01_sdk/lan/LanLocation.h"

#include <iostream>
#include <thread>

#define PACKET_COUNT_PER_FRAME 24

int main(int argc, char* argv[])
{
  // Specify device location by providing its IP address and data channel port
  // (default to 192.168.10.160 and 8100 respectively, can be configured by user)
  ltme01_sdk::LanLocation device_address(inet_addr("192.168.10.160"), htons(8100));

  // Create device instance
  ltme01_sdk::Device device(device_address);

  // Try opening device
  int error_code = device.open();
  if (error_code != ltme01_sdk::RESULT_SUCCESS) {
    std::cerr << "Error: Failed to open device (" << error_code << ")" << std::endl;
    return -1;
  }
  else {
    // Put device into low-power mode, then bring it back to normal operation
    for (int i = 0; i < 3; i++) {
      std::cout << "[" << i << "] Entering low-power mode... ";
      bool success = device.enterLowPowerMode();
      std::cout << (success ? "Done" : "Failed") << std::endl;

      std::this_thread::sleep_for(std::chrono::seconds(3));

      std::cout << "[" << i << "] Exiting low-power mode... ";
      success = device.exitLowPowerMode();
      std::cout << (success ? "Done" : "Failed") << std::endl;

      std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    std::cout << "Waiting for device to become stable";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "." << std::endl;

    auto readRangeData = [&device](ltme01_sdk::DataPacket& dataPacket) {
      int result = device.readDataPacket(dataPacket, 6000);
      if (result != ltme01_sdk::RESULT_SUCCESS)
        throw std::exception();
    };

    ltme01_sdk::DataPacket dataPacket;
    try {
      // Read and discard stale data packets possibly cached by operating system
      for (int i = 0; i < 100; i++)
        readRangeData(dataPacket);

      do {
        readRangeData(dataPacket);
      }
      while (dataPacket.index() != PACKET_COUNT_PER_FRAME - 1);

      for (int i = 0; i < PACKET_COUNT_PER_FRAME * 450; i++) {
        readRangeData(dataPacket);
        if (dataPacket.isValid()) {
          if (dataPacket.index() != PACKET_COUNT_PER_FRAME - 1)
            std::cout << (int)dataPacket.index() << " ";
          else
            std::cout << (int)dataPacket.index() << std::endl;
        }
        else
          std::cout << ".";
      }
    }
    catch (std::exception& e) {
      std::cerr << "Error reading data from device" << std::endl;
    }

    // Close device
    device.close();

    std::cout << "Device closed" << std::endl;
  }

  return 0;
}
