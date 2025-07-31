#include "main.h"

#include <stdio.h> 

extern I2C_HandleTypeDef hi2c1;

extern int8_t i2c_tx_buf[4];
uint8_t i2c_rx_buf[1] = {0};

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
  printf("I2C Address matched: %02X\r\n", AddrMatchCode);

  if (TransferDirection == I2C_DIRECTION_RECEIVE) {
    printf("Read from master\r\n");
    HAL_I2C_Slave_Seq_Transmit_IT(hi2c, i2c_tx_buf, sizeof(i2c_tx_buf), I2C_LAST_FRAME);
  } else{
    printf("Write from master\r\n");
    HAL_I2C_Slave_Seq_Receive_IT(hi2c, i2c_rx_buf, sizeof(i2c_rx_buf), I2C_FIRST_AND_LAST_FRAME);
  }
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
  printf("%d\r\n", i2c_rx_buf[0]);
}

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c){
  HAL_I2C_EnableListen_IT(&hi2c1);
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c){
  HAL_I2C_EnableListen_IT(&hi2c1);
}