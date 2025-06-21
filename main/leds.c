#include <stdint.h>
#include <stdio.h>
#include "leds.h"
#include <esp_log.h>
#include "ws2812.h"

uint8_t led_buffer[AMOUNT_OF_LEDS * 3] = {0};

static const char* TAG = "leds";

void leds_off(){
    ESP_LOGI(TAG, "Turning off all LEDs");
    for (uint8_t i = 0; i < AMOUNT_OF_LEDS; i++) {
        led_buffer[3 * i + 0] = 0;
        led_buffer[3 * i + 1] = 0;
        led_buffer[3 * i + 2] = 0;
    }
    ws2812_send_data(led_buffer, sizeof(led_buffer));
}

void led_set(uint8_t led, uint8_t r, uint8_t g, uint8_t b) {
    if (led >= AMOUNT_OF_LEDS) return;
    led_buffer[3 * led + 0] = g;
    led_buffer[3 * led + 1] = r;
    led_buffer[3 * led + 2] = b;

    ws2812_send_data(led_buffer, sizeof(led_buffer));
}

// Convert HSV (h: 0–359, s/v: 0–255) to RGB (0–255)
void hsv_to_rgb(uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b) {
    uint8_t region = h / 60;
    uint16_t remainder = (h % 60) * 255 / 60; // scale remainder to 0–255

    uint16_t p = (v * (255 - s)) / 255;
    uint16_t q = (v * (255 - (s * remainder) / 255)) / 255;
    uint16_t t = (v * (255 - (s * (255 - remainder)) / 255)) / 255;

    switch (region) {
        case 0: *r = v; *g = t; *b = p; break;
        case 1: *r = q; *g = v; *b = p; break;
        case 2: *r = p; *g = v; *b = t; break;
        case 3: *r = p; *g = q; *b = v; break;
        case 4: *r = t; *g = p; *b = v; break;
        default: *r = v; *g = p; *b = q; break;
    }
}

void led_set_hsv(uint8_t led, uint16_t h, uint8_t s, uint8_t v) {
    uint8_t r, g, b;

    h = h % 360; // wrap hue to 0–359
    hsv_to_rgb(h, s, v, &r, &g, &b);
    led_set(led, r, g, b);
}

