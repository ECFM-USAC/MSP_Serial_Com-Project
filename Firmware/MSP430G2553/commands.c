/*
 * commands.c
 *
 *	MSP_Serial_Com Project
 *
 *	Laboratorio de instrumentacion
 *	Escuela de Ciencias Fisicas y Matematicas
 *	USAC
 *
 *	ecfm.usac.edu.gt
 *
 *  Created on: 25/02/2016
 *      Author: hepf
 */

#include "string.h"
#include "msp430g2553.h"
#include "msp_serial_com.h"
#include "msp_config.h"
#include "commands.h"

/* Globals */
unsigned int GRL_STATUS = 0;
unsigned int BLK_STATUS = 0;
unsigned int TMS_STATUS = 0;
unsigned int TIMER_A_SELECT = 0;
unsigned int msec_counter = 0;
unsigned int sec_counter = 0;
unsigned int T_MEAS = 1;
unsigned int MEASUREMENT = 0;
unsigned int MEASURE;

/* functions for commands */
void Show_help(char*);
void Silent_Mode_Select(char *);
void Green_led_func(char *);
void Red_led_func(char *);
void Read_Temp(char *);
void Num_Format_Select(char *);

/* Number of commands */
#define CMD_NUMBER 6

/* Commands table */
const command COMMAND_LIST[ CMD_NUMBER ] = {
		{"NF", Num_Format_Select, "NF n\tn={0|1}; Set numeric format: 0 - hex; 1 - dec. "},
		{"TM", Read_Temp, "TM n m\tn={0|1}; turn off (0) or on (1) measuremenst from on board\
				\n\ttemperature senson with period T = m secs. (0 < m < 65535)"},
		{"RL", Red_led_func, "RL n m\tn={0|1}; turn off (0) or on (1) on board red led\n\tblinkin with period T = m*62.5 ns. (0 < m < 65535)"},
		{"GL", Green_led_func, "GL n\tn={0|1}; Turn off (0) or on (1) on board green led"},
		{"SM", Silent_Mode_Select, "SM n\tSilent mode select:\
				\n\tn=0\tDisable. Keyboard feedback and all messages are show.\
				\n\tn=1\tNo keyboard feedback. Commands responses are show until \\n is sent.\
				\n\tn=2\tOnly prints numerical values (PrintHex, PrintDec) and strings\n\t\tfrom PrintStrOSM func."},
		{"HL", Show_help, "HL\tShow commands help"}
};


/* Other functions */
void PrintMeasure(void);

void Exec_Commands(void){
	char Rcv_Cmd[ RX_BUF_SIZE ];
	unsigned int CMD = 0;
	char *token;
	 GetRxBuff(Rcv_Cmd);
	token = strtok(Rcv_Cmd," ");
	unsigned int i = CMD_NUMBER;
	while(i--){
		if ( !strcmp( token, COMMAND_LIST[ i ].cmd_name ) ){
		token = strtok( NULL, " ");
		COMMAND_LIST[ i ].cmd_func(token);
		CMD = 1;
		}
	}
	if( !CMD ) PrintStr( "> Invalid command\n" );
	RX_TRS = 0;
}


void Show_help(char *arg){
	unsigned int i = CMD_NUMBER;
	PrintStr( "\nCommands avaible:\n" );
	while( i-- ){
		PrintStr( "\n" );
		PrintStr( COMMAND_LIST[ i ].cmd_help );
	}
	PrintStr( "\n\n" );
}

void Silent_Mode_Select(char *arg){
	unsigned int CMD_OK = 0;
	switch( arg[0] ){
	case '0':
		SILENT_MODE = 0;
		CMD_OK = 1;
		break;
	case '1':
		SILENT_MODE = 1;
		CMD_OK = 1;
		break;
	case '2':
		SILENT_MODE = 2;
		CMD_OK = 1;
		break;
	}
	if ( CMD_OK )
		PrintStr( "> OK\n" );
	else
		PrintStr( "> Invalid argument\n" );
}

