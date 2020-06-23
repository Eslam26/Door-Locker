/*******************************************************************************************************
 *  [MODULE]      :      <TWI>                                                                         *
 *  [FILE NAME]   :      <TWI_Cfg.h>                                                                   *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 5, 2019>                                                                 *
 *  [Description} :      <Header file for ATmega16 TWI Driver configuration>                           *
 ******************************************************************************************************/

#ifndef TWI_CFG_H_
#define TWI_CFG_H_

/*-------------------------------------------DEFINES--------------------------------------------------*/

/* TWI FREQUENCY */
#define TWI_FREQ 400000

#define TWI_CLOCK_PRESCALER_CONFIG F_OSC_1
#define TWI_GENERAL_CALL_RECOGNITION_ENABLE_MODE_CONFIG TWI_GENERAL_CALL_RECOGNITION_ENABLE_OFF
#define TWI_SLAVE_ADDRESS_CONFIG 0x01


#endif /* TWI_CFG_H_ */
