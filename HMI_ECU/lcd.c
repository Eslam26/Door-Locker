/*******************************************************************************************************
 *  [MODULE]      :      <LCD>                                                                         *
 *  [FILE NAME]   :      <LCD.c>                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 5, 2019>                                                                 *
 *  [Description} :      <Source file for the ATmega16 LCD driver>                                     *
 ******************************************************************************************************/

#include "LCD.h" /* include the header file of LCD Driver */

/*------------------------------------ Functions Definitions------------------------------------------*/

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  LCD_init
 [Description]  :  This function is responsible for initializing LCD Driver
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */

	#if (DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
		#else
			LCD_DATA_PORT_DIR |= 0x0F; /* Configure the lowest 4 bits of the data port as output pins */
		#endif
		LCD_sendCommand(FOUR_BITS_DATA_MODE); /* Setting LCD in 4-bit mode */
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line LCD + 4-bit Data Mode + 5*7 dot display Mode */
	#elif (DATA_BITS_MODE == 8)
		LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	#endif

	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  LCD_sendCommand
 [Description]  :  This function is responsible for sending command to LCD
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void LCD_sendCommand(uint8 a_command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); /* Clearing RW pin to write data to LCD*/
	_delay_ms(1); /* delay for processing */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD */
	_delay_ms(1); /* delay for processing */
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (a_command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_command & 0xF0) >> 4);
#endif

	_delay_ms(1); /* delay for processing */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD */
	_delay_ms(1); /* delay for processing */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD  */
	_delay_ms(1); /* delay for processing */

	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((a_command & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (a_command & 0x0F);
#endif

	_delay_ms(1); /* delay for processing  */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD */
	_delay_ms(1); /* delay for processing */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = a_command; /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD */
	_delay_ms(1); /* delay for processing */
#endif
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  LCD_displayCharacter
 [Description]  :  This function is responsible for displaying character on LCD
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void LCD_displayCharacter(uint8 a_data)
{
	/* Data Mode RS=1 */
	SET_BIT(LCD_CTRL_PORT,RS);
	/* Clearing RW pin to write data to LCD */
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	/* delay for processing */
	_delay_ms(1);
	/* Enable LCD */
	SET_BIT(LCD_CTRL_PORT,E);
	/* delay for processing  */
	_delay_ms(1);
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (a_data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((a_data & 0xF0) >> 4);
#endif

	/* delay for processing  */
	_delay_ms(1);
	 /* disable LCD */
	CLEAR_BIT(LCD_CTRL_PORT,E);
	/* delay for processing */
	_delay_ms(1);
	/* Enable LCD */
	SET_BIT(LCD_CTRL_PORT,E);
	/* delay for processing */
	_delay_ms(1);

	/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((a_data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (a_data & 0x0F);
#endif

	/* delay for processing */
	_delay_ms(1);
	/* disable LCD */
	CLEAR_BIT(LCD_CTRL_PORT,E);
	/* delay for processing */
	_delay_ms(1);
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = a_data; /* out the required command to the data bus D0 --> D7 */
	/* delay for processing  */
	_delay_ms(1);
	 /* disable LCD */
	CLEAR_BIT(LCD_CTRL_PORT,E);
	/* delay for processing */
	_delay_ms(1);
#endif
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  LCD_displayString
 [Description]  :  This function is responsible for displaying string
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void LCD_displayString(const char *Str)
{
	uint8 i = 0;
	/* looping until reaches to the null character element */
	while(Str[i] != '\0')
	{
		/* display the current character */
		LCD_displayCharacter(Str[i]);
		i++;
	}

}
/*----------------------------------------------------------------------------------------------------
 [Function Name]:  LCD_goToRowColumn
 [Description]  :  This function is responsible for moving curosr to specific location
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;

	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}
	/* write the specific address in the LCD */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  LCD_displayStringRowColumn
 [Description]  :  This function is responsible for displaying string from specific location
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  LCD_intgerToString
 [Description]  :  This function is responsible for displaying integer values
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* 10 for decimal */
   LCD_displayString(buff);
}

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  LCD_clearScreen
 [Description]  :  This function is responsible for clearing screen
 [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/


void LCD_clearScreen(void){
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}
