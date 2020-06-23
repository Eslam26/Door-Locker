/************************************************************************************************************************
 *  [FILE NAME]   :      <main.c>                                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                                              *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                                  *
 *  [Description} :      <Header file for the HMI_ECU>                                                                  *
 ************************************************************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

/*---------------------------------------------------DEFINITIONS--------------------------------------------------------*/
#define ECU_READY 0x11                                   /* defines Ready Signal */
#define PASSWORD_COMMAND  0x01                           /* defines Password Request Signal */
#define PASSWORD_CONFIRMATION_COMMAND 0x02               /* defines Password Confirmation Request Signal */
#define PASSWORD_MATCH_CONFIRMATION_COMMAND 0x03         /* defines Password Match Confirmation Signal */
#define PASSWORD_MATCH_NOT_CONFIRMATION_COMMAND 0x04     /* defines Password Not matched Confirmation Signal */
#define PASSWORD_SCREEN_COMMAND 0x05                     /* defines Password Screen Signal */
#define REQUEST_SCREEN_COMMAND 0x06                      /* defines Options Screen Signal */
#define OPEN_DOOR_COMMAND 0x07                           /* defines Open Door signal */
#define DOOR_IS_OPENNING_COMMAND 0x08                    /* defines Opening state of the door signal */
#define DOOR_IS_LOCKING_COMMAND 0x09                     /* defines Closing state of the door signal */
#define COMPLETE_TASK_COMMAND 0x0A                       /* defines completing task signal */
#define ALARM_COMMAND 0x0B                               /* defines Alert Signal */
#define GET_PASSWORD_DONE 0x0C                           /* defines state of getting saved password from EXT-EEPROM */
#define NULL_PTR ((void*)0)
#define PROJECT_NAME "Door Locker"
#define WELCOME_MESSAGE "WELCOME"
#define PASSWORD_REQUEST_MESSAGE "Please enter your password :[5]"
#define OLD_PASSWORD_REQUEST_MESSAGE "Please enter your old password :[5] "
#define PASSWORD_REQUEST_CONFIRMATION_MESSAGE "Please re-enter your password :[5] "
#define NEW_PASSWORD_REQUEST_MESSAGE "Please enter your new password :[5] "
#define PASSWORD_NOT_MATCHED_ERROR_MESSAGE "Not Matched ... "
#define FIRST_REQUEST_MESSAGE "(+) : open the door "
#define SECOND_REQUEST_MESSAGE "(-) : change the password"
#define INCORRET_INPUT_MESSAGE "INCORRECT INPUT"
#define INCORRET_PASSWORD_MESSAGE "INCORRECT PASSWORD"
#define DOOR_IS_UNLOCKING_MESSAGE "Door is unlocking ..."
#define DOOR_IS_LOCKING_MESSAGE "Door is locking ..."
#define THIEF_MESSAGE "Thief !!!"
#define MILLI_SEC_400 400
#define MILLI_SEC_2000 2000
#define ZERO 0
#define ROW_0 0
#define ROW_1 1
#define COL_0 0
#define COL_3 3
#define COL_12 12
#define COL_13 13
#define getIntroScreen_FUN_INDEX 0
#define getPasswordCreationScreen_FUN_INDEX 1
#define getPasswordScreen_FUN_INDEX 2
#define getRequestScreen_FUN_INDEX 3
#define getOpenDoorCloseDoorScreen_FUN_INDEX 4
#define getBuzzerScreen_FUN_INDEX 5

#endif /* MAIN_H_ */
