/************************************************************************************************************************
 *  [FILE NAME]   :      <main.h>                                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                                              *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                                  *
 *  [Description} :      <Header file for the CONTROL_ECU>                                                              *
 ************************************************************************************************************************/

#ifndef MAIN_H_
#define MAIN_H_

/*---------------------------------------------------DEFINITIONS--------------------------------------------------------------------------*/
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
#define BASE_ADDRESS_LOCATION 0x0002                     /* defines the base address location which the password has been saved in the memory */

#define BUZZER_PORT_DIRECTION DDRD                       /* defines the port direction that the buzzer is being connected */
#define BUZZER_PORT PORTD                                /* defines the port out that the buzzer is being connected */
#define BUZZER_PIN PD2                                   /* defines which pin that the buzzer is connected to */
#define MOTOR_PORT_DIRECTION DDRC                        /* defines the port direction that the motor is being connected */
#define MOTOR_PORT PORTC                                 /* defines the port out that the motor is being connected */
#define MOTOR_IN1 4                                      /* defines which pin that the first input of the motor is connected to */
#define MOTOR_IN2 5                                      /* defines which pin that the second input of the motor is connected to */
#define MOTOR_EN 3                                       /* defines which pin that the enable pin of the motor is connected to */
#define NULL_Ptr ((void*)0)
#define ZERO 0                                           /* defines 0 number */

#endif /* MAIN_H_ */
