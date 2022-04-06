/*
******************************************************************************
File:     main.c
Info:     Generated by Atollic TrueSTUDIO(R) 9.3.0   2022-04-06

The MIT License (MIT)
Copyright (c) 2019 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Includes */
#include "stm32f0xx.h"

void TIM6_DAC_IRQHandler(void) {
	TIM6->SR &= ~TIM_SR_UIF;

	blinkLed8();
}

void init_gpio() {
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;	//turn on clock pulse
	GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;	//init gpio
}

void blinkLed8() {
	GPIOC->ODR ^= GPIO_ODR_8;
}

void blinkLed9() {
	if (TIM6->CNT > 4000) {
		GPIOC->BSRR = GPIO_BSRR_BR_9;
		return;
	}

	GPIOC->BSRR = GPIO_BSRR_BS_9;
}

void init_tim6() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

	TIM6->ARR = 8000 - 1;
	TIM6->PSC = 500 - 1;

	TIM6->DIER |= TIM_DIER_UIE;

	NVIC_SetPriority(TIM6_DAC_IRQn, 8);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	TIM6->CR1 |= TIM_CR1_CEN;
}

int main(void)
{
	init_gpio();
	init_tim6();
	while (1)
	{
		blinkLed9();
	}
}
