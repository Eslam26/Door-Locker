/******************************************************************************************************
 *  [FILE NAME]   :      <keypad.c>                                                                    *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                 *
 *  [Description} :      <Source file for the KeyPad Driver>                                           *
 ******************************************************************************************************/

/*----------------------------------------- -INCLUDES------------------------------------------------*/
#include "keypad.h"

/* if N_COL defines as 3 so we will remove the declaration of the KeyPad_4x4_adjustKeyNumber function */
#if (N_COL == 3)
static uint8 KeyPad_4x3_adjustKeyNumber(uint8 a_button_number);
/* if N_COL defines as 4 so we will remove the declaration of the KeyPad_4x3_adjustKeyNumber function */
#elif (N_COL == 4)
static uint8 KeyPad_4x4_adjustKeyNumber(uint8 a_button_number);
#endif
/*------------------------------------FUNCTIONS DEFINITIONS------------------------------------------*/

/*----------------------------------------------------------------------------------------------------
 [Function Name]:  KeyPad_getPressedKey
 [Description]  :  This functions is responsible for getting which the key is pressed
 [Returns]      :  This return shall indicate the value of the key which is pressed
 ----------------------------------------------------------------------------------------------------*/
uint8 keyPad_getPressedKey(void) {
	uint8 col, row; /*variable for storing the value of the current coloumn and row during looping over them*/
	while (1) {
		/* starting looping over them */
		for (col = 0; col < N_COL; col++) {
			/* each loop one coloumn only will be an output pin
			 * and the rest will be input pins including the row pins
			 */
			KEYPAD_PORT_DIRECTION = (0b00010000 << col);

			/*clear the output coloumn and enabling the internal pull resistors for row pins*/
			KEYPAD_PORT_OUT = (~(0b00010000 << col));

			for (row = 0; row < N_ROW; row++) /*looping over the rows pins*/
			{
				if (BIT_IS_CLEAR(KEYPAD_PORT_IN, row))
				{
					/* if N_COL defines as 3 so we will remove the declaration of the KeyPad_4x4_adjustKeyNumber function */

						#if (N_COL == 3)
							return KeyPad_4x3_adjustKeyNumber((row*N_COL)+col+1);
					/* if N_COL defines as 4 so we will remove the declaration of the KeyPad_4x3_adjustKeyNumber function */
						#elif (N_COL== 4)
							return KeyPad_4x4_adjustKeyNumber((row*N_COL)+col+1);
						#endif
				}
			}
		}
	}

}


/*----------------------------------------------------------------------------------------------------
 [Function Name]:  KeyPad_4x3_adjustKeyNumber
 [Description]  :  This functions is responsible for adjusting the key Number for Keypad 4x3
 [Args]
 [in]              uint8 a_button_n
 	 	 	 	 	 	this arg shall indicate the number of the button which is pressed
 [Returns]      :  This return shall indicate the value of the key which is pressed
 ----------------------------------------------------------------------------------------------------*/
#if (N_COL == 3)

static uint8 KeyPad_4x3_adjustKeyNumber(uint8 a_button_number)
{
		switch(a_button_number) /*switching on the value of the button number to return the real value*/
		{
			case 10: return '*'; // ASCII Code of =
					 break;
			case 11: return 0;
					 break;
			case 12: return '#'; // ASCII Code of +
					 break;
			default: return a_button_number;
		}
}


#elif ( N_COL ==  4)
/*----------------------------------------------------------------------------------------------------
 [Function Name]:  KeyPad_4x4_adjustKeyNumber
 [Description]  :  This functions is responsible for adjusting the key Number for Keypad 4x4
 [Args]
 [in]              uint8 a_button_n
 	 	 	 	 	 	this arg shall indicate the number of the button which is pressed
 [Returns]      :  This return shall indicate the value of the key which is pressed
 ----------------------------------------------------------------------------------------------------*/
static uint8 KeyPad_4x4_adjustKeyNumber(uint8 a_button_number)
{
	switch(a_button_number) /*switching on the value of the button number to return the real value*/
		{
			case 1: return 7;
					break;
			case 2: return 8;
					break;
			case 3: return 9;
					break;
			case 4: return '%'; // ASCII Code of %
					break;
			case 5: return 4;
					break;
			case 6: return 5;
					break;
			case 7: return 6;
					break;
			case 8: return '*'; /* ASCII Code of '*' */
					break;
			case 9: return 1;
					break;
			case 10: return 2;
					break;
			case 11: return 3;
					break;
			case 12: return '-'; /* ASCII Code of '-' */
					break;
			case 13: return 13;  /* ASCII of Enter */
					break;
			case 14: return 0;
					break;
			case 15: return '='; /* ASCII Code of '=' */
					break;
			case 16: return '+'; /* ASCII Code of '+' */
					break;
			default: return a_button_number;
		}
}

#endif
