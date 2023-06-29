//
// Created by ryan on 28/06/23.
//

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "bbb_regs.h"
#include "hw_types.h"

extern bool flag_gpio;

void gpioIsrHandler(void);
void ISR_Handler(void);


#endif //INTERRUPT_H
