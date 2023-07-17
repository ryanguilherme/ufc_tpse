/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "timer.h"
#include "gpio.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "led.h"
#include "interrupt.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define CM_PER_GPMCBEn1_REGS                    0x44E10878

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/

bool flag_gpio;

bool flag_timer;


void disableWdt ( ){
    HWREG(SOC_WDT_1_REGS + WDT_WSPR) = 0xAAAA;
    while ((HWREG(SOC_WDT_1_REGS + WDT_WWPS) & (1<<4)) != 0 ) { }
    HWREG(SOC_WDT_1_REGS + WDT_WSPR) = 0x5555;
    while ((HWREG(SOC_WDT_1_REGS + WDT_WWPS) & (1<<4)) != 0 ) { }
}

void butConfig ( ){
    /* configure pin 28 mux for input GPIO */
    HWREG(CM_PER_GPMCBEn1_REGS) |= 0x2F;
    //gpioPinMuxSetup(GPIO1, 28);

    /* clear pin 28 for input, led USR0, TRM 25.3.4.3 */
    HWREG(SOC_GPIO_1_REGS + GPIO_OE) |= 1<<28;

    flag_gpio = false;

    /* Setting interrupt GPIO pin. */
    HWREG(SOC_GPIO_1_REGS + GPIO_IRQSTATUS_SET_0) |= 1<<28;

    /* Enable interrupt generation on detection of a rising edge.*/
    HWREG(SOC_GPIO_1_REGS + GPIO_RISINGDETECT) |= 1<<28;

    /* Enable debounce for pin 28 GPIO1 */
    HWREG(SOC_GPIO_1_REGS + GPIO_DEBOUNCENABLE) |= 1<<28;
}/* -----  end of function butConfig  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int main(void){

    disableWdt();

    DMTimerSetUp();

    gpioInitModule(GPIO1);
    gpioInitModule(GPIO2);
    ledConfig();
//    HWREG(INTCPS + INTC_MIR_CLEAR2) |= (1<<31);
//    HWREG(INTCPS + INTC_MIR_CLEAR3) |= (1<<2);//(98 --> Bit 2 do 4º registrador (MIR CLEAR3))

    mirClear(95);
    mirClear(98);

    butConfig();

    unsigned int delayIN = 100;

    while (1){
        // uartPutString(UART0, "ENTERED WHILE\n\r", 16);
        if (flag_gpio) {
            gpioSetPinValue(GPIO1, 21, HIGH);
            gpioSetPinValue(GPIO1, 22, HIGH);
            gpioSetPinValue(GPIO1, 23, HIGH);
            gpioSetPinValue(GPIO1, 24, HIGH);
            delay(delayIN);
            gpioSetPinValue(GPIO1, 21, LOW);
            gpioSetPinValue(GPIO1, 22, LOW);
            gpioSetPinValue(GPIO1, 23, LOW);
            gpioSetPinValue(GPIO1, 24, LOW);
            delay(delayIN);
            gpioSetPinValue(GPIO2, 6, HIGH);
            gpioSetPinValue(GPIO2, 7, HIGH);
            gpioSetPinValue(GPIO2, 8, HIGH);
            gpioSetPinValue(GPIO2, 9, HIGH);
            delay(delayIN);
            gpioSetPinValue(GPIO2, 6, LOW);
            gpioSetPinValue(GPIO2, 7, LOW);
            gpioSetPinValue(GPIO2, 8, LOW);
            gpioSetPinValue(GPIO2, 9, LOW);
            delay(delayIN);
        }
        else{
            gpioSetPinValue(GPIO1, 21, HIGH);
            gpioSetPinValue(GPIO1, 22, HIGH);
            gpioSetPinValue(GPIO1, 23, HIGH);
            gpioSetPinValue(GPIO1, 24, HIGH);
            gpioSetPinValue(GPIO2, 6, HIGH);
            gpioSetPinValue(GPIO2, 7, HIGH);
            gpioSetPinValue(GPIO2, 8, HIGH);
            gpioSetPinValue(GPIO2, 9, HIGH);
            delay(delayIN);
            gpioSetPinValue(GPIO1, 21, LOW);
            gpioSetPinValue(GPIO1, 22, LOW);
            gpioSetPinValue(GPIO1, 23, LOW);
            gpioSetPinValue(GPIO1, 24, LOW);
            gpioSetPinValue(GPIO2, 6, LOW);
            gpioSetPinValue(GPIO2, 7, LOW);
            gpioSetPinValue(GPIO2, 8, LOW);
            gpioSetPinValue(GPIO2, 9, LOW);
            delay(delayIN);
        }
    }

	return(0);
} /* ----------  end of function main  ---------- */

/* COMPILE AND RUN
 * setenv app "setenv autoload no; setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1; tftp 0x80000000 /tftpboot/appTimer.bin; go 0x80000000;"
 * run app
*/