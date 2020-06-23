/*******************************************************************************************************
 *  [MODULE]      :      <USART>                                                                       *
 *  [FILE NAME]   :      <USART.c>                                                                     *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 5, 2019>                                                                 *
 *  [Description} :      <Source file for the ATmega16 USART driver>                                   *
 ******************************************************************************************************/

/*------------------------------------------INCLUDES--------------------------------------------------*/
#include "USART.h"

/*-------------------------------------------DEFINES--------------------------------------------------*/
#define NULL_PTR ((void*)0)

/*------------------------------------------GLOBAL VARIABLES------------------------------------------*/
static volatile void (*	g_USART_TXC_callBackPtr)(void) = NULL_PTR;
static volatile void (*	g_USART_RXC_callBackPtr)(void) = NULL_PTR;
static volatile void (*	g_USART_UDRE_callBackPtr)(void) = NULL_PTR;

/*----------------------------------------------ISR---------------------------------------------------*/
ISR(USART_RXC_vect){
	if (g_USART_RXC_callBackPtr != NULL_PTR) {
			(*g_USART_RXC_callBackPtr)();
	}
}

ISR(USART_TXC_vect){
	if (g_USART_TXC_callBackPtr != NULL_PTR) {
			(*g_USART_TXC_callBackPtr)();
	}
}

ISR(USART_UDRE_vect){
	if (g_USART_UDRE_callBackPtr != NULL_PTR) {
			(*g_USART_UDRE_callBackPtr)();
	}
}

/*-----------------------------------Functions Definitions--------------------------------------------*/

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  USART_init
 *  [Description]  :  This function is responsible for sending a byte
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void USART_init(const USART_configType* USART_configStructurePtr)
{

	uint16 UBRR_registerValue = 0;
	/* Set the double transmission mode configuration */
	UCSRA = (UCSRA & 0b11111101) | (( USART_configStructurePtr->doubleTransmissionModeConfig & 0b00000001)<<(U2X));

	/* Set the multi processor communication mode configuration */
	UCSRA = (UCSRA & 0b11111110) | (( USART_configStructurePtr->multiProcessorCommunicationModeConfig & 0b00000001)<<(MPCM));


	/* Set RX Complete Interrupt Mode Configuration */
	UCSRB = (UCSRB & 0b01111111) | (( USART_configStructurePtr->rxCompleteInterruptModeConfig & 0b00000001)<<(RXCIE));

	/* Set TX Complete Interrupt Mode Configuration */
	UCSRB = (UCSRB & 0b10111111) | (( USART_configStructurePtr->txCompleteInterruptModeConfig & 0b00000001)<<(TXCIE));
	/* Set Data Register Empty Interrupt Mode Configuration */
	UCSRB = (UCSRB & 0b11011111) | (( USART_configStructurePtr->dataRegisterEmptyInterruptModeConfig & 0b00000001)<<(UDRIE));

	/* Set the character size configuration */
	UCSRB = (UCSRB & 0b11111011) | ((( USART_configStructurePtr->characterSizeConfig & 0b00000100)>>2)<<(UCSZ2));

	/* Enable Tx and Rx */
	UCSRB = (UCSRB & 0b11101111) | ((1)<<(RXEN));
	UCSRB = (UCSRB & 0b11110111) | ((1)<<(TXEN));
	

	UCSRC = (UCSRC & 0b01111111) | ((1)<<(URSEL));

	/* Set USART mode Configuration */
	UCSRC = (UCSRC & 0b10111111) | (( USART_configStructurePtr->modeSelectConfig & 0b00000001)<<(UMSEL));

	/* Set Parity mode Configuration */
	UCSRC = (UCSRC & 0b11001111) | (( USART_configStructurePtr->parityBitModeConfig & 0b00000011)<<(UPM0));

	/* Set Stop bit mode configuration */
	UCSRC = (UCSRC & 0b11110111) | (( USART_configStructurePtr->stopBitModeConfig & 0b00000001)<<(USBS));

	/* Set the character size configuration */
	UCSRC = (UCSRC & 0b11111001) | (( USART_configStructurePtr->characterSizeConfig & 0b00000011)<<(UCSZ0));

	/* Set the clock polarit configuration */
	UCSRC = (UCSRC & 0b11111110) | (( USART_configStructurePtr->clockPolarityConfig & 0b00000001)<<(UCPOL));
	
	/* Calculate UBRR Value */
	if(USART_configStructurePtr->modeSelectConfig == SYNCHRONOUS_OPERATION_MODE){
		UBRR_registerValue = (((F_CPU / ( USART_configStructurePtr->baudrateValue* 2UL))) - 1);
	}
	else if(USART_configStructurePtr->modeSelectConfig == ASYNCHRONOUS_OPERATION_MODE){
		if(USART_configStructurePtr->doubleTransmissionModeConfig == USART_DOUBLE_TRANSMISSION_MODE_ENABLE_OFF)
		{
			UBRR_registerValue = (((F_CPU / ( USART_configStructurePtr->baudrateValue* 16UL))) - 1);
		}
		else if(USART_configStructurePtr->doubleTransmissionModeConfig == USART_DOUBLE_TRANSMISSION_MODE_ENABLE_ON){
			UBRR_registerValue = (((F_CPU / ( USART_configStructurePtr->baudrateValue* 8UL))) - 1);
		}
		else
		{

		}
	}
	else
	{

	}

	/* Set UBRR value */
	UBRRH = UBRR_registerValue>>8;
	UBRRL = UBRR_registerValue;
}
	
/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  USART_sendByte
 *  [Description]  :  This function is responsible for sending a byte
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void USART_sendByte(const uint8 data)
{
	/* Wait for Tx buffer (UDR) is empty */

	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR = data;

}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  USART_recieveByte
 *  [Description]  :  This function is responsible for sending a byte
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
uint8 USART_recieveByte(void)
{
	/* Wait for received data */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

    return UDR;		
}


/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  USART_TXC_setCallBack
 *  [Description]  :  This function is responsible for getting the address of the function which
 *  					will be executed when USART TXC is set
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void USART_TXC_setCallBack(void (*USART_TXC_setCallBack_Ptr)(void)) {
	g_USART_TXC_callBackPtr = USART_TXC_setCallBack_Ptr;
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  USART_RXC_setCallBack
 *  [Description]  :  This function is responsible for getting the address of the function which
 *  					will be executed when USART RXC is set
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void USART_RXC_setCallBack(void (*USART_RXC_setCallBack_Ptr)(void)) {
	g_USART_RXC_callBackPtr = USART_RXC_setCallBack_Ptr;
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  USART_UDRE_setCallBack
 *  [Description]  :  This function is responsible for getting the address of the function which
 *  					will be executed when UDR register is empty
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void USART_UDRE_setCallBack(void (*USART_UDRE_setCallBack_Ptr)(void)) {
	g_USART_UDRE_callBackPtr = USART_UDRE_setCallBack_Ptr;
}
