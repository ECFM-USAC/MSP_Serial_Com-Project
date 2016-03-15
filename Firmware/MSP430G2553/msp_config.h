/*
 * msp_config.h
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
 * \file msp_config.h
 * \author Hector Perez (hector@ecfm.usac.edu.gt)
 * \date Feb 23, 2016
 *
 * \brief Harware Configuration for MSP430G2553 (header file)
 *
 * Header file for msp_config.c
 *
 * \see http://www.ti.com/product/MSP430G2553/technicaldocuments
 * \see http://www.ti.com/tool/msp-exp430g2#Technical%20Documents
 */

#ifndef MSP_CONFIG_H_
#define MSP_CONFIG_H_

/* Some definitions */
/** Alias for red led pin (1.0) */
#define RD_LED BIT0
/** Alias for green led pin (1.6) */
#define GR_LED BIT6
/** Alias for hardware UART TX pin (1.2) */
#define TXD BIT2
/** Alias for hardware UART RX pin (1.1)*/
#define RXD BIT1


/* Flags definitions */
/** This flag is defined on msp_serial_com.c. */
extern volatile unsigned int RX_TRS;
/** This flag is defined on msp_serial_com.c. */
extern unsigned int SILENT_MODE;
/** This flag is defined on commands.c. */
extern unsigned int MEASUREMENT;
/** This flag is defined on msp_serial_com.c. */
extern unsigned int NUM_FORMAT;

/**
 *  \brief Configures MSP430G2553 hardware.
 *
 *  Refer to msp_config.c for
 *  more information.
 *
 */
void ConfigMSP(void);

#endif /* MSP_CONFIG_H_ */
