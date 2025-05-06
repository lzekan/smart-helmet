#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "i2c/i2c_lcd.h"
#include "i2c/i2c_sensor.h"
#include "driver/sht3x.h"

void app_main(void)
{
    i2c_sensor_init();
    i2c_lcd_init();     //cekaj ekran da probas

    while (1) 
    {
        float temperature, humidity;
        if (sht3x_read_temp_humidity(&temperature, &humidity) == ESP_OK) 
        {
            printf("Temperature: %.2f °C, Humidity: %.2f %%\n", temperature, humidity);
        } 
        else 
        {
            printf("Failed to read from sensor\n");
        }
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
