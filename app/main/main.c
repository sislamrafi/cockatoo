#include "main.h"


#define ON_BORD_LED 0x05U

#define PWM_PIN 0x05U

ESC motorFL = { GPIOA,0x05U,CHANNEL1 };


int main(void) {
  rcc_config_HSE8MHz_SYS180MHz();
  ConfigTimer2ForSystem();
  ESC_ConfigWithTimer2();

  configUSART(USART2, USART2_PIN_A3_A2, 115200);

  //GPIO_ENABLE(GPIOA);
  //pinConfig(GPIOA, ON_BORD_LED, GPIO_OUTPUT);

  // ESC_Attach(&motorFL);

  MPU6050_Init();

  while (1) {
    /* code */
    // digitalWrite(GPIOA, ON_BORD_LED, GPIO_PIN_HIGH);
    // __digitalWriteDebugButton(ON_BORD_LED,GPIO_PIN_HIGH);
    // Delay(2000);
    // digitalWrite(GPIOA, ON_BORD_LED, GPIO_PIN_LOW);
    // __digitalWriteDebugButton(ON_BORD_LED,GPIO_PIN_LOW);
    // Delay(2000);
    //setTimer2PWMDutyCycle( 1000+(1000*__alalogReadDebug()/0xFFFF) );
    // ESC_write(&motorFL, (1000 + (1000 * __alalogReadDebug() / 0xFFFF)));
  }
}

void SYS_ROUTINE(void) {
  __debugRamUsage();
}