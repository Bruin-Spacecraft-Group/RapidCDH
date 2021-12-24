#ifndef RAPIDCDH_UCAM_III_H
#define RAPIDCDH_UCAM_III_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

class UCamIII {
public:
    UCamIII(const char* serial_dev, uint32_t baud_rate, uint8_t rst_pin,
            uint8_t img_format, uint8_t resolution, std::ofstream& fout);
    ~UCamIII();

    void init();
    void sync() const;
    void hard_reset() const;
    void soft_reset(uint8_t rst_type, bool immediate = false) const;

    void send_cmd_unchecked(uint8_t cmd, uint8_t param1 = 0x00, uint8_t param2 = 0x00, uint8_t param3 = 0x00, uint8_t param4 = 0x00) const;
    void send_cmd(uint8_t cmd, uint8_t param1 = 0x00, uint8_t param2 = 0x00, uint8_t param3 = 0x00, uint8_t param4 = 0x00) const;
    void receive_cmd(uint8_t* data, uint8_t len = NUM_CMD_BYTES, uint16_t timeout = 500) const;

    void initial(uint8_t img_format, uint8_t resolution);
    void set_package_size(uint32_t size);
    void set_baud_rate(uint32_t baud_rate);
    void set_light_freq(uint8_t light_freq);
    void set_tone(uint8_t contrast, uint8_t brightness, uint8_t exposure);
    void set_sleep_timeout(uint8_t timeout);

    void snapshot(uint8_t snapshot_type, uint16_t skipped_frames = 0) const;
    [[nodiscard]] uint32_t get_picture(uint8_t picture_type) const;
    void write_jpeg_data(uint32_t len) const;
    void write_raw_data(uint32_t len) const;

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
        FMT_RAW_CRYCBY_16 = 0x08, // 16-bit Colour (RAW, CrYCbY)
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
        RST_FULL,            // Resets the whole system. The uCAM-III will reboot and soft_reset all registers and state machines.
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

    enum LightFreq { // Hz
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
    const char* m_serial_dev;
    uint32_t m_baud_rate;
    uint32_t m_serial_port;
    uint16_t m_serial_timeout = 500; // ms
    uint8_t m_rst_pin;

    uint16_t m_pkg_size;
    uint8_t m_img_format;
    uint8_t m_resolution;

    uint8_t m_light_freq;                  // Hz
    uint8_t m_contrast      = TONE_NORMAL;
    uint8_t m_brightness    = TONE_NORMAL;
    int8_t  m_exposure      = 0;
    uint8_t m_sleep_timeout = 15;          // Seconds

    std::ofstream& m_fout;

    // UCam parameters
    enum Params {
        NUM_CMD_BYTES = 6,     // Number of bytes in one command
        CMD_PREFIX    = 0xAA,  // First byte of all commands
        MAX_PKG_SIZE  = 512,   // Bytes
        MAX_TRIES     = 60     // Max number of tries for SYNC during synchronization
    };

    static void print_cmd(uint8_t * cmd, uint8_t len = NUM_CMD_BYTES);
    static std::string parse_nak_err(uint8_t nak_err);
    static std::string cmd_to_str(uint16_t cmd);
};

#endif //RAPIDCDH_UCAM_III_H