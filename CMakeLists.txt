cmake_minimum_required(VERSION 3.27)
project(BluetoothLE)

set(CMAKE_CXX_STANDARD 17)

add_executable(BluetoothLE main.cpp
        source/BluetoothLE.cpp
        include/BluetoothLE.h
)
