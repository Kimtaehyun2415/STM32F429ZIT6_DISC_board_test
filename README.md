# STM32F429ZIT6_DISC_board_test
STM32F429ZIT6_DISC_board_test

 - No use bare metal , use Free RTOS
 - Fress RTOS
   - Task 1 : ADC Test, Can Test(MCP2551)
   - Task 2 : l3gd20 Test
   - Task 3 : PWM_duty_control
   - Task 4 : name Error(hSemTask), no Semaphore Task , stmpe811 test (normal task)
   - SemaTask : semaphore Task, User push button -> LED ON/OFF
   
 - Touch Sensor (I2C) : stmpe811
 - Gyro Sensor (SPI) : l3gd20
 - TIM, PWM Duty period change check
 - Polling ADC(no DMA, no interrupt)
 - data check, transmit polling UART
 - only dev-board test STM32F429ZIT6 DISC
