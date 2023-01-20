#ifndef __LPS25HB_H
#define __LPS25HB_H

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#define PICO_DEBUG

#define I2C_SDA 20  // 26pin
#define I2C_SCL 21  // 27pin

#define LPS25HB_ADRS 0x5c
#define WHO_AM_I 0x0f
#define CTRL_REG1 0x20
#define WAKE_UP 0x90
#define P_ADRS 0x28
#define LPS25HB_DEVICE_CODE 0xbd

bool LPS25HB_init(i2c_inst_t *, uint8_t *);
bool LPS25HB_write(i2c_inst_t *i2c, uint8_t *, int, bool);
bool LPS25HB_read(i2c_inst_t *i2c, uint8_t *, int, bool);

#endif /* __LPS25HB_H */
