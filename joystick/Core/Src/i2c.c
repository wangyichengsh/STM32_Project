#include "main.h"

#include <stdio.h> 

extern I2C_HandleTypeDef hi2c1;

extern uint8_t i2c_tx_buf[4];
uint8_t i2c_rx_buf[1] = {0};
uint8_t send_data = 0;

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
  if (TransferDirection == I2C_DIRECTION_RECEIVE) {
    HAL_I2C_Slave_Seq_Transmit_IT(hi2c, i2c_tx_buf, sizeof(i2c_tx_buf), I2C_FIRST_AND_LAST_FRAME);
  } else{
    HAL_I2C_Slave_Seq_Receive_IT(hi2c, i2c_rx_buf, sizeof(i2c_rx_buf), I2C_FIRST_FRAME);
  }
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
  printf("%d\r\n", i2c_rx_buf[0]);
  if(i2c_rx_buf[0]<4 && i2c_rx_buf[0]>=0){
    send_data = i2c_tx_buf[i2c_rx_buf[0]];
  }
  HAL_I2C_Slave_Seq_Transmit_IT(hi2c, &send_data, 1, I2C_LAST_FRAME);
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c){
  if(HAL_I2C_GetState(hi2c)!=  HAL_I2C_STATE_LISTEN  ){
    HAL_I2C_EnableListen_IT(&hi2c1);
  }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c){
  uint32_t err = HAL_I2C_GetError(hi2c);
  printf("err:%lu\r\n", err);
  if(HAL_I2C_GetState(hi2c)!=  HAL_I2C_STATE_LISTEN  ){
    HAL_I2C_EnableListen_IT(&hi2c1);
  }
}