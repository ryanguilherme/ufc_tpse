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

#include "uart.h"
#include <stdio.h>
#include "timer.h"
#include "gpio.h"
#include "hw_types.h"
#include "clock_module.h"
#include "pad.h"
#include "soc_AM335x.h"
#include "control_module.h"
#include "bbb_regs.h"
#include "led.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
	
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */

bool flag_gpio;

void butConfig ( ){
    /* configure pin 28 mux for input GPIO */
    HWREG(CM_PER_GPMCBEn1_REGS) |= 0x2F;

    /* clear pin 28 for input, led USR0, TRM 25.3.4.3 */
    HWREG(GPIO1_OE) |= 1<<28;

    flag_gpio = false;

    /* Setting interrupt GPIO pin. */
    HWREG(GPIO1_IRQSTATUS_SET_0) |= 1<<28;

    /* Enable interrupt generation on detection of a rising edge.*/
    HWREG(GPIO1_RISINGDETECT) |= 1<<28;
}/* -----  end of function butConfig  ----- */

int main(void){

    gpioInitModule(GPIO1);
    gpioInitModule(GPIO2);
    ledConfig();

    butConfig();
	/*-----------------------------------------------------------------------------
	 *  initialize UART modules
	 *-----------------------------------------------------------------------------*/
	uartInitModule(UART0, 115200, STOP1, PARITY_NONE, FLOW_OFF);
	
	/*-----------------------------------------------------------------------------
	 *  initialize TIMER modules
	 *-----------------------------------------------------------------------------*/
    DMTimerSetUp();

    HWREG(WDT_WSPR) = 0xAAAA;
    while ((HWREG(WDT_WWPS) & (1<<4)) != 0 ) { }
    HWREG(WDT_WSPR) = 0x5555;
    while ((HWREG(WDT_WWPS) & (1<<4)) != 0 ) { }

    int delayIN = 1000;

    /*
    Frequencia alvo: 62.5 Heartz
    Para cada led há um delay de 1 milisegundo
    Como há 8 leds, o delay é chamado para acender 8 vezes
    Como o delay também apaga o led 8 vezes, então o nosso perído equivale a 16 delays
    Logo, nosso período é 16ms
    Para calcular a frequência fazemos: F = 1/T onde F = frequência e T = período
    Sabendo que nosso período é 16ms, então fazemos F = 1/16 = 0.0625 KHz
    Esse resultado foi dado em KHz pois o período que utilizamos está em milisegundos, não segundos
    Para converter a frequência de KHz para Hz fazemos F * 10³
    Logo, 0.0625 * 10³ = 62.5Hz, a frequência alvo.
    */

    while (1){
        gpioSetPinValue(GPIO1, 21, HIGH);
        gpioSetPinValue(GPIO1, 22, HIGH);
        gpioSetPinValue(GPIO1, 23, HIGH);
        gpioSetPinValue(GPIO1, 24, HIGH);
        Delay(delayIN);
        gpioSetPinValue(GPIO1, 21, LOW);
        gpioSetPinValue(GPIO1, 22, LOW);
        gpioSetPinValue(GPIO1, 23, LOW);
        gpioSetPinValue(GPIO1, 24, LOW);
        Delay(delayIN);
        gpioSetPinValue(GPIO2, 6, HIGH);
        gpioSetPinValue(GPIO2, 7, HIGH);
        gpioSetPinValue(GPIO2, 8, HIGH);
        gpioSetPinValue(GPIO2, 9, HIGH);
        Delay(delayIN);
        gpioSetPinValue(GPIO2, 6, LOW);
        gpioSetPinValue(GPIO2, 7, LOW);
        gpioSetPinValue(GPIO2, 8, LOW);
        gpioSetPinValue(GPIO2, 9, LOW);
        Delay(delayIN);
    }

	return(0);
} /* ----------  end of function main  ---------- */

/* COMPILE AND RUN
 * setenv app "setenv autoload no; setenv ipaddr 10.4.1.2; setenv serverip 10.4.1.1; tftp 0x80000000 /tftpboot/appTimer.bin; go 0x80000000;"
 * run app
*/