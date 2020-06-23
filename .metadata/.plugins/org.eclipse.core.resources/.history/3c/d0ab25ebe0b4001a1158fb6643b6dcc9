/*******************************************************************************************************
 *  [FILE NAME]   :      <uart.h>                                                                      *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                 *
 *  [Description} :      <Header file for the USART Driver>                                            *
 ******************************************************************************************************/


#ifndef UART_H_
#define UART_H_

/*--------------------------------------INCLUDES--------------------------------------------------------*/
#include <avr/io.h>
#include "common_macros.h"
#include "std_types.h"

/*-----------------------------------------ENUMS---------------------------------------------------------*/
typedef enum{
	OFF, ON
}Uart_interrupt;

typedef enum{
	Asynchronus, Synchronous
}Uart_mode;

typedef enum{
	Disabled, Reserved, evenParity, oddParity
}Uart_parity;

typedef enum{
	_5bit, _6bit, _7bit, _8bit, _9bit=7
}Uart_characterSize;

typedef enum{
	_1bit, _2bit
}Uart_stopBit;

typedef enum{
	Rising_Transmitted_Falling_Recieved, Falling_Transmitted_Rising_Recieved
}Uart_clockPolarity;

typedef enum{
	multi_OFF, multi_ON
}Uart_multiProcessorCommunicationMode;


/*--------------------------------------Structures and Unions------------------------------------------*/

/*********************************************************************************************************
[Structure Name]        : Uart_configType
[Structure Description] :
This structure is responsible for maintaining information about initial parameters
in order to intializing the USART Driver
*********************************************************************************************************/
typedef struct{

   Uart_mode mode; /* Mode of USART Driver synchronous or Asynchrounous */
   Uart_parity parity; /* Parity Bit type mode */
   Uart_stopBit stop;  /* Number of stop Bits */
   Uart_characterSize size; /* defines the character size */
   Uart_clockPolarity clock; /* defines the clock type mode for synchronous mode only */
   Uart_interrupt interrupt; /* Interrupts mode */
   Uart_multiProcessorCommunicationMode multiMode; /* Multi-Processor Communication Mode */
   uint16 userBaudRate; /* User BaudRate */
}Uart_configType;

/*---------------------------------------FUNCTION DECLARATIONS------------------------------------------*/

void UART_init(const Uart_configType * );       /* declaration of the function that intialize the USART Driver */
void UART_sendByte(const uint8 a_data);         /* declaration of the function that transmits data */
uint8 UART_recieveByte(void);                   /* declaration of the function that recieves data */
void UART_sendString(const uint8 * a_string );  /* declaration of the function that transmits strings */
void UART_recieveString(uint8 * a_string);      /* declaration of the function that recieves strings */


#endif /* UART_H_ */
