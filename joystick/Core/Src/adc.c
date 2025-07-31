#include "main.h"

extern uint16_t adc_value[2];
extern int8_t i2c_tx_buf[4];

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    // Update TX buffer with fresh data (assuming 12-bit ADC)
    i2c_tx_buf[0] = adc_value[0] & 0xFF;
    i2c_tx_buf[1] = adc_value[0] >> 8;
    i2c_tx_buf[2] = adc_value[1] & 0xFF;
    i2c_tx_buf[3] = adc_value[1] >> 8;
}

