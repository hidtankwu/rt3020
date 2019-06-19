/**
 * Copyright (C) 2017 - 2019 Richtek
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holder nor the names of the
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 * The information provided is believed to be accurate and reliable.
 * The copyright holder assumes no responsibility
 * for the consequences of use
 * of such information nor for any infringement of patents or
 * other rights of third parties which may result from its use.
 * No license is granted by implication or otherwise under any patent or
 * patent rights of the copyright holder.
 *
 * @file       rt3020.h
 * @date       13 Jun 2019
 * @version    0.0.1
 * @brief
 *
 */
/*! @file rt3020.h */
/*!
 * @defgroup RT3020 SENSOR API
 * @{
 */

#ifndef RT3020_H__
#define RT3020_H__
/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************************/
/* header files */

#include "rt3020_defs.h"
/*********************************************************************/
/* (extern) variable declarations */
/*********************************************************************/
/* function prototype declarations */
/*!
 * @brief This API is the entry point, Call this API before using other APIs.
 * This API reads the chip-id of the sensor which is the first step to
 * verify the sensor and also it configures the read mechanism of SPI and
 * I2C interface.
 *
 * @param[in,out] dev : Structure instance of rt3020_dev
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_init(struct rt3020_dev *dev);

/*!
 * @brief This API writes the given data to the register address
 * of the sensor.
 *
 * @param[in] reg_addr : Register address from where the data to be written.
 * @param[in] reg_data : Pointer to data buffer which is to be written
 *                       in the reg_addr of sensor.
 * @param[in] len      : No of bytes of data to write..
 * @param[in] dev      : Structure instance of rt3020_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_set_regs(uint8_t reg_addr, uint8_t *reg_data, uint8_t len, const struct rt3020_dev *dev);

/*!
 * @brief This API reads the data from the given register address of sensor.
 *
 * @param[in] reg_addr  : Register address from where the data to be read
 * @param[out] reg_data : Pointer to data buffer to store the read data.
 * @param[in] len       : No of bytes of data to be read.
 * @param[in] dev       : Structure instance of rt3020_dev.
 *
 * @note For most of the registers auto address increment applies, with the
 * exception of a few special registers, which trap the address. For e.g.,
 * Register address - 0x14(RT3020_FIFO_DATA_ADDR)
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_get_regs(uint8_t reg_addr, uint8_t *reg_data, uint8_t len, const struct rt3020_dev *dev);

/*!
 * @brief This API is used to perform soft-reset of the sensor
 * where all the registers are reset to their default values except 0x4B.
 *
 * @param[in] dev       : Structure instance of rt3020_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_soft_reset(const struct rt3020_dev *dev);

/*!
 * @brief This API is used to set the power mode of the sensor.
 *
 * @param[in] power_mode  : Macro to select power mode of the sensor.
 * @param[in] dev         : Structure instance of rt3020_dev.
 *
 * Possible value for power_mode :
 *   - RT3020_NORMAL_MODE
 *   - RT3020_SLEEP_MODE
 *   - RT3020_LOW_POWER_MODE
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_set_power_mode(uint8_t power_mode, const struct rt3020_dev *dev);

/*!
 * @brief This API is used to get the power mode of the sensor
 *
 * @param[out] power_mode  : power mode of the sensor.
 * @param[in] dev          : Structure instance of rt3020_dev.
 *
 * * Possible value for power_mode :
 *   - RT3020_NORMAL_MODE
 *   - RT3020_SLEEP_MODE
 *   - RT3020_LOW_POWER_MODE
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_get_power_mode(uint8_t *power_mode, const struct rt3020_dev *dev);

/*!
 * @brief This API is used to get the accel data along with the sensor-time
 *
 * @param[in,out] accel    : Structure instance to store data
 * @param[in] dev          : Structure instance of rt3020_dev
 *
 *
 * @note : The Accel data value are in LSB based on the range selected
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_get_accel_data(struct rt3020_sensor_data *accel, const struct rt3020_dev *dev);

/*!
 * @brief This API is used to set the sensor settings like sensor
 * configurations and interrupt configurations like
 *    - Accelerometer configurations (Like ODR,OSR,range...)
 *    - Tap configurations
 *    - Activity change configurations
 *    - Gen1/Gen2 configurations
 *    - Orient change configurations
 *    - Step counter configurations
 *
 * @param[in] conf         : Structure instance of the configuration structure
 * @param[in] n_sett       : Number of settings to be set
 * @param[in] dev          : Structure instance of rt3020_dev
 *
 * @note : Fill in the value of the required configurations in the conf structure
 * (Examples are mentioned in the readme.md) before calling this API
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_set_sensor_conf(const struct rt3020_sensor_conf *conf, uint16_t n_sett, const struct rt3020_dev *dev);

/*!
 * @brief This API is used to get the sensor settings like sensor
 * configurations and interrupt configurations and store
 * them in the corresponding structure instance
 *
 * @param[in] conf         : Structure instance of the configuration structure
 * @param[in] n_sett       : Number of settings to be obtained
 * @param[in] dev          : Structure instance of rt3020_dev.
 *
 * @note : Call the API and the settings structure will be updated with the
 * sensor settings
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_get_sensor_conf(struct rt3020_sensor_conf *conf, uint16_t n_sett, const struct rt3020_dev *dev);

/*!
 * @brief This API is used to set the device specific settings like
 *  - RT3020_AUTOWAKEUP_TIMEOUT
 *  - RT3020_AUTOWAKEUP_INT
 *  - RT3020_AUTO_LOW_POWER
 *  - RT3020_INT_PIN_CONF
 *  - RT3020_INT_OVERRUN_CONF
 *  - RT3020_FIFO_CONF
 *
 * @param[in] conf         : Structure instance of the configuration structure.
 * @param[in] n_sett       : Number of settings to be set
 * @param[in] dev          : Structure instance of rt3020_dev.
 *
 * @note : Fill in the value of the required configurations in the conf structure
 * (Examples are mentioned in the readme.md) before calling this API
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_set_device_conf(const struct rt3020_device_conf *conf, uint8_t n_sett, const struct rt3020_dev *dev);

/*!
 * @brief This API is used to get the device specific settings and store
 * them in the corresponding structure instance
 *
 * @param[in] conf         : Structure instance of the configuration structure
 * @param[in] n_sett       : Number of settings to be obtained
 * @param[in] dev          : Structure instance of rt3020_dev.
 *
 * @note : Call the API and the settings structure will be updated with the
 * sensor settings
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t rt3020_get_device_conf(struct rt3020_device_conf *conf, uint8_t n_sett, const struct rt3020_dev *dev);

#ifdef __cplusplus
}
#endif  /* End of CPP guard */

#endif  /* RT3020_H__ */
/** @}*/
