#include "driver/gpio.h"
#include "./psee-fun.h"
#include "driver/gpio.h"
#include "rom/gpio.h"

void setup_sensors()
{
    esp_rom_gpio_pad_select_gpio(LED_PIN_RED);
    gpio_set_direction(LED_PIN_RED, GPIO_MODE_OUTPUT);    
    esp_rom_gpio_pad_select_gpio(LED_PIN_YELLOW);
    gpio_set_direction(LED_PIN_YELLOW, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(BUTTON);
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_pad_select_gpio(SENSOR_CLOSE);
    gpio_set_direction(SENSOR_CLOSE, GPIO_MODE_INPUT);
    gpio_pad_select_gpio(SENSOR_OPEN);
    gpio_set_direction(SENSOR_OPEN, GPIO_MODE_INPUT);  


}
