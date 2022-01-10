#ifndef RAPIDCDH_GLOBALS_H
#define RAPIDCDH_GLOBALS_H

namespace constants {
    inline constexpr bool DEBUG = true;

    // WiringPi pins
    inline constexpr uint8_t UCAM_RESET_PIN = 7;

    // Serial
    inline const char* SERIAL_DEV_0 = "/dev/ttyAMA0";
    inline constexpr uint32_t SERIAL_BAUD_RATE = 921600;
}

// Error codes
enum Status {
    SUCCESS,
    FAILURE,
};

#endif
