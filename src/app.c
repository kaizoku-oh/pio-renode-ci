#include "hal_utils.h"

int main(void)
{
  int i = 0;

  enable_clock();
  enable_gpios();
  enable_uart();
  enable_delay();

  printf("App STARTED\n");
  while(1)
  {
    printf("Hello world! %d\r\n", i++);
    delay_ms(1000);
  }

  return 0;
}