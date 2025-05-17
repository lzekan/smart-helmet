#include "i2c_bmi270.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include <string.h>
#include "esp_rom_sys.h"
#include "../drivers/bmi270/bmi2_defs.h"
#include "../drivers/bmi270/bmi2.h"
#include "../drivers/bmi270/bmi270.h"

#define TAG "BMI270"

#define BMI270_I2C_ADDR 0x68 // Or 0x69 depending on the AD0 pin

// Delay function (in microseconds)
void bmi2_delay_us(uint32_t period, void *intf_ptr) {
    esp_rom_delay_us(period);
}

// I2C read function
int8_t bmi2_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = *((uint8_t*)intf_ptr);
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    return ret == ESP_OK ? BMI2_OK : BMI2_E_COM_FAIL;
}

// I2C write function
int8_t bmi2_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = *((uint8_t*)intf_ptr);
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write(cmd, (uint8_t *)data, len, true);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    return ret == ESP_OK ? BMI2_OK : BMI2_E_COM_FAIL;
}

// Sensor initialization
int8_t bmi270_init_sensor(struct bmi2_dev *dev) {
    static uint8_t dev_addr = BMI270_I2C_ADDR;

    dev->intf = BMI2_I2C_INTF;
    dev->read = bmi2_i2c_read;
    dev->write = bmi2_i2c_write;
    dev->delay_us = bmi2_delay_us;
    dev->intf_ptr = &dev_addr;
    dev->read_write_len = 32;
    dev->config_file_ptr = NULL;

    int8_t rslt = bmi2_init(dev);  // Step 1
    if (rslt != BMI2_OK) {
        ESP_LOGE(TAG, "bmi2_init failed: %d", rslt);
        return rslt;
    }

    rslt = bmi2_set_config_file(dev);  // Step 2
    if (rslt != BMI2_OK) {
        ESP_LOGE(TAG, "bmi2_set_config_file failed: %d", rslt);
        return rslt;
    }

    uint8_t sensors[] = { BMI2_ACCEL, BMI2_GYRO };
    rslt = bmi2_sensor_enable(sensors, 2, dev);  // Step 3
    if (rslt != BMI2_OK) {
        ESP_LOGE(TAG, "bmi2_sensor_enable failed: %d", rslt);
    }

    return rslt;
}
