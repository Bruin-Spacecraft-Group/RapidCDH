#ifndef RAPIDCDH_UCAM_III_H
#define RAPIDCDH_UCAM_III_H

#include <iostream>
#include <string>
#include <cstdint>

class UCamIII {
public:
    UCamIII(const char* serial_dev, const int baud_rate, const int rst_pin);
    ~UCamIII();

    void initialize();
    void hardware_reset() const;

    void send_cmd(int cmd, uint8_t param1, uint8_t param2, uint8_t param3, uint8_t param4) const;
    void receive_cmd(int* data) const;

    // Commands
    void sync() const;

    // Enums
    enum CmdID {
        CMD_INITIAL          = 0x01,
        CMD_GET_PICTURE      = 0x04,
        CMD_SNAPSHOT         = 0x05,
        CMD_SET_PACKAGE_SIZE = 0x06,
        CMD_SET_BAUD_RATE    = 0x07,
        CMD_RESET            = 0x08,
        CMD_DATA             = 0x0A,
        CMD_SYNC             = 0x0D,
        CMD_ACK              = 0x0E,
        CMD_NAK              = 0x0F,
        CMD_LIGHT            = 0x13,
        CMD_SET_TONE         = 0x14, // Contrast, brightness, exposure
        CMD_SLEEP            = 0x15
    };

    enum ImgFormat {
        FMT_RAW_GRAY_8    = 0x03, // 8-bit Gray Scale (RAW, 8-bit for Y only)
        FMT_RAW_CrYCbY_16 = 0x08, // 16-bit Colour (RAW, CrYCbY)
        FMT_RAW_RGB_16    = 0x06, // 16-bit Colour (RAW, 565(RGB))
        FMT_JPEG          = 0x07
    };

    enum RawRes {
        RAW_60x80   = 0x01,
        RAW_160x120 = 0x03,
        RAW_128x128 = 0x09,
        RAW_128x96  = 0x0B
    };

    enum JPEGRes {
        JPEG_160x128 = 0x03,
        JPEG_320x240 = 0x05,
        JPEG_640x480 = 0x07
    };

    enum PictureType {
        PIC_SNAPSHOT = 0x01,
        PIC_RAW      = 0x02,
        PIC_JPEG     = 0x05
    };

    enum SnapshotType {
        SNAP_JPEG, // Compressed
        SNAP_RAW   // Uncompressed
    };

    enum ResetType {
        RST_ALL,            // Resets the whole system. The uCAM-III will reboot and reset all registers and state machines.
        RST_STATE_MACHINES  // Resets the state machines only
    };

    enum Error {
        ERR_NONE,
        ERR_PICTURE_TYPE,
        ERR_PICTURE_UP_SCALE,
        ERR_PICTURE_SCALE,
        ERR_UNEXPECTED_REPLY,
        ERR_SEND_PICTURE_TIMEOUT,
        ERR_UNEXPECTED_COMMAND,
        ERR_SRAM_JPEG_TYPE,
        ERR_SRAM_JPEG_SIZE,
        ERR_PICTURE_FORMAT,
        ERR_PICTURE_SIZE,
        ERR_PARAMETER,
        ERR_SEND_REGISTER_TIMEOUT,
        ERR_COMMAND_ID,
        ERR_PICTURE_NOT_READY,
        ERR_TRANSFER_PACKAGE_NUM,
        ERR_SET_TRANSFER_PACKAGE_SIZE_WRONG,
        ERR_COMMAND_HEADER,
        ERR_COMMAND_LENGTH,
        ERR_SEND_PICTURE,
        ERR_SEND_COMMAND
    };

    enum LightFreqType { // Hz
        FREQ_50,
        FREQ_60
    };

    // For brightness, contrast, exposure
    enum Tone {
        TONE_MIN,    // Exposure: -2
        TONE_LOW,    // Exposure: -1
        TONE_NORMAL, // Default. Exposure: 0
        TONE_HIGH,   // Exposure: +1
        TONE_MAX     // Exposure: +2
    };

private:
    const char* serial_dev;
    int baud_rate;
    int serial_port;
    int rst_pin;
};

class UCamIIIException {
public:
    UCamIIIException(const std::string &msg) {
        std::cout << "UCam Error: " << msg << std::endl;
    }

    UCamIIIException(int err) {
        std::cout << "UCam Error: ";

        switch (err) {
            case UCamIII::ERR_PICTURE_TYPE:
                std::cout << "Picture type error";
                break;
            case UCamIII::ERR_PICTURE_UP_SCALE:
                std::cout << "Picture up scale";
                break;
            case UCamIII::ERR_PICTURE_SCALE:
                std::cout << "Picture scale error";
                break;
            case UCamIII::ERR_UNEXPECTED_REPLY:
                std::cout << "Unexpected reply";
                break;
            case UCamIII::ERR_SEND_PICTURE_TIMEOUT:
                std::cout << "Send picture timeout";
                break;
            case UCamIII::ERR_UNEXPECTED_COMMAND:
                std::cout << "Unexpected command";
                break;
            case UCamIII::ERR_SRAM_JPEG_TYPE:
                std::cout << "SRAM JPEG type error";
                break;
            case UCamIII::ERR_SRAM_JPEG_SIZE:
                std::cout << "SRAM JPEG size error";
                break;
            case UCamIII::ERR_PICTURE_FORMAT:
                std::cout << "Picture format error";
                break;
            case UCamIII::ERR_PICTURE_SIZE:
                std::cout << "Picture size error";
                break;
            case UCamIII::ERR_PARAMETER:
                std::cout << "Parameter error";
                break;
            case UCamIII::ERR_SEND_REGISTER_TIMEOUT:
                std::cout << "Send register timeout";
                break;
            case UCamIII::ERR_COMMAND_ID:
                std::cout << "Command ID error";
                break;
            case UCamIII::ERR_PICTURE_NOT_READY:
                std::cout << "Picture not ready";
                break;
            case UCamIII::ERR_TRANSFER_PACKAGE_NUM:
                std::cout << "Transfer package number error";
                break;
            case UCamIII::ERR_SET_TRANSFER_PACKAGE_SIZE_WRONG:
                std::cout << "Set transfer package size wrong";
                break;
            case UCamIII::ERR_COMMAND_HEADER:
                std::cout << "Command header error";
                break;
            case UCamIII::ERR_COMMAND_LENGTH:
                std::cout << "Command length error";
                break;
            case UCamIII::ERR_SEND_PICTURE:
                std::cout << "Send picture error";
                break;
            case UCamIII::ERR_SEND_COMMAND:
                std::cout << "Send command error";
                break;
            default:
                std::cout << "Unknown error";
                break;
        }

        std::cout << std::endl;
    }
};

#endif //RAPIDCDH_UCAM_III_H