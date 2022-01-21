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

void FreqMeterInit(void);



#endif /* SRC_FREQMETER_H_ */

/************************ (C) COPYRIGHT KonvolucioBt ***********END OF FILE****/
