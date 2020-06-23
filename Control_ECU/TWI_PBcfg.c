/*******************************************************************************************************
 *  [MODULE]      :      <TWI>                                                                         *
 *  [FILE NAME]   :      <TWI_PBcfg.c>                                                                 *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 5, 2019>                                                                 *
 *  [Description} :      <source file for ATmega16 TWI Driver that contains the configuration struct>  *
 ******************************************************************************************************/

/*--------------------------------------------INCLUDES------------------------------------------------*/
#include "TWI.h"

/*----------------------------------------CONFIGURATION STRUCTURE-------------------------------------*/
TWI_configType TWI_configStructure = {
TWI_CLOCK_PRESCALER_CONFIG,
TWI_GENERAL_CALL_RECOGNITION_ENABLE_MODE_CONFIG,
TWI_SLAVE_ADDRESS_CONFIG };
