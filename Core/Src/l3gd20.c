/*
 * l3gd20.c
 *
 *  Created on: 2023. 7. 12.
 *      Author: user
 */


#include "l3gd20.h"


extern SPI_HandleTypeDef hspi5;
extern UART_HandleTypeDef huart1;


uint8_t gyroData_tx[100]={0, };
uint8_t xl_tx[2]={0xA8, }, xl_rx[2]={0, }, xh_tx[2]={0xA9, }, xh_rx[2]={0, },
        yl_tx[2]={0xAA, }, yl_rx[2]={0, }, yh_tx[2]={0xAB, }, yh_rx[2]={0, },
		zl_tx[2]={0xAC, }, zl_rx[2]={0, }, zh_tx[2]={0xAD, }, zh_rx[2]={0, };

uint8_t who_iam_cmd_tx = 0x8F;
uint8_t id_get_tx[2] = {0, };



void l3gd20Init(void)
{
	uint8_t cmd_init_write[2] = {0x20, 0x0F};
	// write CTRL_REG1 to NORMAL MODE
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi5, cmd_init_write, 2, 0xFF);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}

void l3gd20_Start(void) // Gyro Start
{
	uint8_t ms_init_write[2] = {0x28, 0x40};
	uint8_t test_read_init[2] = {0xA8, }, read_buff[2]={0, },

			X_L_Read_INIT[2] = {0xE8, }, X_L_Read_BUF[2]={0, },
			X_H_Read_INIT[2] = {0xA9, }, X_H_Read_BUF[2]={0, },
			Y_L_Read_INIT[2] = {0xAA, }, Y_L_Read_BUF[2]={0, },
			Y_H_Read_INIT[2] = {0xAB, }, Y_H_Read_BUF[2]={0, },
			Z_L_Read_INIT[2] = {0xAC, }, Z_L_Read_BUF[2]={0, },
			Z_H_Read_INIT[2] = {0xAD, }, Z_H_Read_BUF[2]={0, };


	// write CTRL_REG1 to NORMAL MODE

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi5, ms_init_write, 2, 0xFF);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi5, test_read_init, read_buff, 2, 0xFF);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);

    // ms bit '1' Auto read test
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi5, X_L_Read_INIT, X_L_Read_BUF, 2, 0xFF);
	HAL_SPI_Receive(&hspi5,  X_H_Read_BUF, 2, 0xFF);
	HAL_SPI_Receive(&hspi5,  Y_L_Read_BUF, 2, 0xFF);
	HAL_SPI_Receive(&hspi5,  Y_H_Read_BUF, 2, 0xFF);
	HAL_SPI_Receive(&hspi5,  Z_L_Read_BUF, 2, 0xFF);
	HAL_SPI_Receive(&hspi5,  Z_H_Read_BUF, 2, 0xFF);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);

	uint8_t gyroData_test[100]={0, };
	sprintf((char *)gyroData_test, "\n Gyro Value : \r\n X : %d %d\r\n Y : %d %d\r\n Z : %d %d\r\n",
			X_L_Read_BUF[1], X_H_Read_BUF[1], Y_L_Read_BUF[1], Y_H_Read_BUF[1], Z_L_Read_BUF[1], Z_H_Read_BUF[1]);
	HAL_UART_Transmit(&huart1, gyroData_test, strlen(gyroData_test), 0xFF);

//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//	HAL_SPI_TransmitReceive(&hspi5, xl_tx, xl_rx, 2, 0xFF);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
//
//	HAL_Delay(10);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//	HAL_SPI_TransmitReceive(&hspi5, xh_tx, xh_rx, 2, 0xFF);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
//
//	HAL_Delay(10);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//	HAL_SPI_TransmitReceive(&hspi5, yl_tx, yl_rx, 2, 0xFF);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
//
//	HAL_Delay(10);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//	HAL_SPI_TransmitReceive(&hspi5, yh_tx, yh_rx, 2, 0xFF);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
//
//	HAL_Delay(10);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//	HAL_SPI_TransmitReceive(&hspi5, zl_tx, zl_rx, 2, 0xFF);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
//
//	HAL_Delay(10);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//	HAL_SPI_TransmitReceive(&hspi5, zh_tx, zh_rx, 2, 0xFF);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);

//	sprintf((char *)gyroData_tx, "Gyro Value : \r\n X : %d %d\r\n Y : %d %d\r\n Z : %d %d\r\n",
//			xl_rx[1], xh_rx[1], yl_rx[1], yh_rx[1], zl_rx[1], zh_rx[1]);
//	HAL_UART_Transmit(&huart1, gyroData_tx, strlen(gyroData_tx), 0xFF);

}

uint8_t ReadReg0(void)
{

}

int whoIam(void)
{

	int ret = -1;
//	uint8_t dummy[2] = {0, };
//	HAL_SPI_TransmitReceive_DMA(&hspi5, id_get_tx, dummy, 2);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi5, &who_iam_cmd_tx, 1, 0xFF);
    HAL_SPI_Receive(&hspi5, id_get_tx, 2, 0xFF);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);


	if(id_get_tx[1] != 0xFF)
	{
		ret = 0;
	}

	return ret;

}
