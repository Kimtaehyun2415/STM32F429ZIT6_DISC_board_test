/*
 * stmpe811.c
 *
 *  Created on: Jul 13, 2023
 *      Author: user
 */

#include "stmpe811.h"

extern I2C_HandleTypeDef hi2c3;
extern LTDC_HandleTypeDef hltdc;
extern SPI_HandleTypeDef hspi5;
extern UART_HandleTypeDef huart1;

uint16_t STMPE811_addr=0x82;
uint8_t T_buffer[8];
uint8_t R_buffer[8];

void stmpe811_init(void)
{
    T_buffer[7] = 0x00;
    R_buffer[7] = 0x00;

    T_buffer[0] = 0x02;  // Reset bit 1
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x03, 1, T_buffer, 1, 1000);
    HAL_Delay(10);

    T_buffer[0] = 0x00;  // Reset bit 0
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x03, 1, T_buffer, 1, 1000);
    HAL_Delay(2);

    T_buffer[0] = 0x08;  // GPIO, TSC, ADC clock on
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x04, 1, T_buffer, 1, 1000);

    T_buffer[0] = 0x49;  // sampling time: 80, 12-bit ADC
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x20, 1, T_buffer, 1, 1000);
    HAL_Delay(1);

    T_buffer[0] = 0x01;  // ADC frequency: 3.25MHz
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x21, 1, T_buffer, 1, 1000);

    T_buffer[0] = 0x9A;  // Average 4 samples, detect delay 500 us, settling time 500 us
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x41, 1, T_buffer, 1, 1000);

    T_buffer[0] = 0x01;  // FIFO threshold: 0x01
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x4A, 1, T_buffer, 1, 1000);

    T_buffer[0] = 0x01;  // Reset FIFO bit 1
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x4B, 1, T_buffer, 1, 1000);

    T_buffer[0] = 0x00;  // Reset FIFO bit 0
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x4B, 1, T_buffer, 1, 1000);

    T_buffer[0] = 0x01;  // Touchscreen controller fraction: 1, whole part: 7
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x56, 1, T_buffer, 1, 1000);

    T_buffer[0] = 0x01;  // Maximum current of TSC: 80mA
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x58, 1, T_buffer, 1, 1000);

    T_buffer[0] = 0xFF;  // Clear all interrupt status
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x0B, 1, T_buffer, 1, 1000);

    T_buffer[0] = 0x01;  // Enable TSC
    HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x40, 1, T_buffer, 1, 1000);

}

uint8_t stmpe811_read(uint8_t* x, uint8_t* y)
{
       HAL_I2C_Mem_Read(&hi2c3, STMPE811_addr, 0x40, 1, R_buffer, 1, 1000);
       HAL_Delay(1);

       if (R_buffer[0] & 0x80)  // if touch is detected
       {
		  // FIFO number
		  HAL_I2C_Mem_Read(&hi2c3, STMPE811_addr, 0x4C, 1, R_buffer + 1, 1, 1000);
		  // x, y, and z(pressure) data
		  // 0xD7 STMPE611 non-auto-increment
		  // 0x07 STMPE811 non-auto-increment
		  HAL_I2C_Mem_Read(&hi2c3, STMPE811_addr, 0xD7, 1, R_buffer + 2, 4, 1000);
       }
       else
       {
        return 0;
       }

       *x = (R_buffer[2] << 4) | (R_buffer[3] >> 4);
       *y = ((R_buffer[3] & 0x0F) <<8) | R_buffer[4];
//     *z = R_buffer[5];  // for debugging
       T_buffer[0] = 0x01;  // Reset FIFO bit 1
       HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x4B, 1, T_buffer, 1, 1000);

       T_buffer[0] = 0x00;  // Reset FIFO bit 0
       HAL_I2C_Mem_Write(&hi2c3, STMPE811_addr, 0x4B, 1, T_buffer, 1, 1000);

       return 1;

}

