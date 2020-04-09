# BMP280 SPI-type STM32F030 
<<<<<<< HEAD
Bosch sensor on SPI bus driving by STM32F030F4

Slight precaution!

The original bug or feature of STM32F0 series concerns SPI bus. When 8-bit width data bus is expected, it has to send 8-bit data into SPI bus as well. Unfortunately, an MC can not recognize 8-bit or 16-bit data had been sent. Although, when assembler is used , there is no problem or the problem has to be solved by using STRB command. like this:

STRB trPacket, [tmpa, #SPI1_DR_Offset]

Whereas on C or C++, the peripheral register has to be cast like this:

(__IO uint8_t)&SPI1->DR = buf[0];
=======
 Bosch sensor on SPI bus driving by STM32F030F4
 
 
Slight precaution!


The original bug or feature of STM32F0 series concerns SPI bus. When 8-bit width data bus is expected, it has to send 8-bit data into SPI bus as well. Unfortunately, an MC can not recognize 8-bit or 16-bit data had been sent. Although, when assembler is used , there is no problem or the problem has to be solved by using STRB command. like this:

STRB trPacket, [tmpa, #SPI1_DR_Offset]
 
  

Whereas on C or C++, the peripheral register has to be cast like this:

*(__IO uint8_t*)&SPI1->DR = buf[0];
>>>>>>> 2b84840758e1fe76f15c8bc25c648bffaec166f9
