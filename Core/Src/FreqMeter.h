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
typedef struct _FreqMeter_t
{
  uint16_t Counter;
  uint8_t ConfigIndex;
  uint8_t OutOfRange;

}FreqMeter_t;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

extern TIM_HandleTypeDef hCounter;
extern TIM_HandleTypeDef hTimebase;

FreqMeter_t *FreqMeterInit(void);



#endif /* SRC_FREQMETER_H_ */

/************************ (C) COPYRIGHT KonvolucioBt ***********END OF FILE****/
