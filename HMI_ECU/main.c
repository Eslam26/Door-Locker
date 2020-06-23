/************************************************************************************************************************
 *  [FILE NAME]   :      <main.c>                                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                                              *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                                  *
 *  [Description} :      <Source file for the HMI_ECU>                                                                  *
 ************************************************************************************************************************/

/*------------------------------------------------------INCLUDES--------------------------------------------------------*/
#include "micro_config.h"
#include "main.h"
#include "USART.h"
#include "keypad.h"
#include "LCD.h"



/*------------------------------------------------FUNCTIONS DECLARATIONS------------------------------------------------------------------*/
void getIntroScreen(void);
void getPasswordCreationScreen(void);
void getPasswordScreen(void);
void getRequestScreen(void);
void getOpenDoorCloseDoorScreen(void);
void getBuzzerScreen(void);
void sendData(uint8 data);

/*-------------------------------------------------GLOBAL VARIABLES-----------------------------------------------------------------------*/
uint8 volatile g_stepSelector = 0;
uint8 volatile g_switchRequest = 0;
uint8 g_data;
uint8 volatile g_flag = 0;
/* pointer to array of functions */
void (*fun_ptr_arr[])(
		void) = {getIntroScreen, getPasswordCreationScreen,
			getPasswordScreen, getRequestScreen, getOpenDoorCloseDoorScreen, getBuzzerScreen
};

/*--------------------------------------------------STRUCTURES----------------------------------------------------------------------------*/

