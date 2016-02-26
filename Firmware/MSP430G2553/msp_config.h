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
 *      Author: Hector
 */

#ifndef MSP_CONFIG_H_
#define MSP_CONFIG_H_

/* Some definitions */
#define RD_LED BIT0
#define GR_LED BIT6
#define TXD BIT2
#define RXD BIT1


/* Flags definitions */
extern volatile unsigned int RX_TRS;
extern unsigned int SILENT_MODE;
extern unsigned int MEASUREMENT;
extern unsigned int NUM_FORMAT;

void ConfigMSP(void);

#endif /* MSP_CONFIG_H_ */
