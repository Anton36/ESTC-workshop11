

#include "led_handler.h"
#include "nrf_log.h"
#include "pwm_handler.h"
#include "nrfx_pwm.h"
#include <stdint.h>
#include "fds.h"

#define FILE_ID 0x0010      /* The ID of the file to write the records into. */
#define RECORD_KEY 0x1101 /* A key for the first record. */



static void fds_evt_handler(fds_evt_t const *p_fds_evt)
{
    switch (p_fds_evt->id)
    {
    case FDS_EVT_INIT:
        if (p_fds_evt->result != NRF_SUCCESS)
        {
            // Initialization failed.
        }
        break;
    default:
        break;
    }
}
void estc_fds_init()
{
    
    ret_code_t ret = fds_register(fds_evt_handler);

    ret = fds_init();
    if (ret == FDS_ERR_NO_PAGES)
    {
        rgb_led_state.is_led_on = true;
    }
}




void fds_write_data(void)
{
    fds_record_t record;
    fds_find_token_t ftok;
    fds_record_desc_t record_desc;
    memset(&ftok, 0, sizeof(fds_find_token_t));

    // Set up record.
    record.file_id = FILE_ID;
    record.key = RECORD_KEY;
    record.data.p_data = (void *)&rgb_led_state;
    record.data.length_words = sizeof(rgb_led_state_t) / 4;
    ret_code_t rc;
    if (fds_record_find(FILE_ID, RECORD_KEY, &record_desc, &ftok) == NRF_SUCCESS)
    {
        rc = fds_record_update(&record_desc, &record);
        NRF_LOG_INFO("led parametrs have been update")
        NRF_LOG_INFO("RGB: R=%d, G=%d, B=%d", rgb_led_state.red, rgb_led_state.green, rgb_led_state.blue);
        NRF_LOG_INFO("led state=%d", rgb_led_state.is_led_on);
    }
    else
    {
        rc = fds_record_write(&record_desc, &record);
        NRF_LOG_INFO("led parametrs have been write")
        NRF_LOG_INFO("RGB: R=%d, G=%d, B=%d", rgb_led_state.red, rgb_led_state.green, rgb_led_state.blue);
        NRF_LOG_INFO("led state=%d", rgb_led_state.is_led_on);
    }
   

    if (rc != NRF_SUCCESS)
    {
    }
}

void fds_read_data(void)
{
    fds_flash_record_t flash_record;
    fds_find_token_t ftok;
    fds_record_desc_t record_desc;
    /* It is required to zero the token before first use. */
    memset(&ftok, 0, sizeof(fds_find_token_t));
    NRF_LOG_INFO("entering read memory zone")
  
    if (fds_record_find(FILE_ID, RECORD_KEY, &record_desc, &ftok) == NRF_SUCCESS)
    {
        NRF_LOG_INFO("data find")

        if (fds_record_open(&record_desc, &flash_record) == NRF_SUCCESS)
        {
            rgb_led_state = *(rgb_led_state_t *)flash_record.p_data;

            NRF_LOG_INFO("led parametrs have been read from memory")
            NRF_LOG_INFO("RGB: R=%d, G=%d, B=%d", rgb_led_state.red, rgb_led_state.green, rgb_led_state.blue);
            NRF_LOG_INFO("led state=%d", rgb_led_state.is_led_on);

        }

        if (fds_record_close(&record_desc) != NRF_SUCCESS)
        {
            /* Handle error. */
        }
    }
}
