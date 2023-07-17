//
// Created by ryan on 28/06/23.
//

#include "interrupt.h"

#include "hw_types.h"
#include "uart.h"

void timerIrqHandler(void) {
    HWREG(SOC_DMTIMER_7_REGS + DMTIMER_IRQSTATUS) = 0x2;

    flag_timer = true;

    DMTimerDisable(SOC_DMTIMER_7_REGS);
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioIsrHandler
 *  Description:
 * =====================================================================================
 */
void gpioIsrHandler(void){

    uartPutString(UART0, "BUTTON PRESSED\n\r", 17);
    /* Clear the status of the interrupt flags */
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_0) = 0x10000000;

    flag_gpio ^= 1;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ISR_Handler
 *  Description:
 * =====================================================================================
 */
void ISR_Handler(void){
    /* Verify active IRQ number */
    unsigned int irq_number = HWREG(INTCPS + INTC_SIR_IRQ) & 0x7f;

    if(irq_number == 98)
        gpioIsrHandler();
    else if (irq_number == 95)
        timerIrqHandler();

    /* acknowledge IRQ */
    HWREG(INTCPS + INTC_CONTROL) = 0x1;
}