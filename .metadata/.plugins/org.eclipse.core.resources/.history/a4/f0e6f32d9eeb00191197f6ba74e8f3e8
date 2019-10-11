/*******************************************************************************************************
 *  [FILE NAME]   :      <uart.c>                                                                      *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                 *
 *  [Description} :      <Source file for the USART Driver>                                            *
 ******************************************************************************************************/

/*------------------------------------------INCLUDES--------------------------------------------------*/

#include "uart.h"   /* include the header file for the USART Driver */
/*------------------------------------STATIC FUNCTIONS DECLARATIONS-----------------------------------*/

/* Declaration of the function that calculates the UBRR value */
static uint16 getUBRRvalue(const Uart_configType * configType_Ptr);
/*------------------------------------FUNCTIONS DEFINITIONS-------------------------------------------*/

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  UART_init
 [Description]  :  This function is responsible for initializing UART
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void UART_init(const Uart_configType * configType_Ptr)
{
	uint16 baudPrescale; /* variable to store the value of baudPrescale */

	     /* UCSRA Register
	     * -------------------------------------------------
	     * | RXC | TXC | UDRE | FE | DOR | PE | U2X | MPCM |
	     * -------------------------------------------------
	     * RXC  : Recieve Complete Flag
     	 * TXC  : Transmit Complete Flag
	     * UDRE : indicates the transmit buffer is ready to recieve new data
     	 * FE   : Frame Error
     	 * DOR  : Data Overrun Error
	     * PE   : Parity Error
	     * U2X  : Double Transmission speed
	     * MPCM : Multi-Processor Communication Mode
	     */
	/* set up U2X Mode */
	UCSRA = (UCSRA & 0b11111101) | ((!(configType_Ptr->mode) & 0b00000001)<<U2X);
	/* set up  Multi-Processor Communication Mode */
	UCSRA = (UCSRA & 0b11111110) | ((configType_Ptr->multiMode & 0b00000001)<<MPCM);

	     /* UCSRB Register
		 * -------------------------------------------------------------
		 * | RXCIE | TXCIE | UDRIE | RXEN | TXEN | UCSZ2 | RXB8 | TXB8 |
		 * -------------------------------------------------------------
		 * RXCIE   : setting this bit enables interrupt on the RXC Flag
		 * TXCIE   : setting this bit enables interrupt on the TXC Flag
		 * UDRIE   : setting this bit enables interrupt on the UDRE Flag
		 * RXEN    : setting this bit enables the USART Reciever
		 * TXEN    : setting this bit enables the USART Transmitter
		 * UCSZ2   : bits combined with UCSZ: to set the character size
		 * RXB8    : is the ninth data bit of the recieved character ( 9 bits mode )
		 * TXB8    : is the ninth data bit in the character to be transmitted (9 bits mode )
	     */

	UCSRB = (UCSRB & 0b00011111) | ((configType_Ptr->interrupt & 0b00000001)<<UDRIE);
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRB = (UCSRB & 0b11111011) | (((configType_Ptr->size   & 0b00000100)>>2)<<UCSZ2);
	         /* UCSRC Register
			 * --------------------------------------------------------------
			 * | URSEL | UMSEL | UPM1 | UPM0 | USBS | UCSZ1 | UCSZ0 | UCPOL |
			 * --------------------------------------------------------------
			 * URSEL  : This bit selects between accessing USCRC or the UBRRH Register
			 * UMSEL  : this bit selects between Asynchronous and synchronous mode
			 * UPM1:0 : these bits helps you choose parity bit type
			 * USBS   : this bits helps you choose the number of stop bits for your frame
			 * UCPOL  : this bit sets the relationship between the data output change and data input sample
		     */

	UCSRC = (1<<URSEL) ;
	UCSRC = (UCSRC & 0b10111111) | ((configType_Ptr->mode   & 0b00000001)<<UMSEL);
	UCSRC = (UCSRC & 0b11001111) | ((configType_Ptr->parity & 0b00000011)<<UPM0);
    UCSRC = (UCSRC & 0b11110111) | ((configType_Ptr->stop   & 0b00000001)<<USBS);
    UCSRC = (UCSRC & 0b11111001) | ((configType_Ptr->size   & 0b00000011)<<UCSZ0);
    UCSRC = (UCSRC & 0b11111110) | ((configType_Ptr->clock  & 0b00000001)<<UCPOL);

    /* getting value of UBRR Register and store it in baudPrescale variable */
    baudPrescale = getUBRRvalue(configType_Ptr);
    /* writing the value of UBRR in UBRR Register */
    UBRRH = baudPrescale>>8;
    UBRRL = baudPrescale;

}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  UART_sendByte
 [Description]  :  This function is responsible for sending data
 [Args]
 [in]           :  const uint8 a_data
 	 	 	 	 	 this arg shall indicates the data which will be sent through UART
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void UART_sendByte(const uint8 a_data)
{
	UDR = a_data;  /* writing the data which will be sent in the UDR Register */
    while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
    SET_BIT(UCSRA,TXC); // Clear the TXC flag
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  UART_recieveByte
 [Description]  :  This function is responsible for recieving data
 [Returns]      :  This function returns uint8 variable which is the data is being recieved
 ----------------------------------------------------------------------------------------------------*/
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this
		 * flag is set to one */
		while(BIT_IS_CLEAR(UCSRA,RXC)){}
		/* Read the received data from the Rx buffer (UDR) and the RXC flag
		   will be cleared after read this data */
	    return UDR;
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  UART_sendString
 [Description]  :  This function is responsible for sending String through USART
 [Args]
 [in]           :  const uint8 * a_string
 	 	 	 	 	 this arg shall indicates the address of the string that will be sent
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void UART_sendString(const uint8 * a_string )
{
	while(*a_string != '\0')  /* looping until the end of the string */
		{
			UART_sendByte(*a_string);
			a_string++; /* increment the pointer by one to pointer to the next byte in the string */
		}
}

/*-----------------------------------------------------------------------------------------------------------------
 [Function Name]:  UART_recieveString
 [Description]  :  This function is responsible for recieving String
 [in]           :  const uint8 * a_string
 	 	 	 	 	 this arg shall indicates the address of the array that the recieved data will be stored in it
 [Returns]      :  This function returns void
 -----------------------------------------------------------------------------------------------------------------*/
void UART_recieveString(uint8 * a_string)
{
	    uint8 i = 0; /* variable used as counter */
	    /* recieving first byte of the string and store it in the first location in the array */
		a_string[i] = UART_recieveByte();
		/* looping umtil reaching the special character */
		while(a_string[i] != '$')
		{
			i++;
			a_string[i] = UART_recieveByte();
		}
		a_string[i] = '\0';
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  getUBRRvalue
 [Description]  :  This function is responsible for getting the UBRR value regarding the user BaudRate
 [Returns]      :  This function returns UBRR register value
  ----------------------------------------------------------------------------------------------------*/
static uint16 getUBRRvalue(const Uart_configType * configType_Ptr)
{
	if(!(configType_Ptr->mode))
	{
		if(BIT_IS_SET(UCSRA, U2X))
			{
				return (((F_CPU / ((configType_Ptr->userBaudRate) * 8UL))) - 1);
			}
		else
		{
				return (((F_CPU / ((configType_Ptr->userBaudRate) * 16UL))) - 1);
		}

	}
	else
	{
		return (((F_CPU / ((configType_Ptr->userBaudRate) * 2UL))) - 1);
	}

}
