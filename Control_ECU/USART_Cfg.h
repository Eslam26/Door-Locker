/*******************************************************************************************************
 *  [MODULE]      :      <USART>                                                                       *
 *  [FILE NAME]   :      <USART_Cfg.h>                                                                 *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 5, 2019>                                                                 *
 *  [Description} :      <Header file for ATmega16 USART Driver configuration>                         *
 ******************************************************************************************************/

#ifndef USART_CFG_H_
#define USART_CFG_H_

/*-------------------------------------------DEFINES--------------------------------------------------*/


#define USART_DOUBLE_TRANSMISSION_ENABLE_MODE_CONFIG USART_DOUBLE_TRANSMISSION_MODE_ENABLE_OFF
#define USART_MULTI_PROCESSOR_COUMMUNICATION_ENABLE_MODE_CONFIG USART_MULTI_PROCESSOR_COUMMUNICATION_ENABLE_OFF
#define USART_RX_COMPLETE_INTERRUPT_ENABLE_MODE_CONFIG USART_RX_COMPLETE_INTERRUPT_ENABLE_OFF
#define USART_TX_COMPLETE_INTERRUPT_ENABLE_MODE_CONFIG USART_TX_COMPLETE_INTERRUPT_ENABLE_OFF
#define USART_DATA_R_EMPTY_INTERRUPT_ENABLE_MODE_CONFIG USART_DATA_R_EMPTY_INTERRUPT_ENABLE_OFF
#define USART_MODE_SELECT_CONFIG ASYNCHRONOUS_OPERATION_MODE
#define USART_PATITY_MODE_CONFIG USART_PATITY_DISABLED
#define USART_STOP_BIT_MODE_CONFIG USART_TWO_STOP_BITS
#define USART_CHARACTER_SIZE_CONFIG USART_8_BIT
#define USART_CLOCK_POLARITY_CONFIG USART_TRANSMITTED_DATA_RISING_EDGE_RECIEVED_DATA_FALLING_EDGE
#define USART_BAUDRATE_VALUE_CONFIG 9600

#endif /* USART_CFG_H_ */
