/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

CAN_TxHeaderTypeDef txHeader;
uint8_t txData[8]={1,1,1,1,0,0,0,0};
uint32_t txMailbox;
CAN_RxHeaderTypeDef rxHeader;
CAN_FilterTypeDef  sFilterConfig; // Rx filtering config
CAN_FilterTypeDef  can2FilterConfig;
uint8_t rxData[8];

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 21;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_14TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_5TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
  sFilterConfig.FilterBank = 0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;              // 0x00000000 = 모든 ID
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterActivation = ENABLE;
 // sFilterConfig.SlaveStartFilterBank = 14;
  if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE END CAN1_Init 2 */

}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 21;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_14TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_5TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */
//  can2FilterConfig.FilterBank = 0;
//  can2FilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
//  can2FilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
//  can2FilterConfig.FilterIdHigh = 0x0000;
//  can2FilterConfig.FilterIdLow = 0x0000;
//  can2FilterConfig.FilterMaskIdHigh = 0x0000;              // 0x00000000 = 모든 ID�??? 받아?��?��겠다
//  can2FilterConfig.FilterMaskIdLow = 0x0000;
//  can2FilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
//  can2FilterConfig.FilterActivation = ENABLE;
//  can2FilterConfig.SlaveStartFilterBank = 14;
//  if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
  /* USER CODE END CAN2_Init 2 */

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
//HAL_CAN_ERROR_RX_FOV

void can_test(void)
{


//	if(HAL_CAN_Start(&hcan1) != HAL_OK)
//	{
//		      Error_Handler();
//	}

    txHeader.StdId = 0x102;                 // Standard Identifier, 0 ~ 0x7FF
    txHeader.ExtId = 0x01;                  // Extended Identifier, 0 ~ 0x1FFFFFFF
    txHeader.RTR = CAN_RTR_DATA;            // trans message frame type, DATA or REMOTE
    txHeader.IDE = CAN_ID_STD;              // trans message identifi type, STD or EXT
    txHeader.DLC = 8;                       // trans Frame length, 0 ~ 8 byte
    txHeader.TransmitGlobalTime = ENABLE;  // trans frame time stamp counter value capture.

	txMailbox = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);
	HAL_CAN_AddTxMessage(&hcan1, &txHeader, txData, &txMailbox);
	while(HAL_CAN_IsTxMessagePending(&hcan1, txMailbox)){}
	while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) != 3) {}

		uint8_t can_data[100]={0, };
	    sprintf(&can_data,"\r\n CAN TX data : %d%d%d%d%d%d%d%d \r\n",
	    		txData[0],txData[1],txData[2],txData[3],txData[4],txData[5],txData[6],txData[7]);
	    HAL_UART_Transmit(&huart1, can_data, strlen(can_data), 0xFF);


//	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);



}

void can_rxrx(void)
{
	HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rxHeader, rxData);
	uint8_t nu_data[100]={0, };
    sprintf(&nu_data,"\r\n can normal RX data : %d%d%d%d%d%d%d%d \r\n",
    		rxData[0],rxData[1],rxData[2],rxData[3],rxData[4],rxData[5],rxData[6],rxData[7]);
    HAL_UART_Transmit(&huart1, nu_data, strlen((char *)nu_data), 0xFF);

}
/* USER CODE END 1 */
