/************************************************************************************************************************
 *  [FILE NAME]   :      <main.c>                                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                                              *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                                  *
 *  [Description} :      <Source file for the CONTROL_ECU>                                                              *
 ************************************************************************************************************************/

/*------------------------------------------------------INCLUDES-------------------------------------------------------------------------*/
#include "micro_config.h"
#include "main.h"
#include "USART.h"
#include "GPT.h"
#include "external_eeprom.h"


/*------------------------------------------------FUNCTIONS DECLARATIONS------------------------------------------------------------------*/

uint8 recieveData(void);                                 /* declaration of the function that recieve data from HMI_ECU */
void passwordCreation(void);                             /* declaration of the function that creates a new password    */
void passwordConfirmation(void);                         /* declaration of the function that match the rentered password with the first one */
void savePassword (uint8 * a_pass);                      /* declaration of the function that save the new password in the EEPROM */
void comparingWithSavedPassword (void);                  /* declaration of the function that compare the requested password with the saved one in the EEPROM */
void openCloseDoor(void);                                /* declaration of the function that opens and closes the door */
void buzzer(void);                                       /* declaration of the function that turns on and off the buzzer */
void calledBackFunction (void);                          /* declaration of the function that will be called by Timer 1 when performs its ISR */

/*-------------------------------------------------GLOBAL VARIABLES-----------------------------------------------------------------------*/
uint8 g_password[6] = { 0 };                             /* array that stores the sent passowrd form HMI_ECU */
uint8 g_data;                                            /* variable to store the recieved data */
uint8 g_counter = 0;                                     /* variable acts as seconds counter */
uint8 g_errorCounter;                                    /* counter for incorrect password entered */

/*--------------------------------------------------STRUCTURES----------------------------------------------------------------------------*/

