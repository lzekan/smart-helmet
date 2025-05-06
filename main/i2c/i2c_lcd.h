#ifndef I2C_LCD_H
#define I2C_LCD_H


#include "esp_err.h"

#define I2C_MASTER_NUM_1       I2C_NUM_1
#define I2C_MASTER_SDA_IO_1    25  
#define I2C_MASTER_SCL_IO_1    26    
#define I2C_MASTER_FREQ_HZ_1   400000
#define I2C_MASTER_TX_BUF_DISABLE  0
#define I2C_MASTER_RX_BUF_DISABLE  0

esp_err_t i2c_lcd_init(void);

#endif // I2C_LCD_H


