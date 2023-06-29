//
// Created by ryan on 28/06/23.
//

#include "interrupt.h"

#include "hw_types.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioIsrHandler
 *  Description:
 * =====================================================================================
 */
void gpioIsrHandler(void){

    /* Clear the status of the interrupt flags */
    HWREG(GPIO1_IRQSTATUS_0) = 0x10000000;

    flag_gpio = true;
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ISR_Handler
 *  Description:
 * =====================================================================================
 */
void ISR_Handler(void){
    /* Verify active IRQ number */
    unsigned int irq_number = HWREG(INTC_SIR_IRQ) & 0x7f;

    if(irq_number == 98)
        gpioIsrHandler();

    /* acknowledge IRQ */
    HWREG(INTC_CONTROL) = 0x1;
}