
#include "stmpe811.h"

extern I2C_HandleTypeDef hi2c3;
extern SPI_HandleTypeDef hspi5;
extern UART_HandleTypeDef huart1;

uint16_t STMPE811_addr=0x82;
uint8_t T_buffer[8];
uint8_t R_buffer[8];

void stmpe811_init(void)
{
    T_buffer[7] = 0x00;
    R_buffer[7] = 0x00;


    stmpe811_write(0x02,0x03); // Reset bit 1
    stmpe811_write(0x00,0x03); // Reset bit 0
    stmpe811_write(0x08,0x04);  // GPIO, TSC, ADC clock on
    stmpe811_write(0x49,0x20); // sampling time: 80, 12-bit ADC
    stmpe811_write(0x01,0x21);  // ADC frequency: 3.25MHz
    stmpe811_write(0x9A,0x41); // Average 4 samples, detect delay 500 us, settling time 500 us
    stmpe811_write(0x01,0x4A); // FIFO threshold: 0x01
    stmpe811_write(0x01,0x4B); // Reset FIFO bit 1
    stmpe811_write(0x00,0x4B); // Reset FIFO bit 0
    stmpe811_write(0x01,0x56); // Touchscreen controller fraction: 1, whole part: 7
    stmpe811_write(0x01,0x58); // Maximum current of TSC: 80mA
    stmpe811_write(0xFF,0x0B); // Clear all interrupt status
    stmpe811_write(0x01,0x40); // Enable TSC

}

uint8_t stmpe811_read(uint8_t* x, uint8_t* y)
{
       HAL_I2C_Mem_Read(&hi2c3, STMPE811_addr, 0x40, 1, R_buffer, 1, 1000);
       HAL_Delay(1);

       if (R_buffer[0] & 0x80)
       {
		  // FIFO number
		  HAL_I2C_Mem_Read(&hi2c3, STMPE811_addr, 0x4C, 1, R_buffer + 1, 1, 1000);

		  HAL_I2C_Mem_Read(&hi2c3, STMPE811_addr, 0xD7, 1, R_buffer + 2, 4, 1000);
       }
       else
       {
        return 0;
       }

       *x = (R_buffer[2] << 4) | (R_buffer[3] >> 4);
       *y = ((R_buffer[3] & 0x0F) <<8) | R_buffer[4];

       T_buffer[0] = 0x01;  // Reset FIFO bit 1
       HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x4B, 1, T_buffer, 1, 1000);

       T_buffer[0] = 0x00;  // Reset FIFO bit 0
       HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x4B, 1, T_buffer, 1, 1000);

       return 1;

}

void stmpe811_Test(void)
{

	uint16_t x0 = 0;
	uint16_t y0 = 0;

	stmpe811_read(&x0, &y0);


	uint8_t i2cdata[100]={0, };
	sprintf((char *)&i2cdata, "\n location : %d %d\r\n", x0, y0);
	HAL_UART_Transmit(&huart1, i2cdata, 50, 0xFF);

}

void stmpe811_write(uint8_t bit_cmd,uint8_t Wdata)
{
	if(bit_cmd == 0x02)  // reset bit 1
	{
		T_buffer[0] = bit_cmd;
		HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, Wdata, 1, T_buffer, 1, 1000);
	    HAL_Delay(10);
	}
	else if(bit_cmd == 0x00) // reset bit 0
	{
		T_buffer[0] = bit_cmd;
		HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, Wdata, 1, T_buffer, 1, 1000);
	    HAL_Delay(2);
	}
	else
	{
		T_buffer[0] = bit_cmd;
		HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, Wdata, 1, T_buffer, 1, 1000);
	}

}



