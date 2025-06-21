#include <stdint.h>
#include <stdio.h>

#define AMOUNT_OF_LEDS 13

void leds_off();
void led_set(uint8_t led, uint8_t r, uint8_t g, uint8_t b);
void hsv_to_rgb(uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b);
void led_set_hsv(uint8_t led, uint16_t h, uint8_t s, uint8_t v);