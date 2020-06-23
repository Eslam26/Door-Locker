/*******************************************************************************************************
 *  [MODULE]      :      <GPT>                                                                         *
 *  [FILE NAME]   :      <GPT_Cfg.h>                                                                   *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 6, 2019>                                                                 *
 *  [Description} :      <Header file for ATmega16 GPT Driver configuration>                           *
 ******************************************************************************************************/

#ifndef GPT_CFG_H_
#define GPT_CFG_H_

#define GPT_0_CHANNEL_INTIALIZED_NOT_INTIALIZED_CONFIG GPT_CHANNEL_NOT_INTIALIZED
#define GPT_0_TICKS_NUMBER_CONFIG 0
#define GPT_0_CLOCK_PRESCALER_CONFIG DEFAULT_GPT_0_CLOCK_PRESCALER_CONFIG
#define GPT_0_CONTINOUS_ONESHOT_MODE_CONFIG DEFAULT_GPT_0_CONTINOUS_ONESHOT_MODE_CONFIG

#define GPT_1_CHANNEL_INTIALIZED_NOT_INTIALIZED_CONFIG GPT_CHANNEL_INTIALIZED
#define GPT_1_TICKS_NUMBER_CONFIG 31250
#define GPT_1_CLOCK_PRESCALER_CONFIG PRESCALER_256
#define GPT_1_CONTINOUS_ONESHOT_MODE_CONFIG GPT_CH_MODE_CONTINUOUS

#define GPT_2_CHANNEL_INTIALIZED_NOT_INTIALIZED_CONFIG DEFAULT_GPT_2_CHANNEL_INTIALIZED_NOT_INTIALIZED_CONFIG
#define GPT_2_TICKS_NUMBER_CONFIG DEFAULT_GPT_2_TICKS_NUMBER_CONFIG
#define GPT_2_CLOCK_PRESCALER_CONFIG DEFAULT_GPT_2_CLOCK_PRESCALER_CONFIG
#define GPT_2_CONTINOUS_ONESHOT_MODE_CONFIG DEFAULT_GPT_2_CONTINOUS_ONESHOT_MODE_CONFIG


#endif /* GPT_CFG_H_ */
