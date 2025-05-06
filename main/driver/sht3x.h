#ifndef SHT3X_H
#define SHT3X_H

#include "esp_err.h"

#define SHT3X_ADDR 0x44

void sht3x_init(void);
esp_err_t sht3x_read_temp_humidity(float *temperature, float *humidity);

#endif
