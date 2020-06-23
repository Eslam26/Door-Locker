/*******************************************************************************************************
 *  [MODULE]      :      <TWI>                                                                         *
 *  [FILE NAME]   :      <TWI.c>                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 5, 2019>                                                                 *
 *  [Description} :      <Source file for the ATmega16 TWI driver>                                     *
 ******************************************************************************************************/

#include "TWI.h"

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  TWI_init
 *  [Description]  :  This function is responsible for initializing the TWI Driver
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void TWI_init(const TWI_configType* TWI_configStructurePtr)
{
	uint8 result = ONE;
	uint8 twbsValue = TWI_configStructurePtr->clockPrescalerConfig;
	/* getting the value of pow(4,TWBs) */
	while (twbsValue != 0) {
	        result *= 4;
	        twbsValue--;
	    }
	/* calculation of TWBR value */
    TWBR = (((F_CPU/TWI_FREQ)-16)/(2*result));

    /* Set Clock Prescaler */
    TWSR = TWI_configStructurePtr->clockPrescalerConfig;
	
    /* Configure Slave Address */
    TWAR = ((TWI_configStructurePtr->TWI_slaveAddress)<<1);

    /* Set General Call Recognition Mode Configuration */
	TWAR = (TWAR & 0b11111110) | ((TWI_configStructurePtr->generalCallRecognitionEnableModeConfig & 0x01)<<(TWGCE));

	/* Enable TWI */
    TWCR = (TWCR & 0b11111011) | ((ONE<<TWEN));
	
	/* Enable pull up resistors at SCL and SDA Pins */
	SET_BIT(PORTC,4);
	SET_BIT(PORTC,5);
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  TWI_start
 *  [Description]  :  This function is responsible for sending start bit
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void TWI_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  TWI_stop
 *  [Description]  :  This function is responsible for sending stop bit
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void TWI_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  TWI_write
 *  [Description]  :  This function is responsible for writing data
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void TWI_write(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;

    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for data is send successfully */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  TWI_readWithACK
 *  [Description]  :  This function is responsible for reading data with sending ACK
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
uint8 TWI_readWithACK(void)
{

    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for data received successfully */
    while(BIT_IS_CLEAR(TWCR,TWINT));

    /* Read Data */
    return TWDR;
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  TWI_readWithNACK
 *  [Description]  :  This function is responsible for reading data without sending ACK
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
uint8 TWI_readWithNACK(void)
{
    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for  (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));

    /* Read Data */
    return TWDR;
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  TWI_getStatus
 *  [Description]  :  This function is responsible for getting the status of TWI Driver
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
uint8 TWI_getStatus(void)
{
    uint8 status;
    /* get status bits */
    status = TWSR & 0xF8;
    return status;
}
