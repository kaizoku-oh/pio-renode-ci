#include "main.h"
#include "stm32f4_discovery.h"

void On_Receive_Byte(uint8_t u08RxByte);

#define RX_BUFFER_SIZE 64

uint8_t tu08RxBuffer[RX_BUFFER_SIZE];
uint8_t u08RxIndex;

int main(void)
{
  HAL_Init();
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
  BSP_USART_Init();
  BSP_USART_Register_Callback((void *)On_Receive_Byte);

  BSP_USART_Write((uint8_t *)"App started!\r\n", (sizeof("App started!\r\n")-1));
  while(1)
  {
    HAL_Delay(1000);
  }
}

void On_Receive_Byte(uint8_t u08RxByte)
{
  if(RX_BUFFER_SIZE == u08RxIndex)
  {
    u08RxIndex = 0;
  }
  tu08RxBuffer[u08RxIndex++] = u08RxByte;
}

void HAL_GPIO_EXTI_Callback(uint16_t u16Pin)
{
  if(KEY_BUTTON_PIN == u16Pin)
  {
    BSP_USART_Write((uint8_t *)"button pressed", (sizeof("button pressed")-1));
  }
}

void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

void HardFault_Handler(void)
{
  while(1)
  {}
}
