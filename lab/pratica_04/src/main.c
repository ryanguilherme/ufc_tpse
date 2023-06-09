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

#define TOGGLE          										(0x01u)

#define WDT1													0x44E35000
#define WDT_WSPR												0x48
#define WDT_WWPS												0x34

#define CM_PER_GPIO1											0xAC
#define CM_PER_GPIO2											0xB0
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

unsigned int flagBlink;
unsigned int flagBlink2;
unsigned int flagBlink3;
unsigned int flagBlink4;
unsigned int protoFlagBlink1;
unsigned int protoFlagBlink2;
unsigned int protoFlagBlink3;
unsigned int protoFlagBlink4;

static void ledInit();
static void ledToggle();
static void ledToggle2();
static void ledToggle3();
static void ledToggle4();
static void protoboardLedToggle1();
static void protoboardLedToggle2();
static void protoboardLedToggle3();
static void protoboardLedToggle4();

int main(void){
	// unsigned char count=9;

	/*-----------------------------------------------------------------------------
	 *  initialize UART modules
	 *-----------------------------------------------------------------------------*/
	uartInitModule(UART0, 115200, STOP1, PARITY_NONE, FLOW_OFF);
	
	/*-----------------------------------------------------------------------------
	 *  initialize TIMER modules
	 *-----------------------------------------------------------------------------*/
    DMTimerSetUp();

	//uartPutString(UART0,"GPIO INPUT Initialized",23);	
//  	uartPutString(UART0,"Time: ",7);
//  	while(count){
//		uartPutC(UART0,0x30+count);
//		Delay(1000);
//		count--;
//		uartPutC(UART0,' ');
//	}
//	uartPutString(UART0,"OK...",5);
    HWREG(WDT1+WDT_WSPR) = 0xAAAA;
    while ((HWREG(WDT1+WDT_WWPS) & (1<<4)) != 0 ) { }
    HWREG(WDT1+WDT_WSPR) = 0x5555;
    while ((HWREG(WDT1+WDT_WWPS) & (1<<4)) != 0 ) { }

    flagBlink=0;	//init flag
    flagBlink2=0;
    flagBlink3=0;
    flagBlink4=0;
    protoFlagBlink1=0;
    protoFlagBlink2=0;
    protoFlagBlink3=0;
    protoFlagBlink4=0;

    /* Configure the green LED control pin. */
    ledInit();

    uartPutString(UART0, "LEDS INITIALIZING", 18);
//    uartPutString(UART0, "LED BLINK\n", 11);

    uartPutC(UART0, '\n');

    int delayIN = 1;
    char buffer[4];
    uartPutString(UART0, "CHOOSE A DELAY IN MS: ", 23);

    uartgetString(UART0, buffer, 4);

    while (1){
        /* Change the state of the green LED. */
        ledToggle();
        //uartPutString(UART0, "LED BLINK", 10);
        Delay(delayIN);
        ledToggle2();
        //uartPutString(UART0, "LED BLINK", 10);
        Delay(delayIN);
        ledToggle3();
        //uartPutString(UART0, "LED BLINK", 10);
        Delay(delayIN);
        ledToggle4();
        //uartPutString(UART0, "LED BLINK", 10);
        Delay(delayIN);
        protoboardLedToggle1();
        //uartPutString(UART0, "LED BLINK", 10);
        Delay(delayIN);
        protoboardLedToggle2();
        //uartPutString(UART0, "LED BLINK", 10);
        Delay(delayIN);
        protoboardLedToggle3();
        //uartPutString(UART0, "LED BLINK", 10);
        Delay(delayIN);
        protoboardLedToggle4();
        //uartPutString(UART0, "LED BLINK", 10);
        Delay(delayIN);
    }

	return(0);
} /* ----------  end of function main  ---------- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ledInit
 *  Description:
 * =====================================================================================
 */
void ledInit( ){

    unsigned int val_temp;
    unsigned int val_temp_protoboard;
    /*-----------------------------------------------------------------------------
     *  configure clock GPIO in clock module
     *-----------------------------------------------------------------------------*/
    HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
    HWREG(SOC_CM_PER_REGS+CM_PER_GPIO2) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;

    /*-----------------------------------------------------------------------------
     * configure mux pin in control module
     *-----------------------------------------------------------------------------*/
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a5) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a6) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a7) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a8) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_lcd_data0) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_lcd_data1) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_lcd_data2) |= 7;
    HWREG(SOC_CONTROL_REGS+CM_conf_lcd_data3) |= 7;

    /*-----------------------------------------------------------------------------
     *  set pin direction
     *-----------------------------------------------------------------------------*/
    val_temp = HWREG(SOC_GPIO_1_REGS+GPIO_OE);
    val_temp &= ~(1<<21);
    val_temp &= ~(1<<22);
    val_temp &= ~(1<<23);
    val_temp &= ~(1<<24);
    HWREG(SOC_GPIO_1_REGS+GPIO_OE) = val_temp;
    val_temp_protoboard = HWREG(SOC_GPIO_2_REGS+GPIO_OE);
    val_temp_protoboard &= ~(1<<6);
    val_temp_protoboard &= ~(1<<7);
    val_temp_protoboard &= ~(1<<8);
    val_temp_protoboard &= ~(1<<9);
    HWREG(SOC_GPIO_2_REGS+GPIO_OE) = val_temp_protoboard;

}/* -----  end of function ledInit  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ledToggle
 *  Description:
 * =====================================================================================
 */

void protoboardLedToggle1() {

    protoFlagBlink1 ^= TOGGLE;
    if (protoFlagBlink1) {
        HWREG(SOC_GPIO_2_REGS+GPIO_SETDATAOUT) = 1<<6;
    } else {
        HWREG(SOC_GPIO_2_REGS+GPIO_CLEARDATAOUT) = 1<<6;
    }
}

void protoboardLedToggle2() {

    protoFlagBlink2 ^= TOGGLE;
    if (protoFlagBlink2) {
        HWREG(SOC_GPIO_2_REGS+GPIO_SETDATAOUT) = 1<<7;
    } else {
        HWREG(SOC_GPIO_2_REGS+GPIO_CLEARDATAOUT) = 1<<7;
    }
}

void protoboardLedToggle3() {

    protoFlagBlink3 ^= TOGGLE;
    if (protoFlagBlink3) {
        HWREG(SOC_GPIO_2_REGS+GPIO_SETDATAOUT) = 1<<8;
    } else {
        HWREG(SOC_GPIO_2_REGS+GPIO_CLEARDATAOUT) = 1<<8;
    }
}

void protoboardLedToggle4() {

    protoFlagBlink4 ^= TOGGLE;
    if (protoFlagBlink4) {
        HWREG(SOC_GPIO_2_REGS+GPIO_SETDATAOUT) = 1<<9;
    } else {
        HWREG(SOC_GPIO_2_REGS+GPIO_CLEARDATAOUT) = 1<<9;
    }
}


void ledToggle(){

    flagBlink ^= TOGGLE;

    if(flagBlink){
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<21;
    }else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<21;
    }
}/* -----  end of function ledToggle  ----- */

void ledToggle2(){

    flagBlink2 ^= TOGGLE;

    if(flagBlink2){
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<22;
    }else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<22;
    }

}

void ledToggle3(){

    flagBlink3 ^= TOGGLE;

    if(flagBlink3){
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<23;
    }else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<23;
    }

}

void ledToggle4(){

    flagBlink4 ^= TOGGLE;

    if(flagBlink4){
        HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<24;
    }else{
        HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<24;
    }

}

