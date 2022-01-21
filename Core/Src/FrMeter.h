/*
 * FreqMeter.h
 *
 *  Created on: Jan 21, 2022
 *      Author: Margit Robert
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SRC_FREQMETER_H_
#define SRC_FREQMETER_H_
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
/* Exported types ------------------------------------------------------------*/
typedef struct _FrConfig_t
{
  uint16_t TimebasePrescaler;
  uint16_t TimebaseAutoReload;
  uint16_t Multiplier;
}FrConfig_t;


typedef struct _FrMeter_t
{
  uint16_t Counter;
  uint8_t CfgIndex;
  uint8_t OutOfRange;

}FrMeter_t;


/* Exported constants --------------------------------------------------------*/
#define FRMETER_CFG_1S      0
#define FRMETER_CFG_100MS   1
#define FRMETER_CFG_10MS    2
#define FRMETER_CFG_1MS     3

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern TIM_HandleTypeDef hCounter;
extern TIM_HandleTypeDef hTimebase;
extern FrConfig_t FrMeterConfigs[];

FrMeter_t *FrMeterInit(void);
void FrMeterStart(FrMeter_t *context, uint8_t cfgIndex);


#endif /* SRC_FREQMETER_H_ */

/************************ (C) COPYRIGHT KonvolucioBt ***********END OF FILE****/
