// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _IOT_POWER_METER_H_
#define _IOT_POWER_METER_H_
#include "esp_system.h"
#include "driver/pcnt.h"

typedef enum {
    PM_BOTH_VC = 0,                 /**< voltage and current are measured at the same time by different pin */
    PM_SINGLE_CURRENT,              /**< only current is measured now */
    PM_SINGLE_VOLTAGE,              /**< only voltage is measured now */
} pm_mode_t;

typedef enum {
    PM_POWER = 0,
    PM_VOLTAGE,
    PM_CURRENT,
} pm_value_type_t;

typedef struct {
    uint8_t power_io_num;               /**< gpio number of the pin outputing power */
    pcnt_unit_t power_pcnt_unit;        /**< pulse count unit of power pin */
    uint32_t power_ref_param;           /**< reference value to calculate actual power value */
    uint8_t voltage_io_num;             /**< gpio number of the pin outputing voltage */
    pcnt_unit_t voltage_pcnt_unit;      /**< pulse count unit of voltage pin */
    uint32_t voltage_ref_param;         /**< reference value to calculate actual voltage value */
    uint8_t current_io_num;             /**< gpio number of the pin outputing current */
    pcnt_unit_t current_pcnt_unit;      /**< pulse count unit of current pin */
    uint32_t current_ref_param;         /**< reference value to calculate actual current value */
    uint8_t sel_io_num;                 /**< gpio number of mode select pin */
    uint8_t sel_level;                  /**< the gpio level you wang to set to mode select pin */
    pm_mode_t pm_mode;                  /**< mode of power meter refer to struct pm_mode_t */
} pm_config_t;

typedef void* pm_handle_t;

/**
  * @brief  create power meter
  *
  * @param  pm_config refer to struct pm_config_t
  *
  * @return the handle of the power meter
  */
pm_handle_t powermeter_create(pm_config_t pm_config);

/**
  * @brief  delete power meter, free memory
  *
  * @param  pm_handle handle of the power meter
  *
  * @return 
  *     - ESP_OK: succeed
  *     - ESP_FAIL: pm_handle is NULL
  */
esp_err_t powermeter_delete(pm_handle_t pm_handle);

/**
  * @brief  read value of power meter
  *
  * @param  pm_handle handle of the power meter
  * @param  value_type which value you want to read, refer to struct pm_value_type_t
  *
  * @return 
  */
uint32_t powermeter_read(pm_handle_t pm_handle, pm_value_type_t value_type);

/**
  * @brief  change the mode of power meter
  *
  * @param  pm_handle handle of the power meter
  * @param  mode the mode you want to change to 
  *
  * @return 
  *     - ESP_OK: succeed
  *     - others: fail
  */
esp_err_t powermeter_change_mode(pm_handle_t pm_handle, pm_mode_t mode);
#endif
