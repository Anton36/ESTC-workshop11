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

#include "estc_service.h"

#include "app_error.h"
#include "nrf_log.h"

#include "ble.h"
#include "ble_gatts.h"
#include "ble_srv_common.h"

static ret_code_t estc_ble_add_characteristics(ble_estc_service_t *service);

ble_estc_service_t estc_service = {0};

ret_code_t estc_ble_service_init(ble_estc_service_t *service)
{
    ret_code_t error_code = NRF_SUCCESS;
    ble_uuid_t service_uuid;

    ble_uuid128_t uuid_base = {ESTC_BASE_UUID};
    uint8_t uuid_type;

    error_code = sd_ble_uuid_vs_add(&uuid_base, &uuid_type);
    APP_ERROR_CHECK(error_code);

    service_uuid.type = uuid_type;
    service_uuid.uuid = ESTC_SERVICE_UUID;

    error_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &service_uuid, &estc_service.service_handle);
    APP_ERROR_CHECK(error_code);

    NRF_LOG_DEBUG("%s:%d | Service UUID: 0x%04x", __FUNCTION__, __LINE__, service_uuid.uuid);
    NRF_LOG_DEBUG("%s:%d | Service UUID type: 0x%02x", __FUNCTION__, __LINE__, service_uuid.type);
    NRF_LOG_DEBUG("%s:%d | Service handle: 0x%04x", __FUNCTION__, __LINE__, service->service_handle);

    return estc_ble_add_characteristics(service);
}

static ret_code_t estc_ble_add_characteristics(ble_estc_service_t *service)
{
    ret_code_t error_code = NRF_SUCCESS;

    ble_add_char_user_desc_t add_char_user_desc = {0};
    ble_add_char_params_t add_char_params = {0};
   

    const char char1_descriptor[] = "characteristics 1 with  notifications support";
    const char char2_descriptor[] = "characteristics 2 with indications support";

    

    ble_gatts_char_pf_t char_uint16_pf = {0};
    char_uint16_pf.format = BLE_GATT_CPF_FORMAT_UINT16;
    char_uint16_pf.name_space = BLE_GATT_CPF_NAMESPACE_BTSIG;
    char_uint16_pf.unit = 0x2700;

    ble_gatts_char_pf_t char_uint8_pf = {0};
    char_uint8_pf.format = BLE_GATT_CPF_FORMAT_UINT8;
    char_uint8_pf.name_space = BLE_GATT_CPF_NAMESPACE_BTSIG;
    char_uint8_pf.unit = 0x2700;

    ble_uuid_t characteristic1_uuid;
    characteristic1_uuid.uuid = (uint16_t)ESTC_GATT_CHAR_1_UUID;
    characteristic1_uuid.type = BLE_UUID_TYPE_BLE;

    ble_uuid_t characteristic2_uuid;
    characteristic2_uuid.uuid = (uint16_t)ESTC_GATT_CHAR_2_UUID;
    characteristic2_uuid.type = BLE_UUID_TYPE_BLE;
    
    
    add_char_user_desc.max_size = sizeof(char1_descriptor);
    add_char_user_desc.size = sizeof(char1_descriptor);
    add_char_user_desc.p_char_user_desc = (uint8_t *)char1_descriptor;
    add_char_user_desc.char_props.read = 1;
    add_char_user_desc.read_access = SEC_OPEN;
    add_char_user_desc.is_value_user = 0;


    add_char_params.uuid = characteristic1_uuid.uuid;
    add_char_params.uuid_type = characteristic1_uuid.type;
    add_char_params.max_len = sizeof(uint16_t);
    add_char_params.init_len = sizeof(uint16_t);
    add_char_params.char_props.read = 1;
    add_char_params.char_props.write = 1;
    add_char_params.char_props.notify = 1;
    add_char_params.cccd_write_access = SEC_OPEN;
    add_char_params.p_user_descr = &add_char_user_desc;
    add_char_params.p_presentation_format = &char_uint16_pf;

    

    error_code = characteristic_add(estc_service.service_handle, &add_char_params, &estc_service.characteristic1_handle);
    memset(&add_char_params,0,sizeof(add_char_params));
    memset(&add_char_user_desc,0,sizeof(add_char_user_desc));



    add_char_user_desc.max_size = sizeof(char2_descriptor);
    add_char_user_desc.size = sizeof(char2_descriptor);
    add_char_user_desc.p_char_user_desc = (uint8_t *)char2_descriptor;
    add_char_user_desc.char_props.read = 1;
    add_char_user_desc.read_access = SEC_OPEN;
    add_char_user_desc.is_value_user = 0;


    add_char_params.uuid = characteristic2_uuid.uuid;
    add_char_params.uuid_type = characteristic2_uuid.type;
    add_char_params.max_len = sizeof(uint8_t);
    add_char_params.init_len = sizeof(uint8_t);
    add_char_params.char_props.read = 1;
    add_char_params.char_props.write = 1;
    add_char_params.char_props.indicate = 1;
    add_char_params.cccd_write_access = SEC_OPEN;
    add_char_params.p_user_descr = &add_char_user_desc;
    add_char_params.p_presentation_format = &char_uint8_pf;

    error_code = characteristic_add(estc_service.service_handle, &add_char_params, &estc_service.characteristic2_handle);

    APP_ERROR_CHECK(error_code);

    return NRF_SUCCESS;
}

