#include "sao_leds.h"
#include "leds.h"

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_log.h>

static const char* TAG = "sao_leds";

static TaskHandle_t sao_leds_task_handle = NULL;

void menu_sao_leds(xQueueHandle button_queue)
{
    ESP_LOGI(TAG, "SAO LEDs menu");

    if (sao_leds_task_handle == NULL) {
        BaseType_t result = xTaskCreate(
            sao_leds_test,
            "sao_leds_test",
            4096,
            NULL,
            12,
            &sao_leds_task_handle
        );

        if (result == pdPASS) {
            ESP_LOGI(TAG, "SAO LEDs task started");
        } else {
            ESP_LOGE(TAG, "Failed to start SAO LEDs task");
            sao_leds_task_handle = NULL;
        }
    } else {
        ESP_LOGI(TAG, "SAO LEDs task already running");
    }
}

#define GAMMA_CURVE_SIZE 32 
const uint8_t gamma_curve[GAMMA_CURVE_SIZE] = {0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 32, 64, 128, 255,
                                255, 128, 64, 32, 16, 8, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void sao_leds_test(void* pvParameters) {
    ESP_LOGI(TAG, "SAO LEDs testing started");
    uint16_t hue = 0;
    while(1) {
        for (uint8_t g = 0; g < GAMMA_CURVE_SIZE; g++) {  
            hue += 1;
            hue %= 360;
            led_set_hsv(9, hue, 255, gamma_curve[g]);
            led_set_hsv(10, hue, 255, gamma_curve[(g+5) % GAMMA_CURVE_SIZE]);
            led_set_hsv(11, hue, 255, gamma_curve[(g+10) % GAMMA_CURVE_SIZE]);
            led_set_hsv(12, hue, 255, gamma_curve[(g+15) % GAMMA_CURVE_SIZE]);
            vTaskDelay(pdMS_TO_TICKS(75));
        }
    }
}