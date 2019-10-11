/*
 * timer1.h
 *
 *  Created on: Oct 9, 2019
 *      Author: eslamelnaggar
 */

#ifndef TIMER1_H_
#define TIMER1_H_
/*--------------------------------------INCLUDES--------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "common_macros.h"
#include "std_types.h"

/*-----------------------------------DEFINITIONS and Configurations--------------------------------------*/




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

typedef struct {
	Timer1_mode mode;
	Timer1_clock clock;
	uint16 valueICR1;
}Timer1_configType;

typedef struct {
	uint16 initialValueTimer;
	Timer1_OC1A compareMode_OC1A;
	uint16 valueOCR1A;
}Timer1_compare_1A;

typedef struct {
	uint16 initialValueTimer;
	Timer1_OC1A compareMode_OC1B;
	uint16 valueOCR1B;
}Timer1_compare_1B;

/*---------------------------------------FUNCTION DECLARATIONS------------------------------------------*/

void Timer1_init(const Timer1_configType * Timer1_configType_Ptr);
void Timer1_normalMode(uint16 initialValueTimer);
void Timer1_compareMode_OCR1A(const Timer1_compare_1A * Timer1_OCR1A_compare_Ptr);
void Timer1_compareMode_OCR1B(const Timer1_compare_1B * Timer1_OCR1B_compare_Ptr);
void Timer1_setCallBack(void(*setCallBack_Ptr)(void));



#endif /* TIMER1_H_ */
