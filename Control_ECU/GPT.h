/*******************************************************************************************************
 *  [MODULE]      :      <GPT>                                                                         *
 *  [FILE NAME]   :      <GPT.h>                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 6, 2019>                                                                 *
 *  [Description} :      <Header file for the ATmega16 GPT driver>                                     *
 ******************************************************************************************************/

#ifndef GPT_H_
#define GPT_H_

/*------------------------------------------INCLUDES--------------------------------------------*/
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "GPT_Cfg.h"

/*--------------------------------------------DEFINES------------------------------------------*/

/* define number of timer channels */
#define NUM_TIMERS 3

/* define zero and one */
#define ZERO 0
#define ONE 1

/* default GPT Channel Configurations */
#define  DEFAULT_GPT_0_CHANNEL_INTIALIZED_NOT_INTIALIZED_CONFIG GPT_CHANNEL_INTIALIZED
#define  DEFAULT_GPT_0_TICKS_NUMBER_CONFIG 50
#define  DEFAULT_GPT_0_CLOCK_PRESCALER_CONFIG PRESCALER_8
#define  DEFAULT_GPT_0_CONTINOUS_ONESHOT_MODE_CONFIG GPT_CH_MODE_ONESHOT

#define  DEFAULT_GPT_1_CHANNEL_INTIALIZED_NOT_INTIALIZED_CONFIG GPT_CHANNEL_NOT_INTIALIZED
#define  DEFAULT_GPT_1_TICKS_NUMBER_CONFIG ZERO
#define  DEFAULT_GPT_1_CLOCK_PRESCALER_CONFIG NO_PRESCALER
#define  DEFAULT_GPT_1_CONTINOUS_ONESHOT_MODE_CONFIG GPT_CH_MODE_ONESHOT

#define  DEFAULT_GPT_2_CHANNEL_INTIALIZED_NOT_INTIALIZED_CONFIG GPT_CHANNEL_NOT_INTIALIZED
#define  DEFAULT_GPT_2_TICKS_NUMBER_CONFIG ZERO
#define  DEFAULT_GPT_2_CLOCK_PRESCALER_CONFIG NO_PRESCALER
#define  DEFAULT_GPT_2_CONTINOUS_ONESHOT_MODE_CONFIG GPT_CH_MODE_ONESHOT

#define GPT_DISABLED ZERO
#define GPT_ENABLED ONE



/*---------------------------------------------ENUMS-------------------------------------------*/


typedef uint16 GPT_TICKS_NUMBER;

typedef enum{
	 GPT_CHANNEL_NOT_INTIALIZED, GPT_CHANNEL_INTIALIZED
}GPT_CHANNEL_INTIALIZED_NOT_INTIALIZED;

typedef enum
{
	NO_PRESCALER, PRESCALER_8, PRESCALER_64, PRESCALER_256, PRESCALER_1024, PRESCALER_EXTERNAL_SOURCE_FALLING_EDGE, PRESCALER_EXTERNAL_SOURCE_RISING_EDGE
}GPT_CLOCK_PRESCALER;


typedef enum
{
	GPT_CH_MODE_CONTINUOUS,GPT_CH_MODE_ONESHOT
}GPT_CONTINOUS_ONESHOT_MODE;

typedef enum
{
	CHANNEL_ID_0, CHANNEL_ID_1, CHANNEL_ID_2
}GPT_CHANNEL_NUMBER;

typedef enum
{
	GPI_INTERRUPT_ENABLE_OFF, GPI_INTERRUPT_ENABLE_ON
}GPI_INTERRUPT_ENABLE_MODE;

/*--------------------------------------------STRUCTS------------------------------------------*/

typedef struct{

	GPT_CHANNEL_NUMBER channelNumberConfig;
	GPT_CHANNEL_INTIALIZED_NOT_INTIALIZED intializedNotIntializedConfig;
	GPT_TICKS_NUMBER ticksNumberConfig;
	GPT_CLOCK_PRESCALER clockPrescalerConfig;
	GPT_CONTINOUS_ONESHOT_MODE continousNotContinousModeConfig;

}Gpt_timerConfig;


typedef struct
{
	Gpt_timerConfig Timers_Channels[NUM_TIMERS];
}GPT_configType;

/*---------------------------------------FUNCTIONS PROTOTYPES----------------------------------*/
void GPT_init(const GPT_configType* GPT_configStructurePtr);
void GPT_enable(uint8 channelID);
void GPT_disable(uint8 channelID);
void GPT_0_setCallBack(void (*GPT_0_setCallBack_Ptr)(void));
void GPT_1_setCallBack(void (*GPT_1_setCallBack_Ptr)(void));
void GPT_2_setCallBack(void (*GPT_2_setCallBack_Ptr)(void));

/*--------------------------------------------EXTERNS---------------------------+--------------*/
extern GPT_configType GPT_configStructure;

#endif /* GPT_H_ */
