#ifndef I2C_BMI270_H
#define I2C_BMI270_H
#include "../drivers/bmi270/bmi2_defs.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int8_t bmi270_init_sensor(struct bmi2_dev *dev);

int8_t bmi2_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr);
int8_t bmi2_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr);
void bmi2_delay_us(uint32_t period, void *intf_ptr);

#ifdef __cplusplus
}
#endif

#endif // I2C_BMI270_H
