/*******************************************************************************************************
 *  [FILE NAME]   :      <LCD.h>                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                 *
 *  [Description} :      <header file for LCD Driver>                                                  *
 ******************************************************************************************************/

#ifndef lcd_H_
#define lcd_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 8

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

/* LCD HW Pins */
#define RS PD0                            /* defines RS pin */
#define RW PD1                            /* defines RW pin */
#define E  PD2                            /* defines enable pin */
#define LCD_CTRL_PORT PORTD               /* defines LCD Control port */
#define LCD_CTRL_PORT_DIR DDRD            /* defines LCD control port direction */

#define LCD_DATA_PORT PORTC               /* defines LCD data port */
#define LCD_DATA_PORT_DIR DDRC            /* defines data port direction */

/* LCD Commands */
#define CLEAR_COMMAND 0x01                /* defines clear command */
#define FOUR_BITS_DATA_MODE 0x02          /* defines four bits data mode command */
#define TWO_LINE_LCD_Four_BIT_MODE 0x28   /* defines two lines LCD four bit mode command */
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38  /* defines two lines LCD eight bit mode command */
#define CURSOR_OFF 0x0C                   /* defines cursor off command */
#define CURSOR_ON 0x0E                    /* defines cursor on command */
#define SET_CURSOR_LOCATION 0x80          /* defines set cursor location command */


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8 command);     /* declaration of the function that sends commands to LCD */
void LCD_displayCharacter(uint8 data);   /* declaration of the function that displays character */
void LCD_displayString(const char *Str); /* declaration of the function that displays string   */
void LCD_init(void);                     /* declaration of the function that initializes LCD  */
void LCD_clearScreen(void);              /* declaration of the function that clears the screen */
/* declaration of the function that displays string starts from specific coloumn and row */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

/* declaration of the function that moves the cursor to specific location */
void LCD_goToRowColumn(uint8 row,uint8 col);

/* declaration of the function that takes a variables and displays it on the screen */
void LCD_intgerToString(int data);

#endif /* lcd_H_ */
