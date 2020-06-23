/*******************************************************************************************************
 *  [MODULE]      :      <GPT>                                                                         *
 *  [FILE NAME]   :      <GPT_PBcfg.c>                                                                 *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 6, 2019>                                                                 *
 *  [Description} :      <source file for ATmega16 GPT Driver that contains the configuration struct>  *
 ******************************************************************************************************/

#include "GPT.h"

GPT_configType GPT_configStructure = {
	CHANNEL_ID_0, GPT_0_CHANNEL_INTIALIZED_NOT_INTIALIZED_CONFIG,GPT_0_TICKS_NUMBER_CONFIG,GPT_0_CLOCK_PRESCALER_CONFIG,GPT_0_CONTINOUS_ONESHOT_MODE_CONFIG,
	CHANNEL_ID_1, GPT_1_CHANNEL_INTIALIZED_NOT_INTIALIZED_CONFIG,GPT_1_TICKS_NUMBER_CONFIG,GPT_1_CLOCK_PRESCALER_CONFIG,GPT_1_CONTINOUS_ONESHOT_MODE_CONFIG,
	CHANNEL_ID_2, GPT_2_CHANNEL_INTIALIZED_NOT_INTIALIZED_CONFIG,GPT_2_TICKS_NUMBER_CONFIG,GPT_2_CLOCK_PRESCALER_CONFIG,GPT_2_CONTINOUS_ONESHOT_MODE_CONFIG
};
