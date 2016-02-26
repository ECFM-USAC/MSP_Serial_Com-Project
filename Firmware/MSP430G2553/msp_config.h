/*
 * msp_config.h
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

void ConfigMSP(void);

#endif /* MSP_CONFIG_H_ */
