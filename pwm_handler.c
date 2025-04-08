

#include "led_handler.h"
#include "nrf_log.h"
#include "pwm_handler.h"
#include "nrfx_pwm.h"
#include <stdint.h>
#include "app_timer.h"



static nrfx_pwm_t pwm = NRFX_PWM_INSTANCE(0);

static nrf_pwm_values_individual_t pwm_values;
static nrf_pwm_sequence_t const pwm_seq =
    {
        .values.p_individual = &pwm_values,
        .length = NRF_PWM_VALUES_LENGTH(pwm_values),
        .repeats = 0,
        .end_delay = 0};

void pwm_init()
{

    nrfx_pwm_config_t pwm_config =
        {
            .output_pins = {LED1_RED_PIN | NRFX_PWM_PIN_INVERTED,
                            LED2_GREEN_PIN | NRFX_PWM_PIN_INVERTED,
                            LED3_BLUE_PIN | NRFX_PWM_PIN_INVERTED},
            .irq_priority = NRFX_PWM_DEFAULT_CONFIG_IRQ_PRIORITY,
            .base_clock = (nrf_pwm_clk_t)NRFX_PWM_DEFAULT_CONFIG_BASE_CLOCK,
            .count_mode = (nrf_pwm_mode_t)NRFX_PWM_DEFAULT_CONFIG_COUNT_MODE,
            .top_value = PWM_TOP_VALUE,
            .load_mode = NRF_PWM_LOAD_INDIVIDUAL,
            .step_mode = (nrf_pwm_dec_step_t)NRFX_PWM_DEFAULT_CONFIG_STEP_MODE,

        };

    nrfx_pwm_init(&pwm, &pwm_config, NULL);
}

void pwm_playback()
{
    if (rgb_led_state.is_led_on == true)
    {
        if (nrfx_pwm_is_stopped(&pwm))
        {
            nrfx_pwm_simple_playback(&pwm, &pwm_seq, 1, NRFX_PWM_FLAG_LOOP);
            display_current_color();
        }
    }
    else 
    {
        if (!nrfx_pwm_is_stopped(&pwm))
        {
            nrfx_pwm_stop(&pwm,false);
        }
    }
}

void pwm_set_duty_cycle(int channel, int duty_cycle)
{
    duty_cycle %= PWM_TOP_VALUE + 1;

    switch (channel)
    {
    case 0:
        pwm_values.channel_0 = duty_cycle;
        break;
    case 1:
        pwm_values.channel_1 = duty_cycle;
        break;
    case 2:
        pwm_values.channel_2 = duty_cycle;
        break;
    case 3:
        pwm_values.channel_3 = duty_cycle;
        break;
    }
}
