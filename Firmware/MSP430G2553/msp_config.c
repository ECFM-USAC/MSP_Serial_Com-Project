/*
 * msp_config.c
 *
 *	MSP_Serial_Com Project
 *
 *	Laboratorio de instrumentacion
 *	Escuela de Ciencias Fisicas y Matematicas
 *	USAC
 *
 *	ecfm.usac.edu.gt
 *
 *  Created on: Feb 23, 2016
 *      Author: Hector Perez (hector@ecfm.usac.edu.gt)
 */


/**
 * \file msp_config.c
 * \author Hector Perez (hector@ecfm.usac.edu.gt)
 * \date Feb 23, 2016
 *
 * \brief Harware Configuration for MSP430G2553
 *
 * File containing harware register configurations for
 * ports i/o, clock, UART, Timers and ADC.
 *
 * \see http://www.ti.com/product/MSP430G2553/technicaldocuments
 * \see http://www.ti.com/tool/msp-exp430g2#Technical%20Documents
 *
 */


#include "msp430g2553.h"
#include "msp_config.h"


/*! \brief Set Clock Function.
 *
 *  Sets the clock at 16 MHz using the
 *  pre-claibrated data.
 */
void SetClock_16Mhz(void){
		BCSCTL1 = CALBC1_16MHZ;
	    DCOCTL = CALDCO_16MHZ;
}

/*! \brief Set UART Function.
 *
 *  Configures the UART hardware to
 *  work at 9600 bauds & 8N1 mode with
 *  a clock at 16 MHz. This mode is
 *  the recomended to work with the integrated
 *  usb-serial in Launchpad
 *
 */
void SetUART_9600_16MHz(void){
	    P1SEL |= RXD + TXD ; 			// P1.1 = RXD, P1.2=TXD
	    P1SEL2 |= RXD + TXD ; 			// P1.1 = RXD, P1.2=TXD
	    UCA0CTL1 |= UCSSEL_2; 			// SMCLK
		UCA0BR0 = 0x82; 				// 16MHz 9600
		UCA0BR1 = 0x06; 				// 16MHz 9600
	    UCA0MCTL = UCBRS1 + UCBRS2; 	// Modulation UCBRSx = 6
	    UCA0CTL1 &= ~UCSWRST; 			// Enable USCI
	    UC0IE |= UCA0RXIE; 				// Enable USCI_A0 RX interrupt
}


/*! \brief Set UART Function.
 *
 *  Configures the UART hardware to
 *  work at 115200 bauds & 8N1 mode with
 *  a clock at 16 MHz. This mode can be used
 *  only with a external usb-serial adapter
 *  connected to RXD & TXD pins.
 *  WARNING: Don't forget to remove the
 *  UART junpers from the Launcpad.
 *
 */
void SetUART_115200_16MHz(void){
	    P1SEL |= RXD + TXD ; 			// P1.1 = RXD, P1.2=TXD
	    P1SEL2 |= RXD + TXD ; 			// P1.1 = RXD, P1.2=TXD
	    UCA0CTL1 |= UCSSEL_2; 			// SMCLK
		UCA0BR0 = 0x8A; 				// 16MHz 115200
		UCA0BR1 = 0x00; 				// 16MHz 115200
	    UCA0MCTL = UCBRS0 + UCBRS1 + UCBRS2; // Modulation UCBRSx = 7
	    UCA0CTL1 &= ~UCSWRST; 			// Enable USCI
	    UC0IE |= UCA0RXIE; 				// Enable USCI_A0 RX interrupt
}

/*! \brief Set TimerA0 Function.
 *
 *  Configures TimerA0 clock and a default
 *  period of 10000 clock units.
 *
 */
void SetTimerA0(void){
	    TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
	    CCR0 =  10000;
}

/*! \brief Ports initialization.
 *
 *  Sets the inital ports status.
 *
 */
void InitPorts(void){
	/* Pin inicialitation */
		P1DIR |= 0xFF;
		P1OUT &= 0x00;
	    P2DIR |= 0xFF;
	    P2OUT &= 0x00;
}

/*! \brief Set ADC Function.
 *
 *  Configures ADC clock, reference voltage and channel.
 *
 */
void SetADC(void){
	ADC10CTL0=SREF_1 + REFON + ADC10ON + ADC10SHT_3 ;
	ADC10CTL1=INCH_10+ ADC10DIV_3;
}

/**
 *  \brief Configures MSP430G2553 hardware.
 *
 *  Configures: watchdog, clock, UART, timers & ADC by calling
 *  the appropiate functions.
 *  Also initialize ports.
 *
 */
void ConfigMSP(){

	WDTCTL = WDTPW + WDTHOLD; // Watchdog
	InitPorts();
	SetClock_16Mhz();
//	SetUART_9600_16MHz();
	SetUART_115200_16MHz();
	SetTimerA0();
	SetADC();

    __bis_SR_register(GIE);
}
