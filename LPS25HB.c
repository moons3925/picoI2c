#include "LPS25HB.h"

bool LPS25HB_init(i2c_inst_t *i2c, uint8_t *buf) {
    bool result;
    buf[0] = WHO_AM_I;
    result = LPS25HB_write(i2c, buf, 1, true);
    if (result) {
        result = LPS25HB_read(i2c, buf, 1, false);
        if (result) {
            if (LPS25HB_DEVICE_CODE == buf[0]) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool LPS25HB_write(i2c_inst_t *i2c, uint8_t *buf, int length, bool nostop) {
    int ret = i2c_write_timeout_us(i2c, LPS25HB_ADRS, buf, length, nostop,
                                   10000 * length);
    if (ret == length) {
#ifdef PICO_DEBUG
        puts("I2C write success.");
#endif
        return true;
    } else {
#ifdef PICO_DEBUG
        if (PICO_ERROR_GENERIC == ret) {
            puts("PICO Error Generic.");
        } else if (PICO_ERROR_TIMEOUT == ret) {
            puts("PICO Error timeout.");
        }
#endif
    }
    return false;
}

bool LPS25HB_read(i2c_inst_t *i2c, uint8_t *buf, int length, bool nostop) {
    int ret = i2c_read_timeout_us(i2c, LPS25HB_ADRS, buf, length, nostop,
                                  10000 * length);
    if (ret == length) {
#ifdef PICO_DEBUG
        puts("I2C read success.");
#endif
        return true;
    } else {
#ifdef PICO_DEBUG
        if (PICO_ERROR_GENERIC == ret) {
            puts("PICO Error Generic.");
        } else if (PICO_ERROR_TIMEOUT == ret) {
            puts("PICO Error timeout.");
        }
#endif
    }
    return false;
}
