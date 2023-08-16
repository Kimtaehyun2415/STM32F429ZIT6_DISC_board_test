/*
 * timer_pwm.c
 *
 *  Created on: Jul 14, 2023
 *      Author: user
 */

#include "timer_pwm.h"
#include "stdio.h"
#include "string.h"

extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef huart1;

uint16_t arr=0;
uint16_t pul_count=41999;

void pwm_duty_control(void)
{
   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
   // TIM1->CCR1 = (uint16_t)(41999-(uint16_t)(419.99*50));
   // duty 50% change
   //HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);

   arr++;
   if(arr >= 100)arr=0;
   TIM1->CCR1 = (pul_count-((pul_count/100)*arr));
   HAL_Delay(10);

   uint8_t get_in[100]={0, };
   unsigned char percen = '%';
   sprintf(&get_in, "Duty rate : %d %c \r\n",(100-arr), percen);
   HAL_UART_Transmit(&huart1, get_in, strlen(get_in), 0xff);

}

void pwm_DMA(void)
{
	uint8_t dma_buf[0xff]={0};
	HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, dma_buf, strlen(dma_buf) );


}
