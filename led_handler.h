#ifndef LED_HANDLER_H
#define LED_HANDLER_H
#include "pwm_handler.h"

#define LED_ON_STATE 0
#define LED_OFF_STATE 1
#define LEDS_NUMBER 4
#define LED0_GREEN_PIN NRF_GPIO_PIN_MAP(0, 6)
#define LED1_RED_PIN NRF_GPIO_PIN_MAP(0, 8)
#define LED2_GREEN_PIN NRF_GPIO_PIN_MAP(1, 9)
#define LED3_BLUE_PIN NRF_GPIO_PIN_MAP(0, 12)
#define RGB_MAX_VALUE 255
#define MAX_NAME_LENGHT 12


extern int led_digits[];
extern uint32_t duty_cycle;

void led_on(int);
void led_off(int);
void led_init(void);
void display_current_color(void);

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t is_led_on;
} rgb_led_state_t;
extern rgb_led_state_t rgb_led_state;



#endif