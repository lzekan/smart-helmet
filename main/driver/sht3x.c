#include "sht3x.h"
#include "i2c/i2c_sensor.h"
#include "driver/i2c.h"
#include <math.h>
#include <stdio.h>

esp_err_t sht3x_read_temp_humidity(float *temperature, float *humidity)
{
    uint8_t cmd[] = {0x2C, 0x06};  
    esp_err_t err;

    err = i2c_master_write_to_device(I2C_MASTER_NUM_0, SHT3X_ADDR, cmd, sizeof(cmd), pdMS_TO_TICKS(100));
    if (err != ESP_OK) 
    {
        return err;
    }

    vTaskDelay(pdMS_TO_TICKS(20));  

    uint8_t data[6];
    err = i2c_master_read_from_device(I2C_MASTER_NUM_0, SHT3X_ADDR, data, sizeof(data), pdMS_TO_TICKS(100));
    if (err != ESP_OK) 
    {
        return err;
    }

    uint16_t raw_temp = (data[0] << 8) | data[1];
    uint16_t raw_humidity = (data[3] << 8) | data[4];

    *temperature = -45.0 + 175.0 * ((float)raw_temp / 65535.0);
    *humidity = 100.0 * ((float)raw_humidity / 65535.0);

    return ESP_OK;
}
