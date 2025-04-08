#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H


#define DEVICE_NAME "ESTC-Mosolov"              /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME "NordicSemiconductor" /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL 300                    /**< The advertising interval (in units of 0.625 ms. This value corresponds to 187.5 ms). */

#define APP_ADV_DURATION 18000  /**< The advertising duration (180 seconds) in units of 10 milliseconds. */
#define APP_BLE_OBSERVER_PRIO 3 /**< Application's BLE observer priority. You shouldn't need to modify this value. */
#define APP_BLE_CONN_CFG_TAG 1  /**< A tag identifying the SoftDevice BLE configuration. */

#define MIN_CONN_INTERVAL MSEC_TO_UNITS(100, UNIT_1_25_MS) /**< Minimum acceptable connection interval (0.1 seconds). */
#define MAX_CONN_INTERVAL MSEC_TO_UNITS(200, UNIT_1_25_MS) /**< Maximum acceptable connection interval (0.2 second). */
#define SLAVE_LATENCY 0                                    /**< Slave latency. */
#define CONN_SUP_TIMEOUT MSEC_TO_UNITS(4000, UNIT_10_MS)   /**< Connection supervisory timeout (4 seconds). */

#define FIRST_CONN_PARAMS_UPDATE_DELAY APP_TIMER_TICKS(5000) /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
#define NEXT_CONN_PARAMS_UPDATE_DELAY APP_TIMER_TICKS(30000) /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
#define MAX_CONN_PARAMS_UPDATE_COUNT 3                       /**< Number of attempts before giving up the connection parameter negotiation. */



 void advertising_start(void);
 void notification_for_RGB_char(void);
 void notification_for_RGB_char(void);
 void gap_params_init(void);
 void gatt_init(void);
 void nrf_qwr_error_handler(uint32_t nrf_error);
 void services_init(void);
 void on_conn_params_evt(ble_conn_params_evt_t *p_evt);
 void conn_params_error_handler(uint32_t nrf_error);
 void conn_params_init(void);
 void sleep_mode_enter(void);
 void on_adv_evt(ble_adv_evt_t ble_adv_evt);
 void ble_evt_handler(ble_evt_t const *p_ble_evt, void *p_context);
 void ble_stack_init(void);
 void bsp_event_handler(bsp_event_t event);
 void advertising_init(void);

 void rgb_value_update(const ble_gatts_evt_write_t write);
 void led_state_value_update(const ble_gatts_evt_write_t write);
 void peer_manager_init(bool erase_bonds);




#endif