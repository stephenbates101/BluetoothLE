#include <iostream>
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <thread>

#include "include/BluetoothLE.h"

BluetoothLE bluez;

int main() {

    std::cout << "Code has Started" << std::endl;

    bluez.init();

    // This is to set the agent so no codes are required, at least from this end
    // still possible that pass/cancel option appears on the phone
    auto agent = bluez.get_agent();

    agent->set_capabilities(BluetoothLE::Capabilities::NoInputNoOutput);

    std::cout << "Code has Finished" << std::endl;
    return 0;
}
