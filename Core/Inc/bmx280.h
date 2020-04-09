/**
  ******************************************************************************
  * File Name          : bmx280.h
  * Description        : This file provides code for the BMx280 Bosch family
  *                      pressure, humidity and temperature sensors.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#ifndef _BMX280_H
#define _BMX280_H

#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif


typedef struct {
  uint8_t   ID;
  uint8_t   ManID;
  uint8_t   Type;
  uint64_t  UniqID;
  uint16_t  BlockCount;
  uint32_t  Capacity;
  uint8_t   Lock;	
} bmx280_t;


/* Private defines -----------------------------------------------------------*/
/* BMx280 registers */
#define SensorID              0xd0
#define Calib1                0x88
#define Calib2                0xe1
#define CollectData           0xf7
#define ConfigSensor          0xf5
#define CtrlMeasure           0xf4
#define StatusSensor          0xf3
#define CtrlHumidity          0xf2
#define ReserSensor           0xe0
/* Definitions for Status register */
#define Measuring             0x08
#define Measuring_Pos         3
#define ImUpdate              0x00
#define ImUpdate_Pos          0
/* Definitions for Control Measuring register */
#define TemperatureOvsMask    0xe0
#define TemperatureOvs_Pos    5
#define PressureOvsMask       0x1c 
#define PressureOvs_Pos       2 
#define ModeMask              0x03
#define Mode_Pos              0
#define SleepMode             0x00
#define ForceMode             0x01
#define NormalMode            0x03
/* Some other definitions */
#define WriteMask             0x7f
#define ResetValue            0xb6
#define BMP280_ID             0x58
#define BME280_ID             0x60
/* Types demanded by BMx280 datasheet */
typedef int32_t               BMP280_S32_t;
typedef uint32_t              BMP280_U32_t;


/* Exported functions prototypes ---------------------------------------------*/
uint8_t BMP280_Init(void);
BMP280_S32_t* BMP280_ReadT(void);
BMP280_U32_t* BMP280_ReadP(void);
double* BMP280_ReadTP(void);
double* BMP280_ReadPP(void);


#ifdef __cplusplus
}
#endif
#endif /* _BMX280_H */

