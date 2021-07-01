#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/timer.h>

#include "hal_utils.h"

void enable_clock(void)
{
  /* Enable GPIOD clock for LED & USARTs. */
  rcc_periph_clock_enable(RCC_GPIOD);
  rcc_periph_clock_enable(RCC_GPIOA);
  /* Enable clocks for USART2. */
  rcc_periph_clock_enable(RCC_USART2);
}

void enable_gpios(void)
{
  /* Setup GPIO pin GPIO12 on GPIO port D for LED. */
  gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
  /* Setup GPIO pins for USART2 transmit. */
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
  /* Setup USART2 TX pin as alternate function. */
  gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
  
  /* Setup GPIO pin GPIO12 on GPIO port D for LED. */
  gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO12);
  /* Setup GPIO pins for USART2 transmit. */
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
  /* Setup USART2 TX pin as alternate function. */
  gpio_set_af(GPIOA, GPIO_AF7, GPIO2);
}

void enable_delay(void)
{
  /* set up a microsecond free running timer for ... things... */
  rcc_periph_clock_enable(RCC_TIM6);
  /* microsecond counter */
  timer_set_prescaler(TIM6, rcc_apb1_frequency / 1000000 - 1);
  timer_set_period(TIM6, 0xffff);
  timer_one_shot_mode(TIM6);
}

void delay_ms(int ms)
{
  TIM_ARR(TIM6) = ms;
  TIM_EGR(TIM6) = TIM_EGR_UG;
  TIM_CR1(TIM6) |= TIM_CR1_CEN;
  while(TIM_CR1(TIM6) & TIM_CR1_CEN);
}

void enable_uart(void)
{
  /* Setup USART2 parameters. */
  usart_set_baudrate(USART2, 115200);
  usart_set_databits(USART2, 8);
  usart_set_stopbits(USART2, USART_STOPBITS_1);
  usart_set_mode(USART2, USART_MODE_TX);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
  /* Finally enable the USART. */
  usart_enable(USART2);
}

int _write(int file, char *ptr, int len)
{
  int i;

  if(file == STDOUT_FILENO || file == STDERR_FILENO)
  {
    for(i = 0; i < len; i++)
    {
      if(ptr[i] == '\n')
      {
        usart_send_blocking(USART2, '\r');
      }
      usart_send_blocking(USART2, ptr[i]);
    }
    return i;
  }
  errno = EIO;
  return -1;
}
