#include <stdio.h>
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GPIO_PIN 15  // Define o número do pino
#define GPIO_PIN2 2
#define ADC_WIDTH ADC_WIDTH_BIT_12  // Definir resolução do ADC para 12 bits
#define ADC1_CHANNEL ADC1_CHANNEL_0 // GPIO36 está no ADC1_CHANNEL_0


void app_main(void)
{
    // Configura GPIO15 como saída
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;   // Sem interrupção
    io_conf.pin_bit_mask = (1ULL << GPIO_PIN);  // Definindo GPIO15
    io_conf.mode = GPIO_MODE_OUTPUT;         // Modo de saída
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE; // Sem pull-up
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // Sem pull-down
    gpio_config(&io_conf);  // Aplica a configuração

     // Configuração do ADC
    adc1_config_width(ADC_WIDTH);  // Define a largura do ADC (12 bits)
    adc1_config_channel_atten(ADC1_CHANNEL, ADC_ATTEN_DB_6);  // Configura o atenuador para 0 dB (tensão de 0-3V3)

    while (1) {
        // // Coloca GPIO15 em nível alto
        // gpio_set_level(GPIO_PIN, 1);
        // printf("GPIO15 is HIGH\n");
        // vTaskDelay(1000 / portTICK_PERIOD_MS); // Espera 1 segundo

        // // Coloca GPIO15 em nível baixo
        // gpio_set_level(GPIO_PIN, 0);
        // printf("GPIO15 is LOW\n");
        // vTaskDelay(1000 / portTICK_PERIOD_MS); // Espera 1 segundo

        int adc_value = adc1_get_raw(ADC1_CHANNEL);

        printf("Leitura analógica do GPIO2: %d\n", adc_value);
        if (adc_value > 4000) {
          gpio_set_level(GPIO_PIN, 1);
        } else {
          gpio_set_level(GPIO_PIN, 0);
        }
    }
}
