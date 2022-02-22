add_library(SerialPort
            SerialPort.cpp
            SerialPort.h
            gcode_program.cpp
            gcode_program.h
            parser.cpp
            parser.h
            GCode.h
            GCode.cpp
            Arduino.h
            Arduino.cpp)

add_executable(serial main.cpp)

target_link_libraries(serial PUBLIC SerialPort)

target_include_directories(SerialPort PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")