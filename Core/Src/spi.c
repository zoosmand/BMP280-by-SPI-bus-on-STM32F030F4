/**
  ******************************************************************************
  * File Name          : spi.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "spi.h"









////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  SPI1 Initialization procedure
  * @param  none
  * @retval none
  */
void SPI1_Init(void) {
  /* Enable GPIO alternative #0 on hight speed */
  SPI_Port->MODER   |= ((_AF << (SCK_Pin_Pos * 2U)) | (_AF << (MISO_Pin_Pos * 2U)) | (_AF << (MOSI_Pin_Pos * 2U)));
  SPI_Port->OSPEEDR |= ((_HS << (SCK_Pin_Pos * 2U)) | (_HS << (MISO_Pin_Pos * 2U)) | (_HS << (MOSI_Pin_Pos * 2U)));

  /* Enable GPIO output for NSS on lowest speed */
  SPI_Port->MODER     |= (_PU << (NSS_0_Pin_Pos * 2U));
  NSS_0_H;

  /* Set fractal part for 8-bit mode */
  /* Enable software output */
  /* Data size is automaticaly set by 8-bit bus */
  SET_BIT(SPI1->CR2, (SPI_CR2_FRXTH | SPI_CR2_SSOE));

  /* Set software NSS master */
  /* Set baud rate fPCLK/4, 12Mb/s */
  /* Enbale master SPI */
  /* Enbale SPI */
  SET_BIT(SPI1->CR1, (SPI_CR1_SSM | SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_MSTR | SPI_CR1_SPE));
}






/**
  * @brief  SPI1 enabling procedure
  * @param  none
  * @retval none
  */
void SPI1_Enable() {
  SET_BIT(SPI1->CR1, SPI_CR1_SPE);
}





/**
  * @brief  SPI1 disabling procedure
  * @param  none
  * @retval none
  */
void SPI1_Disable() {
  while (READ_BIT(SPI1->SR, SPI_SR_FTLVL) == SPI_SR_FTLVL);
  while (READ_BIT(SPI1->SR, SPI_SR_BSY));
  CLEAR_BIT(SPI1->CR1, SPI_CR1_SPE);
  while (READ_BIT(SPI1->SR, SPI_SR_FTLVL) == SPI_SR_FTLVL);
}






/**
  * @brief  Reads data from SPI bus
  * @param  buf: pointer to buffer to read, the first item of buffer could contain
  *              a command data. Beginning iteration reads a dummy byte.
  *         cnt: count of bytes to read.
  * @retval none
  */
void SPI_Read(uint8_t *buf, uint8_t cnt) {
  // SPI1_Enable();
  NSS_0_L;
  while (PIN_LEVEL(SPI_Port, NSS_0_Pin));

  *(__IO uint8_t*)&SPI1->DR = buf[0];
  while (!(READ_BIT(SPI1->SR, SPI_SR_TXE)));
  while (READ_BIT(SPI1->SR, SPI_SR_RXNE)) {
    SPI1->DR;
  }
  
  // !!!!!!!!!!!
  cnt +=3;

  while (cnt--) {
    *(__IO uint8_t*)&SPI1->DR = 0;
    while (!(READ_BIT(SPI1->SR, SPI_SR_TXE)));
    while (READ_BIT(SPI1->SR, SPI_SR_RXNE)) {
      *buf++ = (uint8_t)SPI1->DR;
    }
  }
    
  NSS_0_H;
  // SPI1_Disable();
}






/**
  * @brief  Writes data into SPI bus
  * @param  buf: pointer to buffer to write.
  *         cnt: count of bytes to write.
  * @retval none
  */
void SPI_Write(uint8_t *buf, uint8_t cnt) {
  NSS_0_L;
  while (PIN_LEVEL(SPI_Port, NSS_0_Pin));

  cnt += 3;

  if (cnt) {
    while (cnt--) {
      *(__IO uint8_t*)&SPI1->DR = *buf++;
      while (!(READ_BIT(SPI1->SR, SPI_SR_TXE)));
      while (READ_BIT(SPI1->SR, SPI_SR_RXNE)) {
        SPI1->DR;
      }
    }
  }
    
  NSS_0_H;
}