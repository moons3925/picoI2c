#include <stdio.h>

#include "LPS25HB.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    // I2C Initialisation. Using it at 100KHz.
    i2c_init(i2c0, 100 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);

    puts("Hello, I2C!");

    uint8_t buf[20];

    bool result = LPS25HB_init(i2c0, buf);
    if (result) {
        puts("LPS25HB initialize success.");
        buf[0] = CTRL_REG1;
        buf[1] = WAKE_UP;
        LPS25HB_write(i2c0, buf, 2, false);
        sleep_ms(10);
        buf[0] = P_ADRS | 0x80;
        LPS25HB_write(i2c0, buf, 1, true);
        LPS25HB_read(i2c0, buf, 3, true);

        int pressure = buf[2] << 16 | buf[1] << 8 | buf[0];
        pressure /= 4096;
        printf("Today's atmospheric pressure is %d[hPa].", pressure);

    } else {
        puts("LPS23HB Init failure.");
    }
    return 0;
}
