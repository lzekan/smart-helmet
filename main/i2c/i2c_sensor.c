#include "i2c_sensor.h"
#include "driver/i2c.h"

esp_err_t i2c_sensor_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO_0,
        .scl_io_num = I2C_MASTER_SCL_IO_0,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    esp_err_t err = i2c_param_config(I2C_MASTER_NUM_0, &conf);
    
    if (err != ESP_OK)
    {
        return err;
    } 
    
    return i2c_driver_install(I2C_MASTER_NUM_0, conf.mode,
                              I2C_MASTER_RX_BUF_DISABLE,
                              I2C_MASTER_TX_BUF_DISABLE, 0);
}
