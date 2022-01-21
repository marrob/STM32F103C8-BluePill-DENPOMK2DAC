/*
 * FreqMeter.c
 *
 *  Created on: Jan 21, 2022
 *      Author: Margit Robert
 */

/* Includes ------------------------------------------------------------------*/
#include "FreqMeter.h"
/* Private define ------------------------------------------------------------*/

#define TIM_TIMBASE TIM2
#define TIM_COUNTER TIM1

/* Private macro -------------------------------------------------------------*/
#define TimebaseStart()   __HAL_TIM_ENABLE(&hTimebase)
#define CoutnerStart()    __HAL_TIM_ENABLE(&hCounter)
#define CounterValue      TIM_COUNTER->CNT
#define TimebaseValue     TIM_TIMBASE->CNT
/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef hCounter;
TIM_HandleTypeDef hTimebase;
FreqMeter_t _freqMeter;


/* Private function prototypes -----------------------------------------------*/
void TimebaseInit(void);
void CounterInit(void);



/* Private user code ---------------------------------------------------------*/
FreqMeter_t *FreqMeterInit(void)
{
  TimebaseInit();
  CounterInit();
  return &_freqMeter;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
   if(htim->Instance == TIM_TIMBASE)
   {
     _freqMeter.Counter = CounterValue;
     CounterValue = 0;
     _freqMeter.OutOfRange = 0;
   }
   else if(htim->Instance == TIM_COUNTER)
   {
     _freqMeter.OutOfRange = 1;
   }
}


void FreqMeterMeasStart()
{
  CounterValue = 0;
  TimebaseValue = 0;
  __HAL_TIM_ENABLE_IT(&hTimebase, TIM_IT_UPDATE);
  TimebaseStart();
  CoutnerStart();
}


void TimebaseInit(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  hTimebase.Instance = TIM2;
  hTimebase.Init.Prescaler = 0;
  hTimebase.Init.CounterMode = TIM_COUNTERMODE_UP;
  hTimebase.Init.Period = 65535;
  hTimebase.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  hTimebase.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&hTimebase) != HAL_OK)
  {
   // Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&hTimebase, &sClockSourceConfig) != HAL_OK)
  {
    //Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&hTimebase, &sMasterConfig) != HAL_OK)
  {
   // Error_Handler();
  }
}

void CounterInit(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};


  hCounter.Instance = TIM1;
  hCounter.Init.Prescaler = 0;
  hCounter.Init.CounterMode = TIM_COUNTERMODE_UP;
  hCounter.Init.Period = 65535;
  hCounter.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  hCounter.Init.RepetitionCounter = 0;
  hCounter.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&hCounter) != HAL_OK)
  {
    //Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_ETRMODE2;
  sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_NONINVERTED;
  sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
  sClockSourceConfig.ClockFilter = 0;
  if (HAL_TIM_ConfigClockSource(&hCounter, &sClockSourceConfig) != HAL_OK)
  {
   // Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&hCounter, &sMasterConfig) != HAL_OK)
  {
   // Error_Handler();
  }
}


/**
* @brief TIM_Base MSP Initialization
* This function configures the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(htim_base->Instance==TIM1)
  {
    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
    HAL_NVIC_SetPriority(TIM1_CC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
  }
  else if(htim_base->Instance==TIM2)
  {
    __HAL_RCC_TIM2_CLK_ENABLE();
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM1)
  {
    __HAL_RCC_TIM1_CLK_DISABLE();
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12);
    HAL_NVIC_DisableIRQ(TIM1_UP_IRQn);
    HAL_NVIC_DisableIRQ(TIM1_CC_IRQn);
  }
  else if(htim_base->Instance==TIM2)
  {
    __HAL_RCC_TIM2_CLK_DISABLE();
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  }

}




/************************ (C) COPYRIGHT KonvolucioBt ***********END OF FILE****/
