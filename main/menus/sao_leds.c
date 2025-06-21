#include "sao_leds.h"
#include "leds.h"

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_log.h>

static const char* TAG = "sao_leds";

void menu_sao_leds(xQueueHandle button_queue)
{
    ESP_LOGI(TAG, "SAO LEDs menu");

    xTaskCreate(sao_leds_test, "sao_leds_test", 4096, NULL, 12, NULL);
}

void sao_leds_test(void* pvParameters) {
    ESP_LOGI(TAG, "SAO LEDs test");
    leds_off();
    ESP_LOGI(TAG, "All LEDS off");
    
    led_set(9, 0xFF, 0x00, 0x00);
    led_set(10, 0x00, 0xFF, 0x00);
    led_set(11, 0x00, 0x00, 0xFF);


    vTaskDelay(pdMS_TO_TICKS(1000));

    while (true) {
        for (uint16_t h = 0; h < 360; h++) {
            led_set_hsv(12,  (h +   0) % 360, 255, 255);
            led_set_hsv(11,  (h +  10) % 360, 255, 255);
            led_set_hsv(10,  (h +  20) % 360, 255, 255);
            led_set_hsv(9, (h +  30) % 360, 255, 255);
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }


    vTaskDelete(NULL);
}
