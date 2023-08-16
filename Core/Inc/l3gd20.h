/*
 * l3gd20.h
 *
 *  Created on: 2023. 7. 12.
 *      Author: user
 */

#ifndef INC_L3GD20_H_
#define INC_L3GD20_H_


#include "main.h"


void l3gd20Init(void);
void l3gd20_Start(void);
uint8_t ReadReg0(void);


#endif /* INC_L3GD20_H_ */