void Green_led_func(char *arg){
	unsigned int CMD_OK = 0;
	switch( arg[0] ){
	case '0':
		if (GRL_STATUS){
			P1OUT &= ~GR_LED;
			GRL_STATUS = 0;
			CMD_OK = 1;
		} else CMD_OK = 2;
		break;
	case '1':
		if (!GRL_STATUS){
			P1OUT |= GR_LED;
			GRL_STATUS = 1;
			CMD_OK = 1;
		}  else CMD_OK = 2;
		break;
	}
	switch ( CMD_OK ){
	case 0:
		PrintStr( "> Invalid argument\n" );
		break;
	case 1:
		PrintStr( "> OK\n" );
		break;
	case 2:
		PrintStr( "> No change\n" );
		break;
	}
}


void Red_led_func(char *arg){
	char *token;
	unsigned int Period;
	unsigned int CMD_OK = 0;
	switch( arg[0] ){
	case '0':
		if (BLK_STATUS){
			CCTL0 &= ~CCIE;
			BLK_STATUS = 0;
			P1OUT &= ~RD_LED;
			CMD_OK = 1;
		} else CMD_OK = 2;
		break;
	case '1':
		if (!BLK_STATUS && !TMS_STATUS ){
			token = strtok( NULL, " ");
			Period = StrToInt( token );
			if( Period ){
			    CCR0 =  Period;
				BLK_STATUS = 1;
				TIMER_A_SELECT = 0;
				CCTL0 |= CCIE;
				CMD_OK = 1;
			} else CMD_OK = 0;
		}  else CMD_OK = 2;
		break;
	}
	switch ( CMD_OK ){
	case 0:
		PrintStr( "> Invalid argument\n" );
		break;
	case 1:
		PrintStr( "> OK\n" );
		break;
	case 2:
		PrintStr( "> Timer Busy\n" );
		break;
	}
}

void PrintMeasure(void){
	PrintInt( MEASURE );
	PrintStrOSM("\n");
	MEASUREMENT = 0;
}

void Read_Temp(char *arg){
	char *token;
	unsigned int CMD_OK = 0;
	switch( arg[0] ){
	case '0':
		if ( TMS_STATUS ){
			CCTL0 &= ~CCIE;
			TMS_STATUS = 0;
			CMD_OK = 1;
		} else CMD_OK = 2;
		break;
	case '1':
		if ( !TMS_STATUS && !BLK_STATUS ){
			token = strtok( NULL, " ");
			T_MEAS = StrToInt( token );
			if( T_MEAS ){
			    CCR0 = 2000;
				TMS_STATUS = 1;
				TIMER_A_SELECT = 1;
				msec_counter = 1000;
				sec_counter = T_MEAS;
				CCTL0 |= CCIE;
				CMD_OK = 1;
			} else CMD_OK = 0;
		}  else CMD_OK = 2;
		break;
	}
	switch ( CMD_OK ){
	case 0:
		PrintStr( "> Invalid argument\n" );
		break;
	case 1:
		PrintStr( "> OK\n" );
		break;
	case 2:
		PrintStr( "> Timer busy\n" );
		break;
	}
}

void Num_Format_Select(char *arg){
	unsigned int CMD_OK = 0;
	switch( arg[0] ){
	case '0':
		NUM_FORMAT = 0;
		CMD_OK = 1;
		break;
	case '1':
		NUM_FORMAT = 1;
		CMD_OK = 1;
		break;
	}
	if ( CMD_OK ) PrintStr( "> OK\n" );
	else PrintStr( "> Invalid argument\n" );
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	switch( TIMER_A_SELECT ){
		case 0:
			P1OUT ^= RD_LED;  // Toggle P1.0
			break;
		case 1:
			msec_counter--;
			if ( !msec_counter ){
				sec_counter--;
				msec_counter = 1000;
				if ( !sec_counter ){
					ADC10CTL0 |= ENC + ADC10SC;      //enable conversion and start conversion
					while(ADC10CTL1 & BUSY);         //wait..i am converting..pum..pum..
					MEASURE = ( ADC10MEM - 673 )*423 /1024;                       //store val in t
					ADC10CTL0 &= ~ENC;                     //disable adc conv
					sec_counter = T_MEAS;
					MEASUREMENT = 1;
				}
			}

			break;
	}
 }
