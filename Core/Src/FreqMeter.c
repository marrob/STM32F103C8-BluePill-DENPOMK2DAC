/*
 * FreqMeter.c
 *
 *  Created on: Jan 21, 2022
 *      Author: Margit Robert
 */

/* Includes ------------------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/


#define TIM_TIMBASE TIM2
#define TIM_COUNTER TIM1


/* Private macro -------------------------------------------------------------*/
#define TimebaseStart()   __HAL_TIM_ENABLE(&htim2)
#define CoutnerStart()    __HAL_TIM_ENABLE(&htim1)
#define CounterValue      TIM_COUNTER->CNT
#define TimebaseValue     TIM_TIMBASE->CNT
/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* Private function prototypes -----------------------------------------------*/

FreqMeter_t _FreqMeter;

/* Private user code ---------------------------------------------------------*/
FreqMeter_t FreqMeterInit(void)
{
  TimebaseInit();
  CounterInit();

  return _FreqMeter;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
   if(htim->Instance == TIM_TIMBASE)
   {
     _FreqMeter.Counter = CounterValue;
     CounterValue = 0;
     _FreqMeter.OutOfRange = 0;
   }
   else if(htim->Instance == TIM_COUNTER)
   {
     _FreqMeter.OutOfRange = 1;
   }

}


void FreqMeterMeasStart()
{
  CounterValue = 0;
  TimebaseValue = 0;
  __HAL_TIM_ENABLE_IT(&TIM_TIMBASE, TIM_IT_UPDATE);
  TimebaseStart();
  CoutnerStart();
}


void TimebaseInit(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

void CounterInit(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};


  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_ETRMODE2;
  sClockSourceConfig.ClockPolarity = TIM_CLOCKPOLARITY_NONINVERTED;
  sClockSourceConfig.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
  sClockSourceConfig.ClockFilter = 0;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}




/************************ (C) COPYRIGHT KonvolucioBt ***********END OF FILE****/
