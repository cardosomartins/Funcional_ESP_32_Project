#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "./psee-fun.h"
#include "driver/gpio.h"
#include "rom/gpio.h"

void app_main(void)
{
    setup_sensors();

    bool gate_status = 0;
    bool sensor_open = 1;
    bool sensor_close = 1;
    bool button = 0;
    bool button_last_state = 0; 
    //Atenção, os sensores tem HIGH/LOW invertidos!
    
    while(true)
    {
        printf("The value of gate_status is: %d \n", gate_status);
        printf("The value of sensor open is: %d \n", sensor_open);
        printf("The value of sensor close is: %d \n", sensor_close);
        printf("The value of button is: %d \n", button);
        printf("The value of button_last_state is: %d \n", button_last_state);
        printf("_______________________________ \n");
        
        sensor_open = gpio_get_level(SENSOR_OPEN);
        sensor_close = gpio_get_level(SENSOR_CLOSE);
        button = gpio_get_level(BUTTON);

        // Inicia quando o botão é pressionado, mas quando seu status anterior não estava pressionado.
        if(button && !button_last_state){
            gate_status = !gate_status;
            
            //Portão abrindo(led amarelo fica aceso):
            if(gate_status == 1){
                gpio_set_level(LED_PIN_YELLOW, gate_status);
                gpio_set_level(LED_PIN_RED, !gate_status);
            }

            //Portão fechando(led vermelho fica aceso):
            if(gate_status == 0){
                gpio_set_level(LED_PIN_YELLOW, gate_status);
                gpio_set_level(LED_PIN_RED, !gate_status);
            }

        }
        
        // Status do portão abrindo ou aberto, mas o sensor detecta aproximação.
        // Logo, o portão já está aberto
        if((gate_status == 1) && (sensor_open == 0)){
            gpio_set_level(LED_PIN_YELLOW, gate_status);
            gpio_set_level(LED_PIN_RED, gate_status);            
        }
        
        // Status do portão fechando ou fechado, mas o sensor mas o sensor detecta aproximação.
        // Logo, o portão já está fechado
        if((gate_status == 0) && (sensor_close == 0)){
            gpio_set_level(LED_PIN_YELLOW, gate_status);
            gpio_set_level(LED_PIN_RED, gate_status);
        }

        // Último estado do botão modificado no final de cada iteração:
        button_last_state = button;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
