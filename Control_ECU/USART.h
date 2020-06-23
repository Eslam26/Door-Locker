/*******************************************************************************************************
 *  [MODULE]      :      <USART>                                                                       *
 *  [FILE NAME]   :      <USART.h>                                                                     *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 5, 2019>                                                                 *
 *  [Description} :      <Header file for the ATmega16 USART driver>                                   *
 ******************************************************************************************************/

#ifndef USART_H_
#define USART_H_
/*------------------------------------------INCLUDES--------------------------------------------*/

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "USART_Cfg.h"

/*-------------------------------------------DEFINES-------------------------------------------*/

#define  DEFAULT_USART_DOUBLE_TRANSMISSION_ENABLE_MODE_CONFIG USART_DOUBLE_TRANSMISSION_MODE_ENABLE_ON
#define  DEFAULT_USART_MULTI_PROCESSOR_COUMMUNICATION_ENABLE_MODE_CONFIG USART_MULTI_PROCESSOR_COUMMUNICATION_ENABLE_OFF
#define  DEFAULT_USART_RX_COMPLETE_INTERRUPT_ENABLE_MODE_CONFIG USART_RX_COMPLETE_INTERRUPT_ENABLE_OFF
#define  DEFAULT_USART_TX_COMPLETE_INTERRUPT_ENABLE_MODE_CONFIG USART_TX_COMPLETE_INTERRUPT_ENABLE_OFF
#define  DEFAULT_USART_DATA_R_EMPTY_INTERRUPT_ENABLE_MODE_CONFIG USART_DATA_R_EMPTY_INTERRUPT_ENABLE_OFF
#define  DEFAULT_USART_MODE_SELECT_CONFIG ASYNCHRONOUS_OPERATION_MODE
#define  DEFAULT_USART_PATITY_MODE_CONFIG USART_PATITY_DISABLED
#define  DEFAULT_USART_STOP_BIT_MODE_CONFIG USART_ONE_STOP_BIT
#define  DEFAULT_USART_CHARACTER_SIZE_CONFIG USART_8_BIT
#define  DEFAULT_USART_CLOCK_POLARITY_CONFIG USART_TRANSMITTED_DATA_RISING_EDGE_RECIEVED_DATA_FALLING_EDGE
#define DEFAULT_USART_BAUDRATE_VALUE_CONFIG 9600

/*--------------------------------------------ENUMS--------------------------------------------*/
typedef enum{
	USART_DOUBLE_TRANSMISSION_MODE_ENABLE_OFF, USART_DOUBLE_TRANSMISSION_MODE_ENABLE_ON
}USART_DOUBLE_TRANSMISSION_ENABLE_MODE;

typedef enum{
	USART_MULTI_PROCESSOR_COUMMUNICATION_ENABLE_OFF, USART_MULTI_PROCESSOR_COUMMUNICATION_ENABLE_ON
}USART_MULTI_PROCESSOR_COUMMUNICATION_ENABLE_MODE;

typedef enum{
	USART_RX_COMPLETE_INTERRUPT_ENABLE_OFF, USART_RX_COMPLETE_INTERRUPT_ENABLE_ON
}USART_RX_COMPLETE_INTERRUPT_ENABLE_MODE;

typedef enum{
	USART_TX_COMPLETE_INTERRUPT_ENABLE_OFF, USART_TX_COMPLETE_INTERRUPT_ENABLE_ON
}USART_TX_COMPLETE_INTERRUPT_ENABLE_MODE;

typedef enum{
	USART_DATA_R_EMPTY_INTERRUPT_ENABLE_OFF, USART_DATA_R_EMPTY_INTERRUPT_ENABLE_ON
}USART_DATA_R_EMPTY_INTERRUPT_ENABLE_MODE;

typedef enum{
	ASYNCHRONOUS_OPERATION_MODE, SYNCHRONOUS_OPERATION_MODE
}USART_MODE_SELECT;

typedef enum{
	USART_PATITY_DISABLED, USART_EVEN_PATITY=2, USART_ODD_PATITY
}USART_PATITY_MODE;

typedef enum{
	USART_ONE_STOP_BIT, USART_TWO_STOP_BITS
}USART_STOP_BIT_MODE;

typedef enum{
	USART_5_BIT, USART_6_BIT, USART_7_BIT, USART_8_BIT, USART_9_BIT=7
}USART_CHARACTER_SIZE;

typedef enum{
	USART_TRANSMITTED_DATA_RISING_EDGE_RECIEVED_DATA_FALLING_EDGE, USART_TRANSMITTED_DATA_FALLING_EDGE_RECIEVED_DATA_RISING_EDGE
}USART_CLOCK_POLARITY;

/*-------------------------------------------STRUCTS-------------------------------------------*/
typedef struct{
	USART_DOUBLE_TRANSMISSION_ENABLE_MODE doubleTransmissionModeConfig;
	USART_MULTI_PROCESSOR_COUMMUNICATION_ENABLE_MODE multiProcessorCommunicationModeConfig;
	USART_RX_COMPLETE_INTERRUPT_ENABLE_MODE rxCompleteInterruptModeConfig;
	USART_TX_COMPLETE_INTERRUPT_ENABLE_MODE txCompleteInterruptModeConfig;
	USART_DATA_R_EMPTY_INTERRUPT_ENABLE_MODE dataRegisterEmptyInterruptModeConfig;
	USART_MODE_SELECT modeSelectConfig;
	USART_PATITY_MODE parityBitModeConfig;
	USART_STOP_BIT_MODE stopBitModeConfig;
	USART_CHARACTER_SIZE characterSizeConfig;
	USART_CLOCK_POLARITY clockPolarityConfig;
	uint16 baudrateValue;
}USART_configType;

/*--------------------------------------FUNCTIONS PROTOTYPES--++++-----------------------------*/

void USART_init(const USART_configType* USART_configStructurePtr);
void USART_sendByte(const uint8 data);
uint8 USART_recieveByte(void);
void USART_TXC_setCallBack(void (*USART_UDRE_setCallBack_Ptr)(void));
void USART_RXC_setCallBack(void (*USART_UDRE_setCallBack_Ptr)(void));
void USART_UDRE_setCallBack(void (*USART_UDRE_setCallBack_Ptr)(void));



/*------------------------------------------EXTERNS------------------------------------------*/
extern USART_configType USART_configStructure;

#endif /* USART_H_ */
