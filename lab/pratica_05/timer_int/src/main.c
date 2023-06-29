/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/05/2018 14:32:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "bbb_regs.h"
#include "hw_types.h"
#include "interrupt.h"
#include "timer.h"
#include "uart.h"

/**
 * \brief   This macro will check for write POSTED status
 *
 * \param   reg          Register whose status has to be checked
 *
 *    'reg' can take the following values \n
 *    DMTIMER_WRITE_POST_TCLR - Timer Control register \n
 *    DMTIMER_WRITE_POST_TCRR - Timer Counter register \n
 *    DMTIMER_WRITE_POST_TLDR - Timer Load register \n
 *    DMTIMER_WRITE_POST_TTGR - Timer Trigger register \n
 *    DMTIMER_WRITE_POST_TMAR - Timer Match register \n
 *
 **/

#define DMTimerWaitForWrite(reg)   \
            if(HWREG(DMTIMER_TSICR) & 0x4)\
            while((reg & HWREG(DMTIMER_TWPS)));


bool flag_timer = false;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  disableWdt
 *  Description:  
 * =====================================================================================
 */
void disableWdt(void){
	HWREG(WDT_WSPR) = 0xAAAA;
	while((HWREG(WDT_WWPS) & (1<<4)));
	
	HWREG(WDT_WSPR) = 0x5555;
	while((HWREG(WDT_WWPS) & (1<<4)));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioSetup
 *  Description:  
 * =====================================================================================
 */
void gpioSetup(){
    /* set clock for GPIO1, TRM 8.1.12.1.31 */
    HWREG(CM_PER_GPIO1_CLKCTRL) = 0x40002;

    /* clear pin 21 for output, led USR0, TRM 25.3.4.3 */
    HWREG(GPIO1_OE) &= ~(1<<21);
    HWREG(GPIO1_OE) &= ~(1<<22);
    HWREG(GPIO1_OE) &= ~(1<<23);
    HWREG(GPIO1_OE) &= ~(1<<24);

    HWREG(GPIO2_OE) &= ~(1<<6);
    HWREG(GPIO2_OE) &= ~(1<<7);
    HWREG(GPIO2_OE) &= ~(1<<8);
    HWREG(GPIO2_OE) &= ~(1<<9);
}

void ledConfig(){
    HWREG(CM_PER_GPMCA5_REGS) |= 0x7;
    HWREG(CM_PER_GMPCA6_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA7_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA8_REGS) |= 0x7;

    HWREG(CM_CONF_LCD_DATA0)  |= 0x7;
    HWREG(CM_CONF_LCD_DATA1)  |= 0x7;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOff
 *  Description:  
 * =====================================================================================
 */
void ledOff(void){
    HWREG(GPIO1_CLEARDATAOUT) |= (1<<21);
    HWREG(GPIO1_CLEARDATAOUT) |= (1<<22);
    HWREG(GPIO1_CLEARDATAOUT) |= (1<<23);
    HWREG(GPIO1_CLEARDATAOUT) |= (1<<24);

    HWREG(GPIO2_CLEARDATAOUT) |= (1<<6);
    HWREG(GPIO2_CLEARDATAOUT) |= (1<<7);
    HWREG(GPIO2_CLEARDATAOUT) |= (1<<8);
    HWREG(GPIO2_CLEARDATAOUT) |= (1<<9);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOn
 *  Description:  
 * =====================================================================================
 */
void ledOn(void){
    HWREG(GPIO1_SETDATAOUT) |= (1<<21);
    HWREG(GPIO1_SETDATAOUT) |= (1<<22);
    HWREG(GPIO1_SETDATAOUT) |= (1<<23);
    HWREG(GPIO1_SETDATAOUT) |= (1<<24);

    HWREG(GPIO2_SETDATAOUT) |= (1<<6);
    HWREG(GPIO2_SETDATAOUT) |= (1<<7);
    HWREG(GPIO2_SETDATAOUT) |= (1<<8);
    HWREG(GPIO2_SETDATAOUT) |= (1<<9);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	char count=9;
	
	/* Hardware setup */
	gpioSetup();
    ledConfig();
	timerSetup();
	disableWdt();

    putString("Timer Interrupt: ",17);

	while(count){
		putCh(0x30+count);
		putCh(' ');
        ledOn();
        putString("HIGH\n\r", 6);
		delay(1000);
        ledOff();
        putString("LOW\n\r", 5);
        count--;
    }
	putString("...OK",5);

    while(1){
        ledOn();
        delay(1000);
        ledOff();
    }


	return(0);
}

/**
 * COMPILE AND RUN [minicom]
 * setenv app "setenv autoload no; setenv serverip 10.4.1.1; setenv ipaddr 10.4.1.2; tftp 0x80000000 /tfptboot/appTimer.bin; go 0x80000000;"
 * run app
**/


