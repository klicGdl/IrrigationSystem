/*----------------------------------------------------------------------*
 *  _   __ _     _____ _____                                            *
 * | | / /| |   |_   _/  __ \   This software is been developed by      *
 * | |/ / | |     | | | /  \/   a group of enthusiast hobbiest          *
 * |    \ | |     | | | |       with the purpose of learn and           *
 * | |\  \| |_____| |_| \__/\   have fun, so nobody is responsible or   *
 * \_| \_/\_____/\___/ \____/   will provide warranty.                  *
 *                                                                      *
 * This software will run in a ESP8266 microcontrolller, the objective  *
 * is to have a irrigation system controler that can read some sensors  *
 * and decide if a valve should be open.                                *
 * There is not restriction to use, modify and improve the code, so     *
 * please do it and share the improvements.                             *
 *                                                                      *
 * Letś have Fun!!                                                      *
 *                                                                      *
 * ---------------------------------------------------------------------*/
#include <Wire.h>

class I2CDevice
{
    uint8_t ADDR; // Address I2C value 7bits format

public:
    I2CDevice() : ADDR(0) {}

    void setAddress(uint8_t addr) { ADDR = addr; }

    bool writeByte(uint8_t data);
    bool writeWord(uint16_t data);

    uint8_t readByte(uint8_t regNum);

    uint8_t getAddress() const { return ADDR; }

    bool isConnected()
    {
        Wire.beginTransmission(ADDR);
        uint8_t error = Wire.endTransmission();
        return error == 0;
    }
};
