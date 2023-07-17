//
// Created by ryan on 28/06/23.
//

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "soc_AM335x.h"
#include "hw_types.h"
#include "timer.h"
#include "gpio.h"

extern bool flag_gpio;
extern bool flag_timer;

#define INTCPS                  0x48200000
#define INTC_MIR_CLEAR0         0x88
#define INTC_MIR_CLEAR1         0xA8
#define INTC_MIR_CLEAR2         0xB8
#define INTC_MIR_CLEAR3         0xC8
#define INTC_MIR_CLEAR4         0xD8
#define INTC_MIR_CLEAR5         0xE8
#define INTC_SIR_IRQ            0x40
#define INTC_CONTROL            0x48

void gpioIsrHandler(void);
void ISR_Handler(void);
void timerIrqHandler(void);

#endif //INTERRUPT_H