int main() {



	/* Initializes USART Driver */
	USART_init(&USART_configStructure);
	/* Initializes LCD */
	LCD_init();
	/* clear the screen */
	LCD_clearScreen();

    /* sending to CONTROL_ECU ECU_READY signal */
	USART_sendByte(ECU_READY);
	/* looping until CONTROL_ECU send ECU_READY signal */
	while (USART_recieveByte() != ECU_READY)
		;
	/* sending to CONTROL_ECU ECU_READY signal */
	USART_sendByte(ECU_READY);
	(*fun_ptr_arr[getIntroScreen_FUN_INDEX])();

	while (1)

	{
		/* calling the function by using pointer to the function
		 * each function has its own index in fun_ptr_arr
		 */
		(*fun_ptr_arr[g_stepSelector])();
	}

	return 0;

}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  getIntroScreen
 [Description]  :  This function is responsible for showing project name and welcome message
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void getIntroScreen(void) {
	LCD_clearScreen();
	/* move the cursor to row_0, col_12 */
	LCD_goToRowColumn(ROW_0, COL_12);
	/* displaying project name */
	LCD_displayString(PROJECT_NAME);
	/* move the cursor to row_1, col_14 */
	LCD_goToRowColumn(ROW_1, 14);
	/* displaying welcome message */
	LCD_displayString(WELCOME_MESSAGE);
	/* waiting 2 seconds */
	_delay_ms(MILLI_SEC_2000);
	/* passing the index of the next function */
	g_stepSelector = getPasswordCreationScreen_FUN_INDEX;
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  getPasswordCreationScreen
 [Description]  :  This function is responsible for displaying password creation screen and
 	 	 	 	 	 	 sending the entered password to CONTROL_ECU
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void getPasswordCreationScreen(void) {
	uint8 key, flag = 1, command;
	/* sending to CONTROL_ECU PASSWORD_COMMAND */
	sendData(PASSWORD_COMMAND);
	LCD_clearScreen();
	/*
	 * 1. checking if there is an old password or not depending from which function is called before this function being called
	 * 2. waiting for a key to be pressed and starting to send the password to CONTROL_ECU to take descisions
	 * 3. after entering the password two times
	 * 4. waiting CONTROL_ECU to take descision about the confirmation of the two passwords
	 * 5. if the two passwords do not match we will point to this function again
	 * 6. if the two password matchd we will point to another function ( Request Screen function )
	 */
	if(g_flag)
	{
		LCD_displayString(NEW_PASSWORD_REQUEST_MESSAGE);
		g_flag=0;
	}
	else
	{
		LCD_displayString(PASSWORD_REQUEST_MESSAGE);
	}

	LCD_goToRowColumn(ROW_1, COL_3);

	do {
		key = keyPad_getPressedKey();
		USART_sendByte(key);
		if (key != '=')
			LCD_displayCharacter('*');
		_delay_ms(MILLI_SEC_400);
	} while (key != '=');
	USART_sendByte(COMPLETE_TASK_COMMAND);

	sendData(PASSWORD_CONFIRMATION_COMMAND);
	LCD_clearScreen();
	LCD_displayString(PASSWORD_REQUEST_CONFIRMATION_MESSAGE);
	LCD_goToRowColumn(ROW_1, COL_3);
	do {
		key = keyPad_getPressedKey();
		USART_sendByte(key);
		if (key != '=')
			LCD_displayCharacter('*');
		_delay_ms(MILLI_SEC_400);
	} while (key != '=');
	USART_sendByte(COMPLETE_TASK_COMMAND);

	while (flag) {
		command = USART_recieveByte();
		if (command == PASSWORD_MATCH_CONFIRMATION_COMMAND) {
			g_stepSelector = getRequestScreen_FUN_INDEX;
			flag = ZERO;

		} else if (command == PASSWORD_MATCH_NOT_CONFIRMATION_COMMAND) {
			g_stepSelector = getPasswordCreationScreen_FUN_INDEX;
			LCD_clearScreen();
			LCD_displayString(PASSWORD_NOT_MATCHED_ERROR_MESSAGE);
			_delay_ms(MILLI_SEC_400);
			flag = ZERO;
		}
	}

}

/*------------------------------------------------------------------------------------------------------------------------------
 [Function Name]:  getPasswordScreen
 [Description]  :  This function is responsible for requesting to enter the password in order to match with the saved password
 [Returns]      :  This function returns void
 ------------------------------------------------------------------------------------------------------------------------------*/
void getPasswordScreen(void) {
	uint8 key = ZERO;
	uint8 flag = 1;
	uint8 command = ZERO;
	sendData(PASSWORD_SCREEN_COMMAND);
	LCD_clearScreen();
	if(g_flag)
		{
			LCD_displayString(OLD_PASSWORD_REQUEST_MESSAGE);
		}
		else
		{
			LCD_displayString(PASSWORD_REQUEST_MESSAGE);
		}
	LCD_goToRowColumn(ROW_1, COL_3);
	while (USART_recieveByte() != GET_PASSWORD_DONE)
		;
	/* sending to CONTROL_ECU ECU_READY signal */
	USART_sendByte(ECU_READY);
	do {
		key = keyPad_getPressedKey();
		USART_sendByte(key);
		if (key != '=')
			LCD_displayCharacter('*');
		_delay_ms(MILLI_SEC_400);
	} while (key != '=');

	USART_sendByte(COMPLETE_TASK_COMMAND);

	while (flag) {
		command = USART_recieveByte();
		switch (command) {
		case PASSWORD_MATCH_CONFIRMATION_COMMAND:

			if (g_switchRequest) {
				g_stepSelector = getOpenDoorCloseDoorScreen_FUN_INDEX;
			} else {
				g_stepSelector = getPasswordCreationScreen_FUN_INDEX;
			}

			flag = ZERO;
			break;
		case PASSWORD_MATCH_NOT_CONFIRMATION_COMMAND:
			g_stepSelector = getPasswordScreen_FUN_INDEX;
			LCD_clearScreen();
			LCD_displayString(INCORRET_PASSWORD_MESSAGE);
			_delay_ms(MILLI_SEC_400);
			flag = ZERO;
			break;
		case ALARM_COMMAND:
			g_stepSelector = getBuzzerScreen_FUN_INDEX;
			flag = ZERO;
			break;
		default:
			break;
		}

	}
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  getRequestScreen
 [Description]  :  This function is responsible for showing the tasks that the system offers
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void getRequestScreen(void) {
	uint8 key;
	LCD_clearScreen();
	sendData(REQUEST_SCREEN_COMMAND);
	LCD_displayString(FIRST_REQUEST_MESSAGE);
	LCD_goToRowColumn(ROW_1, COL_0);
	LCD_displayString(SECOND_REQUEST_MESSAGE);
	key = keyPad_getPressedKey();
	_delay_ms(MILLI_SEC_400);
	if (key == '+') {
		g_stepSelector = getPasswordScreen_FUN_INDEX;
		g_switchRequest = 1;
	} else if (key == '-') {
		g_stepSelector = getPasswordScreen_FUN_INDEX;
		g_switchRequest = 0;
		g_flag = 1;
	} else {
		LCD_clearScreen();
		g_stepSelector = getRequestScreen_FUN_INDEX;

	}
	_delay_ms(MILLI_SEC_400);
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  getOpenDoorCloseDoorScreen
 [Description]  :  This function is responsible for showing the door status when it opens and closes
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void getOpenDoorCloseDoorScreen(void) {
	LCD_clearScreen();
	sendData(OPEN_DOOR_COMMAND);
	while (USART_recieveByte() != DOOR_IS_OPENNING_COMMAND)
		;
	LCD_displayString(DOOR_IS_UNLOCKING_MESSAGE);
	while (USART_recieveByte() != DOOR_IS_LOCKING_COMMAND);
	LCD_clearScreen();
	LCD_displayString(DOOR_IS_LOCKING_MESSAGE);
	while (USART_recieveByte() != COMPLETE_TASK_COMMAND);
	g_stepSelector = getRequestScreen_FUN_INDEX;
}


/*----------------------------------------------------------------------------------------------------
 [Function Name]:  getBuzzerScreen
 [Description]  :  This function is responsible for showing the thief message when the buzzer starts
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void getBuzzerScreen(void) {
	LCD_clearScreen();
	LCD_displayString(THIEF_MESSAGE);
	while (USART_recieveByte() != COMPLETE_TASK_COMMAND)
		;
	g_stepSelector = getIntroScreen_FUN_INDEX;
}


/*----------------------------------------------------------------------------------------------------
 [Function Name]:  sendData
 [Description]  :  This function is responsible for recieving the data from HMI_ECU
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void sendData(uint8 data) {
	/* sending to CONTROL_ECU ECU_READY signal */
	USART_sendByte(ECU_READY);
	/* looping until CONTROL_ECU send ECU_READY signal */
	while (USART_recieveByte() != ECU_READY)
		;
	USART_sendByte(data);
	/* looping until CONTROL_ECU send ECU_READY signal */
	while (USART_recieveByte() != ECU_READY)
		;
}
