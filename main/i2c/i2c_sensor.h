#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H

#include "esp_err.h"

#define I2C_MASTER_SCL_IO_0          22
#define I2C_MASTER_SDA_IO_0          21
#define I2C_MASTER_NUM_0           I2C_NUM_0
#define I2C_MASTER_FREQ_HZ         100000
#define I2C_MASTER_TX_BUF_DISABLE  0
#define I2C_MASTER_RX_BUF_DISABLE  0

esp_err_t i2c_sensor_init(void);

#endif 
