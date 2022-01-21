/*
 * FreqMeter.c
 *
 *  Created on: Jan 21, 2022
 *      Author: Margit Robert
 */

/* Includes ------------------------------------------------------------------*/
#include "FrMeter.h"
#include "main.h"
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
FrMeter_t _frMeter;

FrConfig_t FrMeterConfigs[] =
{
    {800, 60000, 1},
    {80, 60000, 10},
    {8, 53400, 100},
    {1, 48000, 1000}
};



/* Private function prototypes -----------------------------------------------*/
static void TimebaseInit(void);
static void CounterInit(void);



/* Private user code ---------------------------------------------------------*/
FrMeter_t *FrMeterInit(void)
{
  TimebaseInit();
  CounterInit();
  return &_frMeter;
}

void FrMeterStart(FrMeter_t *context, uint8_t cfgIndex)
{
  context->CfgIndex = cfgIndex;
  CounterValue = 0;
  TimebaseValue = 0;

/*
  __HAL_TIM_SET_PRESCALER(&hTimebase, 800);
  __HAL_TIM_SET_AUTORELOAD(&hTimebase, 60000);
*/
  __HAL_TIM_SET_PRESCALER(&hTimebase, FrMeterConfigs[cfgIndex].TimebasePrescaler);
  __HAL_TIM_SET_AUTORELOAD(&hTimebase, FrMeterConfigs[cfgIndex].TimebaseAutoReload);
  __HAL_TIM_ENABLE_IT(&hTimebase, TIM_IT_UPDATE);
  TimebaseStart();
  CoutnerStart();
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
   if(htim->Instance == TIM_TIMBASE)
   {
     _frMeter.Counter = CounterValue;
     CounterValue = 0;
     _frMeter.OutOfRange = 0;
     HAL_GPIO_TogglePin(TIMEBASE_GPIO_Port, TIMEBASE_Pin);
   }
   else if(htim->Instance == TIM_COUNTER)
   {
     _frMeter.OutOfRange = 1;
   }
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
