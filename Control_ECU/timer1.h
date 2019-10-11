/*******************************************************************************************************
 *  [FILE NAME]   :      <timer1.h>                                                                    *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Oct 4, 2019>                                                                 *
 *  [Description} :      <header file for atmega16 Timer1>                                             *
 ******************************************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_
/*--------------------------------------INCLUDES--------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "common_macros.h"
#include "std_types.h"

/*-----------------------------------------ENUMS---------------------------------------------------------*/
typedef enum{
	compareMode_1A, compareMode_2A, compareMode_3A, compareMode_4A
}Timer1_OC1A;

typedef enum{
	compareMode_1B, compareMode_2B, compareMode_3B, compareMode_4B
}Timer1_OC1B;

typedef enum{
	Normal, PWM_phaseCorrect_8BIT, PWM_phaseCorrect_9BIT, PWM_phaseCorrect_10BIT, CTC_OCR1A, FAST_PWM_8BIT,
	FAST_PWM_9BIT, FAST_PWM_10BIT, PWM_PHASE_FREQUENCEY_CORRECT_ICR1, PWM_PHASE_FREQUENCEY_CORRECT_OCR1A,
	PWM_phaseCorrect_ICR1, PWM_phaseCorrect_OCR1A, CTC_ICR1, FAST_PWM_ICR1 =14, FAST_PWM_OCR1A
}Timer1_mode;

typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024, External_clock_falling, External_clock_rising
}Timer1_clock;
/*--------------------------------------Structures and Unions------------------------------------------*/

/*********************************************************************************************************
[Structure Name]        : Timer1_configType
[Structure Description] :
This structure is responsible for maintaining information about initial parameters
in order to intializing the Timer1 Driver
*********************************************************************************************************/
typedef struct {
	Timer1_mode mode;    /*      timer mode        */
	Timer1_clock clock; /*     timer prescaler    */
	uint16 valueICR1;  /* value of ICR1 register */
}Timer1_configType;

/*********************************************************************************************************
[Structure Name]        : Timer1_compare_1A
[Structure Description] :
This structure is responsible for maintaining information about initial parameters
in order to intializing the compare mode of timer1 driver for pin OC1A
*********************************************************************************************************/
typedef struct {
	uint16 initialValueTimer;      /* intial value of the timer counter */
	Timer1_OC1A compareMode_OC1A; /* compare Match output mode for OC1A */
	uint16 valueOCR1A;           /* value of OCR1 register */
}Timer1_compare_1A;

/*********************************************************************************************************
[Structure Name]        : Timer1_compare_1B
[Structure Description] :
This structure is responsible for maintaining information about initial parameters
in order to intializing the compare mode of timer1 driver for pin OC1B
*********************************************************************************************************/
typedef struct {
	uint16 initialValueTimer;    /* intial value of the timer counter */
	Timer1_OC1A compareMode_OC1B;/* compare Match output mode for OC1B */
	uint16 valueOCR1B;           /* value of OCR1 register */
}Timer1_compare_1B;

/*---------------------------------------FUNCTION DECLARATIONS------------------------------------------*/

void Timer1_init(const Timer1_configType * Timer1_configType_Ptr);     /*declaration for a function that intializes Timer 1 Driver */
void Timer1_normalMode(uint16 initialValueTimer);                      /*declaration for a function that starts normal overflow mode */
void Timer1_compareMode_OCR1A(const Timer1_compare_1A * Timer1_OCR1A_compare_Ptr); /*declaration for a function that setups compareMatchOutput mode for OC1A */
void Timer1_compareMode_OCR1B(const Timer1_compare_1B * Timer1_OCR1B_compare_Ptr); /*declaration for a function that setups compareMatchOutput mode for OC1A */
void changeTimerClock(const Timer1_configType *Timer1_configType_Ptr);             /*declaration for a function that changes clock prescaler */
void Timer1_setCallBack(void(*setCallBack_Ptr)(void));
/*declaration for a function that get the address of the function that will be called when timer completes its task */



#endif /* TIMER1_H_ */
