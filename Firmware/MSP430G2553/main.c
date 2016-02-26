/*
 * main.c
 *
 *	MSP_Serial_Com Project
 *
 *	Laboratorio de instrumentacion
 *	Escuela de Ciencias Fisicas y Matematicas
 *	USAC
 *
 *	ecfm.usac.edu.gt
 *
 *  Created on: Jan 27, 2016
 *      Author: Hector
 */


#include "msp_serial_com.h"
#include "msp_config.h"
#include "commands.h"


/* This is needed in order to avoid warnigs at compile time */
//const unsigned int CMD_NMR = CMD_NUMBER;

/* main function */
void main(void)
{

	ConfigMSP();


    while (1){
    	if( RX_TRS ) Exec_Commands( );
    	if( MEASUREMENT ) PrintMeasure();
   }

}

