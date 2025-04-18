/**
 * Copyright 2022 Evgeniy Morozov
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE
 */

#ifndef ESTC_SERVICE_H__
#define ESTC_SERVICE_H__

#include <stdint.h>
#include <stdbool.h>

#include "ble.h"
#include "sdk_errors.h"

#define ESTC_BASE_UUID {0x1e, 0x5f, 0x00, 0x00, 0xa8, 0x9c, 0x46, 0x7d, 0xa1, 0x73, 0xe9, 0x74, 0x63, 0xea, 0xaf, 0x6d} // UUID: 1e5fxxxx-a89c-467d-a173-e97463eaaf6d

#define ESTC_SERVICE_UUID 0x3000

#define ESTC_GATT_CHAR_RGB_UUID 0x3001

#define ESTC_GATT_CHAR_LED_STATUS_UUID 0x3002

typedef struct
{
    uint16_t service_handle;
    uint16_t connection_handle;
    uint8_t uuid_type;
    ble_gatts_char_handles_t characteristic_RGB_handle;
    ble_gatts_char_handles_t characteristic_LED_status_handle;
    bool is_notification_for_RGB_char_enabled;
    bool is_notification_for_LED_state_char_enabled;

} ble_estc_service_t;

extern ble_estc_service_t estc_service;

ret_code_t estc_ble_service_init(ble_estc_service_t *service);

void estc_ble_service_on_ble_event(const ble_evt_t *ble_evt, void *ctx);


#endif /* ESTC_SERVICE_H__ */