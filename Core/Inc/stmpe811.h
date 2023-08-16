/*
 * stmpe811.h
 *
 *  Created on: Jul 13, 2023
 *      Author: user
 */

#ifndef INC_STMPE811_H_
#define INC_STMPE811_H_

#include "main.h"

void stmpe811_init(void);
uint8_t stmpe811_read(uint8_t* x, uint8_t* y);
void stmpe811_Test(void);

#endif /* INC_STMPE811_H_ */
