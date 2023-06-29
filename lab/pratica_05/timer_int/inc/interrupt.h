//
// Created by ryan on 28/06/23.
//

#ifndef interrupt_h
#define interrupt_h

#include "hw_types.h"
#include "bbb_regs.h"

#define DMTimerWaitForWrite(reg)   \
            if(HWREG(DMTIMER_TSICR) & 0x4)\
            while((reg & HWREG(DMTIMER_TWPS)));

extern bool flag_timer;

void timerIrqHandle(void);
void ISRHandle(void);
void timerSetup(void);

#endif
