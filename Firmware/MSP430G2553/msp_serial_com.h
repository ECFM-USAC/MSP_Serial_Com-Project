/*
 * msp_serial_com.h
 *
 *	MSP_Serial_Com Project
 *
 *	Laboratorio de instrumentacion
 *	Escuela de Ciencias Fisicas y Matematicas
 *	USAC
 *
 *	ecfm.usac.edu.gt
 *
 *  Created on: Feb 18, 2016
 *      Author: Hector
 */

#ifndef MSP_SERIAL_COM_H_
#define MSP_SERIAL_COM_H_

#define TX_BUF_SIZE 5
#define RX_BUF_SIZE 15

/* Type defs */
typedef struct {
    const char* cmd_name;
    void (*cmd_func)(char*);
    const char* cmd_help;
} command;


/* functions declarations */
void PrintStr(const char*);
void PrintStrOSM(const char*);
void PrintInt(const unsigned int);
unsigned int StrToInt(const char*);
void GetRxBuff(char*);

#endif /* MSP_SERIAL_COM_H_ */
