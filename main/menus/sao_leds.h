#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

void menu_sao_leds(xQueueHandle button_queue);
void sao_leds_test(void* pvParameters);