void stmpe811_Test(void)
{
	//ili9341 Touch Screen
//	uint16_t frame_buffer[76800];  // frame buffer for 240 x 320 TFT-LCD
	uint16_t x0 = 0;
	uint16_t y0 = 0;
//	uint16_t px = 0;
//	uint16_t py = 0;

//	int i;
//	uint8_t flag_TSC = 0;
//	unsigned char c_str1[] = "Touchscreen test";
//	unsigned char c_str2[] = "(x0,y0) = (    ,    )";
//	unsigned char c_str3[] = "(px,py) = (    ,    )";
//	unsigned char c_str4[] = "Pressed";
//	unsigned char n_str1[12];
//	unsigned char n_str2[12];
//	unsigned char n_str3[12];
//	unsigned char n_str4[12];
//
	stmpe811_read(&x0, &y0);
//	flag_TSC = stmpe811_read(&x0, &y0);
//	if(flag_TSC)
//	{
//	   ILI9341_str(100, 50, 24, 0xFFFF, 0xF81F, c_str4);
//	}
//	else
//	{
//	   ILI9341_str(100, 50, 24, 0xFFFF, 0xFFFF, c_str4);
//	}

	uint8_t i2cdata[100]={0, };
	sprintf((char *)&i2cdata, "\n location : %d %d\r\n", x0, y0);
	HAL_UART_Transmit(&huart1, i2cdata, 50, 0xFF);

	//   GPIOC->BSRR = 0x0004;       // PC2(SS,CSX) high
	//   ili9341_Init();             // initialize ILI9341
	//   ili9341_WriteReg(LCD_MAC);  // Memory Access Control Register
	//   ili9341_WriteData(0x88);    // MY = 1, MX= 0, MV = 0
	//   HAL_LTDC_SetAddress(&hltdc, (uint32_t) frame_buffer, 0); // set address of frame_buffer
	//   stmpe811_init();
	//
	//   for (i = 0; i < 76800; i++)
	//   {
	//          frame_buffer[i] = 0xFFFF;  // white background
	//   }
	//   ILI9341_str(30, 10, 24, 0xFFFF, 0x0000, c_str1);   // black
	//   ILI9341_str(10, 90, 20, 0xFFFF, 0x001F, c_str2);   // red
	//   ILI9341_str(10, 120, 20, 0xFFFF, 0xF800, c_str3);  // blue

	//  	    flag_TSC = stmpe811_read(&x0, &y0);
	//		if (flag_TSC)
	//		{
	//			   ILI9341_str(100, 50, 24, 0xFFFF, 0xF81F, c_str4);
	//		}
	//		else
	//		{
	//			   ILI9341_str(100, 50, 24, 0xFFFF, 0xFFFF, c_str4);
	//		}
	//		px = y0 / 11 - 30;
	//		py = x0 / 14 - 20;
	//
	//		integer_str(n_str1, x0, 4);  //  x0
	//		integer_str(n_str2, y0, 4);  //  y0
	//		integer_str(n_str3, px, 3);  //  x0
	//		integer_str(n_str4, py, 3);  //  y0
	//
	//		ILI9341_str(165, 90, 20, 0xFFFF, 0x001F, n_str1);
	//		ILI9341_str(235, 90, 20, 0xFFFF, 0x001F, n_str2);
	//		ILI9341_str(175, 120, 20, 0xFFFF, 0xF800, n_str3);
	//		ILI9341_str(245, 120, 20, 0xFFFF, 0xF800, n_str4);
	//		HAL_Delay(200);
}

void ILI9341_font(uint16_t x1, uint16_t y1, uint16_t size, uint16_t RGB0, uint16_t RGB1,uint8_t code)
{
   uint16_t i, j, imax, f_width, f_arr_width;
   uint8_t* f_ptr;  // pointer to an array of font table
   uint8_t c_code;  // converted ASCII code

   f_width = 0;     // font width, used to check if the font table is available
   f_arr_width = 0; // width of the font array

   if (size == 16)
   {
		  f_width = 11;
		  f_arr_width = 2;
	//	  f_ptr = &Font1116_Table;
   }
   else if (size == 20)
   {
		  f_width = 14;
		  f_arr_width = 2;
	//	  f_ptr = &Font1420_Table;
   }
   else if (size == 24)
   {
		  f_width = 16;
		  f_arr_width = 3;
	//	  f_ptr = &Font1724_Table;
   }
   if (code < 20)
   {
		  c_code = 0x20;  // blank
   }
   else
   {
		  c_code = code - 0x20;  // ST font table is shifted by 0x20
   }

   if (f_width)  // if width of the font is not zero (font table is available)
   {
		  for (j = 0; j < size; j++)  // j: relative coordinate of y, height = size
		  {
				 for (i = 0; i < 8; i++)  // Relative coordinate of x
				 {
					   if (*(f_ptr + size * f_arr_width * c_code + f_arr_width * j)
									 & (1 << (7 - i))) // if (7 - i)th bit is 1
					   {
							  //*(frame_buffer + y1 + j + (x1 + i) * 240) = RGB1; // foreground
					   }
					   else
					   {
							 // *(frame_buffer + y1 + j + (x1 + i) * 240) = RGB0; // background
					   }
				 }

				 for (i = 8; i < f_width; i++)
				 {
					   if (*(f_ptr + size * f_arr_width * c_code + f_arr_width * j + 1)
									 & (1 << (15 - i))) // if (15 - i)th bit is 1
					   {
							//  *(frame_buffer + y1 + j + (x1 + i) * 240) = RGB1; // foreground
					   }
					   else
					   {
							//  *(frame_buffer + y1 + j + (x1 + i) * 240) = RGB0; // background
					   }
				 }
		  }
   }
}

void ILI9341_str(uint16_t x1, uint16_t y1, uint16_t size, int RGB0, int RGB1, uint8_t* string)
{
       uint16_t i = 0;
       uint16_t f_width = 0;  // font width
       if (size == 16)
       {
              f_width = 11;
       }
       else if (size == 20)
       {
              f_width = 14;
       }
       else if (size == 24)
       {
              f_width = 16;
       }
       while (*(string) != '\0')
       {
              ILI9341_font(x1 + f_width * i, y1, size, RGB0, RGB1, *string);
              string++;
              i++;
       }
}

