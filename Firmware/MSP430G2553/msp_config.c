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

#include "msp430g2553.h"
#include "msp_config.h"

void SetClock_16Mhz(void){
	/* Clock at 16 MHz */
		BCSCTL1 = CALBC1_16MHZ;
	    DCOCTL = CALDCO_16MHZ;
}

void SetUART_9600_16MHz(void){
	/* UART setup */
	    P1SEL |= RXD + TXD ; 			// P1.1 = RXD, P1.2=TXD
	    P1SEL2 |= RXD + TXD ; 			// P1.1 = RXD, P1.2=TXD
	    UCA0CTL1 |= UCSSEL_2; 			// SMCLK
		UCA0BR0 = 0x82; 				// 16MHz 9600
		UCA0BR1 = 0x06; 				// 16MHz 9600
	    UCA0MCTL = UCBRS1 + UCBRS2; 	// Modulation UCBRSx = 6
	    UCA0CTL1 &= ~UCSWRST; 			// Enable USCI
	    UC0IE |= UCA0RXIE; 				// Enable USCI_A0 RX interrupt
}

void SetUART_115200_16MHz(void){
	/* UART setup */
	    P1SEL |= RXD + TXD ; 			// P1.1 = RXD, P1.2=TXD
	    P1SEL2 |= RXD + TXD ; 			// P1.1 = RXD, P1.2=TXD
	    UCA0CTL1 |= UCSSEL_2; 			// SMCLK
		UCA0BR0 = 0x8A; 				// 16MHz 115200
		UCA0BR1 = 0x00; 				// 16MHz 115200
	    UCA0MCTL = UCBRS0 + UCBRS1 + UCBRS2; // Modulation UCBRSx = 7
	    UCA0CTL1 &= ~UCSWRST; 			// Enable USCI
	    UC0IE |= UCA0RXIE; 				// Enable USCI_A0 RX interrupt
}

void SetTimerA(void){
	/* Timer inicialitation */
	    TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
	    CCR0 =  10000;
}

void InitPorts(void){
	/* Pin inicialitation */
		P1DIR |= 0xFF;
		P1OUT &= 0x00;
	    P2DIR |= 0xFF;
	    P2OUT &= 0x00;
}

void SetADC(void){
	ADC10CTL0=SREF_1 + REFON + ADC10ON + ADC10SHT_3 ;
	ADC10CTL1=INCH_10+ ADC10DIV_3;
}

void ConfigMSP(){

	WDTCTL = WDTPW + WDTHOLD; // Watchdog
	InitPorts();
	SetClock_16Mhz();
//	SetUART_9600_16MHz();
	SetUART_115200_16MHz();
	SetTimerA();
	SetADC();

    __bis_SR_register(GIE);
}
