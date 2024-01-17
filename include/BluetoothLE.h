//
// Created by stephen on 08/01/24.
//
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <thread>
#include <mutex>
#include <memory>
#include <shared_mutex>
#include <map>

#ifndef BLUETOOTHLE_BLUETOOTHLE_H
#define BLUETOOTHLE_BLUETOOTHLE_H


class BluetoothLE {

    public:

        typedef enum {
            DisplayOnly,
            DisplayYesNo,
            KeyboardOnly,
            NoInputNoOutput,
            KeyboardDisplay,
        } Capabilities;

    void init();

    std::string capabilities() const;

    void set_capabilities(Capabilities capabilities);

    std::shared_ptr<BluetoothLE> get_agent();

    std::shared_ptr<BluetoothLE> path_get(const std::string& path);

    bool path_exists(const std::string& path);

    private:

    Capabilities _capabilities;

    protected:

    std::string _path;

    std::shared_ptr<BluetoothLE> _conn;

    std::recursive_mutex _child_access_mutex;

    std::map<std::string, std::shared_ptr<BluetoothLE>> _children;
};


#endif //BLUETOOTHLE_BLUETOOTHLE_H
