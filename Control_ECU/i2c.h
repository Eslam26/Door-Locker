/*******************************************************************************************************
 *  [FILE NAME]   :      <i2c.h>                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                 *
 *  [Description} :      <header file for I2C Driver>                                                  *
 ******************************************************************************************************/

/*--------------------------------------INCLUDES--------------------------------------------------------*/
#include <avr/io.h>
#include "common_macros.h"
#include "std_types.h"


/*-------------------------------------Preprocessor Macros-----------------------------------------------*/
#define TW_START         0x08 // start has been sent
#define TW_REP_START     0x10 // repeated start
#define TW_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define TW_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave

/*-----------------------------------------ENUMS---------------------------------------------------------*/

typedef enum{
	Prescaler_1, Prescaler_4, Prescaler_16, Prescaler_64
}I2C_prescaler;

typedef enum{
	OFF, ON
}I2C_generalCallRecognition;
/*--------------------------------------Structures and Unions------------------------------------------*/
/*********************************************************************************************************
[Structure Name]        : I2C_configType
[Structure Description] :
This structure is responsible for maintaining information about initial parameters
in order to intializing the Two Wire Interface Driver
*********************************************************************************************************/
typedef struct{
	I2C_prescaler prescaler;                             /* prescaler of the frequency */
	uint8 valueTWBR;                                     /* value of the TWBR register */
	uint8 address;                                       /* address of the device      */
	I2C_generalCallRecognition generalCallRecognition;   /* genaral call recognition mode setup */

}I2C_configType;
/*---------------------------------------FUNCTION DECLARATIONS------------------------------------------*/

void TWI_init(const I2C_configType *); /* declaration of the function that intializes TWI driver */
void TWI_start(void);                  /* declaration of the function that creates start bit */
void TWI_stop(void);                   /* declaration of the function that creates stop bit */
void TWI_write(uint8 data);            /* declaration of the function that writes data */
uint8 TWI_readWithACK(void);           /* declaration of the function that reads data with sending ACK */
uint8 TWI_readWithNACK(void);          /* declaration of the function that reads data without sending ACK */
uint8 TWI_getStatus(void);             /* declaration of the function that gets the status of the TWI driver */
