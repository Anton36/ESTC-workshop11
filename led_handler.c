#include "led_handler.h"

#include "nrf_log.h"
#include "nrf_gpio.h"
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


#include "nrf_log_backend_usb.h"
uint32_t duty_cycle = 0;

int led_digits[] = {LED0_GREEN_PIN, LED1_RED_PIN, LED2_GREEN_PIN, LED3_BLUE_PIN};



rgb_led_state_t rgb_led_state = {
    .red = 0,
    .green = 6,
    .blue = 242,
    .is_led_on = false,
};

void led_on(int led_index)
{
    nrf_gpio_pin_write(led_digits[led_index], LED_ON_STATE);
}

void led_off(int led_index)
{
    nrf_gpio_pin_write(led_digits[led_index], LED_OFF_STATE);
}

void led_init()
{
    nrf_gpio_cfg_output(LED0_GREEN_PIN); // LED0
    nrf_gpio_cfg_output(LED1_RED_PIN);   // LED1
    nrf_gpio_cfg_output(LED2_GREEN_PIN); // LED2
    nrf_gpio_cfg_output(LED3_BLUE_PIN);  // LED3
    for (int i = 0; i < LEDS_NUMBER; i++)
    {
        nrf_gpio_pin_write(led_digits[i], LED_OFF_STATE);
    }
}

void display_current_color(void)
{

    pwm_set_duty_cycle(0, rgb_led_state.red);
    pwm_set_duty_cycle(1, rgb_led_state.green);
    pwm_set_duty_cycle(2, rgb_led_state.blue);
}
