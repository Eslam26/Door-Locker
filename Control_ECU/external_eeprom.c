/*******************************************************************************************************
 *  [FILE NAME]   :      <external_eeprom.c>                                                           *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                 *
 *  [Description} :      <Source file for EEPROM>                                                      *
 ******************************************************************************************************/

/*--------------------------------------INCLUDES--------------------------------------------------------*/
#include "TWI.h"              /* include the header file for the TWI driver */
#include "external_eeprom.h"  /* include the header file for the external eeprom memory */

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  EEPROM_init
 [Description]  :  This function is responsible for initializing EEPROM
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void EEPROM_init(void)
{
	/* initialize the I2C(TWI) module inside the MC */
	TWI_init(&TWI_configStructure);    /* passing the address of this structure in order to intialize the TWi Driver */
}

/*-------------------------------------------------------------------------------------------------------------------------------
 [Function Name]:  EEPROM_writeByte
 [Description]  :  This function is responsible for writing data in EEPROM
 [Args]
 [In]           :  uint16 a_u16addr
						this arg shall indicates the address of the location in the memory that tha data will be written in it
			       uint8 a_u8data
			       	   	this arg shall indicates the data that will be written in the memory
 [Returns]      :  This function returns state of the writing operation SUCCESS or ERROR
 ------------------------------------------------------------------------------------------------------------------------------*/

uint8 EEPROM_writeByte(uint16 a_u16addr, uint8 a_u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TW_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_write((uint8)(0xA0 | ((a_u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    TWI_write((uint8)(a_u16addr));
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;

    /* write byte to eeprom */
    TWI_write(a_u8data);
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}

/*-----------------------------------------------------------------------------------------------------------------------------------
 [Function Name]:  EEPROM_readByte
 [Description]  :  This function is responsible for reading data from EEPROM
 [Args]
 [In]           :  uint16 a_u16addr
						this arg shall indicates the address of the location in the memory that tha data will be read from
			       uint8 * a_u8data
			       	   	this arg shall indicates the address of the variable that will store the data that will be read from memory
 [Returns]      :  This function returns state of the writing operation SUCCESS or ERROR
 ------------------------------------------------------------------------------------------------------------------------------------*/
uint8 EEPROM_readByte(uint16 a_u16addr, uint8 *a_u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TW_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_write((uint8)((0xA0) | ((a_u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    TWI_write((uint8)(a_u16addr));
    if (TWI_getStatus() != TW_MT_DATA_ACK)
        return ERROR;

    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TW_REP_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_write((uint8)((0xA0) | ((a_u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TW_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *a_u8data = TWI_readWithNACK();
    if (TWI_getStatus() != TW_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();
    return SUCCESS;
}
