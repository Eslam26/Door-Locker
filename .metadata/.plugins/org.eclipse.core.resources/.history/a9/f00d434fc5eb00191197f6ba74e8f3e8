/*******************************************************************************************************
 *  [FILE NAME]   :      <external_eeprom.h>                                                           *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                 *
 *  [Description} :      <header file for EEPROM>                                                      *
 ******************************************************************************************************/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

/*-------------------------------INCLUDES--------------------------------------*/
#include "std_types.h"


/*-----------------------------Preprocessor Macros-----------------------------*/

#define ERROR 0     /* defines ERROR state as 0   */
#define SUCCESS 1   /* defines SUCCESS state as 1 */


/*------------------------------Functions Prototypes---------------------------*/

void EEPROM_init(void);   /* declaration of the function that intializes the EEPROM */
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data); /* declaration of the function that writes data into the memory */
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data); /* declaration of the function that read data from the memory   */

#endif /* EXTERNAL_EEPROM_H_ */