int main() {

	/*
	 * setting motor and buzzer pins as outputs
	 */
	SET_BIT(MOTOR_PORT_DIRECTION,MOTOR_IN1);
	SET_BIT(MOTOR_PORT_DIRECTION,MOTOR_IN2);
	SET_BIT(MOTOR_PORT_DIRECTION,MOTOR_EN);
	SET_BIT(BUZZER_PORT_DIRECTION,BUZZER_PIN);

	/* Enable Global Interrupts */
	SREG = (1<<7);
	/* initialize GPT driver */

	GPT_init(&GPT_configStructure);
	/* set GPT_0 callBack Function */
	GPT_1_setCallBack(calledBackFunction);

	USART_init(&USART_configStructure);        /*intializes USART Driver */
	EEPROM_init();                             /*intializes EEPROM */
	while (USART_recieveByte() != ECU_READY);   /* waiting HMI_ECU to sent ECU_READY signal */
	USART_sendByte(ECU_READY);
	while (USART_recieveByte() != ECU_READY);   /* waiting HMI_ECU to sent ECU_READY si */
	while (1) {
		g_data = recieveData();                /* recieving command from HMI_ECU */
		switch (g_data) {                      /* switching between functions regarding the recieved command */
		case PASSWORD_COMMAND:
			passwordCreation();
			break;
		case PASSWORD_CONFIRMATION_COMMAND:
			passwordConfirmation();
			break;
		case PASSWORD_SCREEN_COMMAND:
			comparingWithSavedPassword();
			break;
		case OPEN_DOOR_COMMAND:
			openCloseDoor();
			break;
		default:
			break;

		}

	}

}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  passwordCreation
 [Description]  :  This function is responsible for password creation
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void passwordCreation(void) {
	uint8 i = 0;
	/* looping until HMI_ECU sends COMPLETE_TASK_COMMAND */
	while (USART_recieveByte() != COMPLETE_TASK_COMMAND) {
		g_password[i] = USART_recieveByte(); /* storing the sent password in g_password array */
		i++;
	}
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  passwordConfirmation
 [Description]  :  This function is responsible for matching the rentered password with the first one
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void passwordConfirmation(void) {

	uint8 i = 0;
	uint8 flag = 0;
	/* looping until HMI_ECU sends COMPLETE_TASK_COMMAND */
	while (USART_recieveByte() != COMPLETE_TASK_COMMAND) {
		if (g_password[i] == USART_recieveByte()) {

		} else {
			flag = 1;  /* not matched occurs */
		}
		i++;
	}
	if(flag)
	{
		/* send not matched command to HMI_ECU */
		USART_sendByte(PASSWORD_MATCH_NOT_CONFIRMATION_COMMAND);

	}
	else
	{

		/*
		 * saving the password in EEPROM and
		 * sending to HMI_ECU match confirmation command
		 */
		savePassword(g_password);
		USART_sendByte(PASSWORD_MATCH_CONFIRMATION_COMMAND);
	}
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  savePassword
 [Description]  :  This function is responsible for writing the new password in EEPROM
 [Args]
 [IN]           :  uint8 * a_pass
 	 	 	 	 	 this arg shall contains the address of the array that stores the password
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void savePassword (uint8 * a_pass)
{
	uint8 i = 0;
	while(i!=5) /* password size */
	{
		EEPROM_writeByte(BASE_ADDRESS_LOCATION+i,a_pass[i]); /* writing in EEPROM byte by byte */
		i++;
	}
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  comparingWithSavedPassword
 [Description]  :  This function is responsible for comparing the requested password with the saved one in the EEPROM
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void comparingWithSavedPassword (void)
{
	uint8 i = 0;
	uint8 * g_password_Ptr = g_password;
	while(i!=5) /* looping until password size to get password from EEPROM */
		{
			EEPROM_readByte(BASE_ADDRESS_LOCATION+i,g_password_Ptr+i);
			i++;
		}
	USART_sendByte(GET_PASSWORD_DONE); /* send to HMI_ECU GET_PASSWORD_DONE command */
	while(USART_recieveByte() != ECU_READY); /* looping until HMI_ECU sends ECU_READY signal */
	i = 0;
		uint8 flag = 0;
		/* looping until HMI_ECU sends COMPLETE_TASK_COMMAND */
		while (USART_recieveByte() != COMPLETE_TASK_COMMAND) {
			if (g_password[i] == USART_recieveByte()) {

			} else {
				flag = 1; /* Incorrect password entered */
			}
			i++;
		}
		if(flag)
		{
			g_errorCounter++;
			if(g_errorCounter == 3)
			{
				/*
				 * after 3 times incorrect password entered buzzer starts and sending to HMI_ECU ALARM_COMMAND
				 */
				USART_sendByte(ALARM_COMMAND);
				buzzer();
				g_errorCounter=0;
			}
			else{
			USART_sendByte(PASSWORD_MATCH_NOT_CONFIRMATION_COMMAND);
			}
		}
		else
		{
			USART_sendByte(PASSWORD_MATCH_CONFIRMATION_COMMAND);
			savePassword(g_password);
			g_errorCounter=0;
		}

}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  openCloseDoor
 [Description]  :  This function is responsible for opening and closing the door
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void openCloseDoor(void){
	/*
	 * setting compare A match output mode
	 * turning the motor clockwise
	 * waiting until reaching 15 seconds
	 * turing the motor anticlockwise
	 * waiting until reaching 30 seconds
	 * turning off the motor
	 * sending to HMI_ECU COMPLETE_TASK_COMMAND
	 */

	/* enable GPT_1 */
	GPT_enable(1);
	USART_sendByte(DOOR_IS_OPENNING_COMMAND);
	SET_BIT(MOTOR_PORT,MOTOR_EN);
	SET_BIT(MOTOR_PORT,MOTOR_IN1);
	CLEAR_BIT(MOTOR_PORT,MOTOR_IN2);
	g_counter = 0;
	while(g_counter != 15);
	g_counter = 0;
    SET_BIT(MOTOR_PORT,MOTOR_IN2);
	CLEAR_BIT(MOTOR_PORT,MOTOR_IN1);
	USART_sendByte(DOOR_IS_LOCKING_COMMAND);
	while(g_counter != 15);
	GPT_disable(1);
	CLEAR_BIT(MOTOR_PORT,MOTOR_EN);
	CLEAR_BIT(MOTOR_PORT,MOTOR_IN1);
	CLEAR_BIT(MOTOR_PORT,MOTOR_IN2);
	USART_sendByte(COMPLETE_TASK_COMMAND);

}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  buzzer
 [Description]  :  This function is responsible for turning on and off the buzzer
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void buzzer(void){

	/*
	 * setting compare A match output Mode
	 * turning on the buzzer
	 * waiting 60 seconds
	 * turning off the buzzer
	 * sending to HMI_ECU COMPLETE_TASK_COMMAND
	 */

	/* enable GPT_1 */
	GPT_enable(1);
	g_counter = 0;
	SET_BIT(BUZZER_PORT,BUZZER_PIN);
	while(g_counter != 60);
	GPT_disable(1);
    CLEAR_BIT(BUZZER_PORT,BUZZER_PIN);
	USART_sendByte(COMPLETE_TASK_COMMAND);
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  recieveData
 [Description]  :  This function is responsible for recieving the data from HMI_ECU
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
uint8 recieveData(void) {
	while (USART_recieveByte() != ECU_READY)
		;
	USART_sendByte(ECU_READY);
	g_data = USART_recieveByte();
	USART_sendByte(ECU_READY);
	return g_data;
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  calledBackFunction
 [Description]  :  This function is being called by Timer 1 when excutes its ISR
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void calledBackFunction (void){
	g_counter++;  /* seconds counter */
	CLEAR_BIT(MOTOR_PORT,MOTOR_EN);
	CLEAR_BIT(MOTOR_PORT,MOTOR_IN1);
	CLEAR_BIT(MOTOR_PORT,MOTOR_IN2);
}
