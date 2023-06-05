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

#include	"hw_types.h"
#include	"soc_AM335x.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME													1000000/4
#define TOGGLE          										(0x01u)

#define CM_PER_GPIO1											0xAC
#define CM_PER_GPIO2											0xB0
#define CM_PER_GPIO3											0xB4

#define GPIO_DATAIN												0x138

// clock enable
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE   				(0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK   			(0x00040000u)
#define CM_PER_GPIO3_CLKCTRL_MODULEMODE_ENABLE					(0x2u)
#define CM_PER_GPIO3_CLKCTRL_OPTFCLKEN_GPIO_3_GDBCLK			(0x00040000u)

#define CM_conf_gpmc_ben1      	 								0x0878
#define CM_conf_gpmc_a5         								0x0854
#define CM_conf_gpmc_a6         								0x0818
#define CM_conf_gpmc_a7         								0x081C
#define CM_conf_gpmc_a8         								0x0820
#define CM_conf_gpmc_ad12         								0x0830
#define CM_conf_lcd_data0										0x08A0
#define CM_conf_lcd_data1										0x08A4
#define CM_conf_lcd_data2										0x08A8
#define CM_conf_lcd_data3										0x08AC
#define CM_conf_mcasp0_fsr										0x09A4

#define WDT1													0x44E35000
#define WDT_WSPR												0x48
#define WDT_WWPS												0x34



#define GPIO_OE                 								0x134
#define GPIO_CLEARDATAOUT       								0x190
#define GPIO_SETDATAOUT         								0x194


unsigned int flagBlink;
unsigned int flagBlink2;
unsigned int flagBlink3;
unsigned int flagBlink4;
unsigned int protoFlagBlink1;
unsigned int protoFlagBlink2;
unsigned int protoFlagBlink3;
unsigned int protoFlagBlink4;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay();
static void ledInit();
static void buttonInit();
static void ledToggle();
static void ledToggle2();
static void ledToggle3();
static void ledToggle4();
static void protoboardLedToggle1();
static void protoboardLedToggle2();
static void protoboardLedToggle3();
static void protoboardLedToggle4();

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int _main(void){
	// disable watchdog
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
	buttonInit();
  	ledInit();
  

  	while (1){
    	/* Change the state of the green LED. */
    	if ((HWREG(SOC_GPIO_3_REGS+GPIO_DATAIN) & (1<<19)) == 0) {
    		while((HWREG(SOC_GPIO_3_REGS+GPIO_DATAIN) & (1<<19)) == 0) {
    			ledToggle();
    			ledToggle2();
    			ledToggle3();
    			ledToggle4();
    			protoboardLedToggle1();
    			protoboardLedToggle2();
    			protoboardLedToggle3();
    			protoboardLedToggle4();
    		}
    	}
    	ledToggle();
		delay();
		ledToggle2();
		delay();
		ledToggle3();
		delay();
		ledToggle4();
		delay();
		protoboardLedToggle1();
		delay();
		protoboardLedToggle2();
		delay();
		protoboardLedToggle3();
		delay();
		protoboardLedToggle4();
		delay();
	}

	return(0);
} /* ----------  end of function main  ---------- */


/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/
static void delay(){
	volatile unsigned int ra;
	for(ra = 0; ra < TIME; ra ++);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  buttonInit
 *  Description:  configure the clock of the GPIO used for the button, and the mux pin
 * =====================================================================================
 */


void buttonInit(){


	unsigned int val_temp_button;
	/*-----------------------------------------------------------------------------
	 *  configure clock GPIO in clock module
	 *-----------------------------------------------------------------------------*/
	HWREG(SOC_CM_PER_REGS+CM_PER_GPIO3) |= CM_PER_GPIO3_CLKCTRL_OPTFCLKEN_GPIO_3_GDBCLK | CM_PER_GPIO3_CLKCTRL_MODULEMODE_ENABLE;
	
	/*-----------------------------------------------------------------------------
	 * configure mux pin in control module
	 *-----------------------------------------------------------------------------*/
	HWREG(SOC_CONTROL_REGS+CM_conf_mcasp0_fsr) |= (1<<5);
	// HWREG(SOC_CONTROL_REGS+CM_conf_mcasp0_fsr) &= ~(1<<3);
	HWREG(SOC_CONTROL_REGS+CM_conf_mcasp0_fsr) |= 7;
	val_temp_button = HWREG(SOC_GPIO_3_REGS+GPIO_OE);
	val_temp_button |= (1<<19);
	HWREG(SOC_GPIO_3_REGS+GPIO_OE) = val_temp_button;


}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledInit
 *  Description:  configure the clock of the GPIO used for the leds, and the mux pin
 * =====================================================================================
 */

void ledInit(){
	
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





