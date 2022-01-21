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
typedef struct _FrMeter_t
{
  uint16_t Counter;
  uint8_t ConfigIndex;
  uint8_t OutOfRange;

}FrMeter_t;

typedef struct _FrConfig_t
{
  uint16_t TimbasePrescaler;
  uint16_t TimebaseMs;

}FrConfig_t;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern TIM_HandleTypeDef hCounter;
extern TIM_HandleTypeDef hTimebase;

FrMeter_t *FrMeterInit(void);
void FrMeterStart(void);


#endif /* SRC_FREQMETER_H_ */

/************************ (C) COPYRIGHT KonvolucioBt ***********END OF FILE****/
