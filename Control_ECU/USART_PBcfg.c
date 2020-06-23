/*******************************************************************************************************
 *  [MODULE]      :      <USART>                                                                       *
 *  [FILE NAME]   :      <USART_PBcfg.c>                                                               *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 5, 2019>                                                                 *
 *  [Description} :      <source file for ATmega16 USART Driver that contains the configuration struct>*
 ******************************************************************************************************/

/*--------------------------------------------INCLUDES------------------------------------------------*/
#include "USART.h"

/*----------------------------------------CONFIGURATION STRUCTURE-------------------------------------*/
USART_configType USART_configStructure = {
		USART_DOUBLE_TRANSMISSION_ENABLE_MODE_CONFIG,
		USART_MULTI_PROCESSOR_COUMMUNICATION_ENABLE_MODE_CONFIG,
		USART_RX_COMPLETE_INTERRUPT_ENABLE_MODE_CONFIG,
		USART_TX_COMPLETE_INTERRUPT_ENABLE_MODE_CONFIG,
		USART_DATA_R_EMPTY_INTERRUPT_ENABLE_MODE_CONFIG,
		USART_MODE_SELECT_CONFIG,
		USART_PATITY_MODE_CONFIG, USART_STOP_BIT_MODE_CONFIG,
		USART_CHARACTER_SIZE_CONFIG, USART_CLOCK_POLARITY_CONFIG,
		USART_BAUDRATE_VALUE_CONFIG };
