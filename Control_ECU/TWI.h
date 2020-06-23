/*******************************************************************************************************
 *  [MODULE]      :      <TWI>                                                                         *
 *  [FILE NAME]   :      <TWI.h>                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 5, 2019>                                                                 *
 *  [Description} :      <Header file for the ATmega16 TWI driver>                                     *
 ******************************************************************************************************/


#ifndef TWI_H_
#define TWI_H_


/*------------------------------------------INCLUDES--------------------------------------------*/
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "TWI_Cfg.h"

/*--------------------------------------------DEFINES------------------------------------------*/
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08
#define TW_REP_START     0x10
#define TW_MT_SLA_W_ACK  0x18
#define TW_MT_SLA_R_ACK  0x40
#define TW_MT_DATA_ACK   0x28
#define TW_MR_DATA_ACK   0x50
#define TW_MR_DATA_NACK  0x58

#define DEFAULT_TWI_FREQ 100000

/* Default TWI CONFIGURATIONS */
#define DEFAULT_TWI_CLOCK_PRESCALER F_OSC_1
#define DEFAULT_TWI_GENERAL_CALL_RECOGNITION_ENABLE_MODE TWI_GENERAL_CALL_RECOGNITION_ENABLE_OFF
#define DEFAULT_TWI_SLAVE_ADDRESS 0x01

#define ONE  1
#define ZERO 0

/*-----------------------------------------------ENUMS-----------------------------------------*/
typedef enum{
	F_OSC_1, F_OSC_4, F_OSC_16, F_OSC_64
}TWI_CLOCK_PRESCALER;

typedef enum{
	TWI_GENERAL_CALL_RECOGNITION_ENABLE_OFF, TWI_GENERAL_CALL_RECOGNITION_ENABLE_ON
}TWI_GENERAL_CALL_RECOGNITION_ENABLE_MODE;

/*----------------------------------------------STRUCTS----------------------------------------*/
typedef struct{
	TWI_CLOCK_PRESCALER clockPrescalerConfig;
	TWI_GENERAL_CALL_RECOGNITION_ENABLE_MODE generalCallRecognitionEnableModeConfig;
	uint8 TWI_slaveAddress;
}TWI_configType;

/*------------------------------------------FUNCTIONS PROTOTYPES-------------------------------*/
void TWI_init(const TWI_configType* TWI_configStructurePtr);
void TWI_start(void);
void TWI_stop(void);
void TWI_write(uint8 data);
uint8 TWI_readWithACK(void); //read with send Ack
uint8 TWI_readWithNACK(void); //read without send Ack
uint8 TWI_getStatus(void);


/*------------------------------------------EXTERNS------------------------------------------*/
extern TWI_configType TWI_configStructure;


#endif /* TWI_H_ */
