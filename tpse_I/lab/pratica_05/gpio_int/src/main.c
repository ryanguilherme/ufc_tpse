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


bool flag_gpio;

typedef enum _pinNum{
	PIN1=1,
	PIN2=2,
	PIN3=3,
	PIN4=4,
	PROTO1=5,
	PROTO2=6,
	PROTO3=7,
	PROTO4=8
}pinNum;


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
 *         Name:  delay
 *  Description:  
 * =====================================================================================
 */
void delay(unsigned int mSec){
    volatile unsigned int count;
    
	for(count=0; count<mSec; count++);

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  putCh
 *  Description:  
 * =====================================================================================
 */
void putCh(char c){
	while(!(HWREG(UART0_LSR) & (1<<5)));

	HWREG(UART0_THR) = c;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getCh
 *  Description:  
 * =====================================================================================
 */
char getCh(){
	while(!(HWREG(UART0_LSR) & (1<<0)));

	return(HWREG(UART0_RHR));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  putString
 *  Description:  
 * =====================================================================================
 */
int putString(char *str, unsigned int length){
	for(int i = 0; i < length; i++){
    	putCh(str[i]);
	}
	return(length);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getString
 *  Description:  
 * =====================================================================================
 */
int getString(char *buf, unsigned int length){
	for(int i = 0; i < length; i ++){
    	buf[i] = getCh();
   	}
	return(length);
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
	HWREG(CM_PER_GPIO2_CLKCTRL) = 0x40002;

    /* Interrupt mask */
    HWREG(INTC_MIR_CLEAR3) |= (1<<2);//(98 --> Bit 2 do 4º registrador (MIR CLEAR3))
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  butConfig
 *  Description:  
 * =====================================================================================
 */
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledConfig
 *  Description:  
 * =====================================================================================
 */
void ledConfig ( ){
    /*  configure pin mux for output GPIO */
    HWREG(CM_PER_GPMCA5_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA6_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA7_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA8_REGS) |= 0x7;
    HWREG(CM_PER_LCD_DATA0)	  |= 0x7;
    HWREG(CM_PER_LCD_DATA1)	  |= 0x7;
    HWREG(CM_PER_LCD_DATA2)	  |= 0x7;
    HWREG(CM_PER_LCD_DATA3)	  |= 0x7;

    /* clear pin 21, 22, 23 and 24 for output, leds USR1, USR2, USR3 and USR4, TRM 25.3.4.3 */
    HWREG(GPIO1_OE) &= ~(1<<21);
    HWREG(GPIO1_OE) &= ~(1<<22);
    HWREG(GPIO1_OE) &= ~(1<<23);
    HWREG(GPIO1_OE) &= ~(1<<24);

    /* clear pin 6, 7, 8 and 9 for output, gpio's LCD_DATA0, LCD_DATA1, LCD_DATA2, LCD_DATA3 */
    HWREG(GPIO2_OE) &= ~(1<<6);
    HWREG(GPIO2_OE) &= ~(1<<7);
    HWREG(GPIO2_OE) &= ~(1<<8);
    HWREG(GPIO2_OE) &= ~(1<<9);

}/* -----  end of function ledConfig  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readBut
 *  Description:  
 * =====================================================================================
 */
unsigned int readBut ( ){
	unsigned int temp;
	temp = HWREG(GPIO1_DATAIN)&0x10000000;
	
	return(temp);
}/* -----  end of function readBut  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOff
 *  Description:  
 * =====================================================================================
 */
void ledOff(pinNum pin){
	switch (pin) {
		case PIN1:
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<21);
		break;
		case PIN2:	
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<22);
		break;
		case PIN3:	
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<23);
		break;
		case PIN4:	
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<24);
		break;
		case PROTO1:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<6);
		break;
		case PROTO2:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<7);
		break;
		case PROTO3:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<8);
		break;
		case PROTO4:	
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<9);
		break;
		default:
		break;
	}/* -----  end switch  ----- */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOn
 *  Description:  
 * =====================================================================================
 */
void ledOn(pinNum pin){
	switch (pin) {
		case PIN1:
			HWREG(GPIO1_SETDATAOUT) |= (1<<21);
		break;
		case PIN2:
			HWREG(GPIO1_SETDATAOUT) |= (1<<22);
		break;
		case PIN3:
			HWREG(GPIO1_SETDATAOUT) |= (1<<23);
		break;
		case PIN4:
			HWREG(GPIO1_SETDATAOUT) |= (1<<24);
		break;
		case PROTO1:
			HWREG(GPIO2_SETDATAOUT) |= (1<<6);
		break;
		case PROTO2:
			HWREG(GPIO2_SETDATAOUT) |= (1<<7);
		break;
		case PROTO3:
			HWREG(GPIO2_SETDATAOUT) |= (1<<8);
		break;
		case PROTO4:
			HWREG(GPIO2_SETDATAOUT) |= (1<<9);
		break;
		default:
		break;
	}/* -----  end switch  ----- */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	
	/* Hardware setup */
	gpioSetup();
	ledConfig();
	butConfig();
	disableWdt();

	putString("gpio Interrupt...\n\r",19);
	ledOff(PIN1);
	ledOff(PIN2);
	ledOff(PIN3);
	ledOff(PIN4);
	ledOff(PROTO1);
	ledOff(PROTO2);
	ledOff(PROTO3);
	ledOff(PROTO4);
	delay(10000);

	//flag_gpio = false;

	while(true){
		if(flag_gpio){
			putString("button press!\n\r",15);
			ledOn(PIN1);
			delay(10000000);
			ledOn(PIN2);
			delay(10000000);
			ledOn(PIN3);
			delay(10000000);
			ledOn(PIN4);
			delay(10000000);
			ledOn(PROTO1);
			delay(10000000);
			ledOn(PROTO2);
			delay(10000000);
			ledOn(PROTO3);
			delay(10000000);
			ledOn(PROTO4);
			delay(10000000);
			ledOff(PIN1);
			delay(10000000);
			ledOff(PIN2);
			delay(10000000);
			ledOff(PIN3);
			delay(10000000);
			ledOff(PIN4);
			delay(10000000);
			ledOff(PROTO1);
			delay(10000000);
			ledOff(PROTO2);
			delay(10000000);
			ledOff(PROTO3);
			delay(10000000);
			ledOff(PROTO4);
			delay(10000000);

			flag_gpio = false;
		}else{
			ledOn(PIN1);
			ledOn(PIN2);
			ledOn(PIN3);
			ledOn(PIN4);
			ledOn(PROTO1);
			ledOn(PROTO2);
			ledOn(PROTO3);
			ledOn(PROTO4);
			delay(10000000);
			ledOff(PIN1);
			ledOff(PIN2);
			ledOff(PIN3);
			ledOff(PIN4);
			ledOff(PROTO1);
			ledOff(PROTO2);
			ledOff(PROTO3);
			ledOff(PROTO4);
			delay(10000000);		
		}
	}

	return(0);
}

/* compile
 setenv autoload no; setenv serverip 10.4.1.1; setenv ipaddr 10.4.1.2; tftp 0x80000000 /tftpboot/appIntGpio.bin;
 go 0x80000000;
*/