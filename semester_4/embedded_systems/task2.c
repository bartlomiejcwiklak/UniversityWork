// 8 Red LEDs
// DCMI_D0 -> PC6
// DCMI_D1 -> PC7
// DCMI_D2 -> PC8
// DCMI_D3 -> PC9
// DCMI_D4 -> PE4
// DCMI_D5 -> PD3
// DCMI_D6 -> PE5
// DCMI_D7 -> PE6

// Joystick
// JOY_RT -> PE0
// JOY_LT -> PE1
// JOY_DN -> PE2
// JOY_UP -> PE3
// JOY_OK -> PE15

// RGB LED
// TIM4_CH1 (R) -> PD12
// TIM4_CH2 (G) -> PD13
// TIM4_CH3 (B) -> PB8

#include "main.h"

#define BLINKING_SPEED 300 // how many milliseconds should one light be lit

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  typedef struct {
      GPIO_TypeDef* port;
      uint16_t pin;
  } LED;

  const LED leds[8] = {
      {GPIOC, GPIO_PIN_6},
      {GPIOC, GPIO_PIN_7},
      {GPIOC, GPIO_PIN_8},
      {GPIOC, GPIO_PIN_9},
      {GPIOE, GPIO_PIN_4},
      {GPIOD, GPIO_PIN_3},
      {GPIOE, GPIO_PIN_5},
      {GPIOE, GPIO_PIN_6}
  };

  uint32_t lastTick = HAL_GetTick();
  int currentLED = 0;
  int direction = 1; // 1: 0->7, -1: 7->0

  while (1)
  {
	  uint32_t currentTick = HAL_GetTick();

	  // Scrolling, blinking RED light:

	  if (currentTick - lastTick >= BLINKING_SPEED){
		  lastTick = currentTick;
		  HAL_GPIO_WritePin(leds[currentLED].port, leds[currentLED].pin, GPIO_PIN_RESET);
		  currentLED += direction;
	  }

	  if (currentLED >= 7) {
		  currentLED = 7;
		  direction = -1;
	  } else if (currentLED <= 0) {
		  currentLED = 0;
		  direction = 1;
	  }

	  HAL_GPIO_WritePin(leds[currentLED].port, leds[currentLED].pin, GPIO_PIN_SET);

	  // Joystick:

	  if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_15) == GPIO_PIN_RESET){
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	  } else {
          if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1) == GPIO_PIN_RESET)
              HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
          else
              HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);

          if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2) == GPIO_PIN_RESET)
              HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
          else
              HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

          if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0) == GPIO_PIN_RESET)
              HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
          else
              HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
      }

  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  // 8 LEDs

  GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  // Joystick

  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  // RGB Led

  GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_8;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}


void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}
#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
