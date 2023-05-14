#include "esc.h"

#include "esc.h"

// write your functions here

//TIM1_CH1N = {PA7,PB13,}
//TIM1_CH2N = {PB0,PB14,}
//TIM1_CH3N = {PB1,PB15,}

//TIM1_CH1 = {PA8, ,}
//TIM1_CH2 = {PA9, ,}
//TIM1_CH3 = {PA10,,}
//TIM1_CH4 = {PA11,,}

//TIM2_CH1 = {PA0,PA5,PB8,PB13}
//TIM2_CH2 = {PA1,PB2,PB9,PB14}
//TIM2_CH3 = {PA2,PB10,PB15}
//TIM2_CH4 = {PA3,PB2,PB11}

void ESC_ConfigWithTimer2(void) {

  //check if timer is enable;
  if (!(RCC->APB1ENR&0b1)){
    ConfigTimer2ForSystem();
  }

  //following are configured in timer.h
  //RCC->APB2ENR |= (1 << 0);
  //TIM2->PSC = 90 - 1;
  //TIM2->ARR = 100;
  //TIM2->CR1 |= (1 << 0); // enable counter

  TIM2->CCR1 = 0;
  TIM2->EGR |= (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4); // enable capture compare generation for channel 1,2,3,4
  
  TIM2->CCMR1 &= ~(0b11 << 0); // chanel 1 output mode
  TIM2->CCMR1 |= (0b110 << 4); // chanel 1 pwm mode 1
  TIM2->CCMR1 |= (1 << 3);     // Output compare 1 preload enable

  TIM2->CCMR1 &= ~(0b11 << 8); // chanel 2 output mode
  TIM2->CCMR1 |= (0b110 << 12); // chanel 2 pwm mode 1
  TIM2->CCMR1 |= (1 << 11);     // Output compare 2 preload enable

  TIM2->CCMR2 &= ~(0b11 << 0); // chanel 3 output mode
  TIM2->CCMR2 |= (0b110 << 4); // chanel 3 pwm mode 1
  TIM2->CCMR2 |= (1 << 3);     // Output compare 3 preload enable

  TIM2->CCMR2 &= ~(0b11 << 8); // chanel 4 output mode
  TIM2->CCMR2 |= (0b110 << 12); // chanel 4 pwm mode 1
  TIM2->CCMR2 |= (1 << 11);     // Output compare 4 preload enable


  TIM2->CR1 |= (1<<7); //Enable control pre-loader

  TIM2->CCER |= (1<<0);// chanel 1 output enable
  TIM2->CCER |= (1<<4);// chanel 2 output enable
  TIM2->CCER |= (1<<8);// chanel 3 output enable
  TIM2->CCER |= (1<<12);// chanel 4 output enable

  TIM2->BDTR |= (1<<14);//AUTO SELECT

  // Re-initialize the counter and generates an update of the registers.
  TIM2->EGR = 1 << 0;//UG bit 1
}

void setTimer2PWMDutyCycle(uint16_t duty){
  TIM2->CCR1 = duty;
}
