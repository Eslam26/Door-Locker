/*
 * timer1.c
 *
 *  Created on: Oct 9, 2019
 *      Author: eslamelnaggar
 */
/*--------------------------------------INCLUDES--------------------------------------------------------*/
#include "timer1.h"
#define NULL_PTR ((void*)0)
/*------------------------------------Global Variables--------------------------------------------------*/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*------------------------------------FUNCTIONS DEFINITIONS-------------------------------------------*/

ISR(TIMER1_OVF_vect) {
	if (g_callBackPtr != NULL_PTR) {
		(*g_callBackPtr)();
	}

}

ISR(TIMER1_COMPA_vect) {
	if (g_callBackPtr != NULL_PTR) {
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_COMPB_vect) {
	if (g_callBackPtr != NULL_PTR) {
		(*g_callBackPtr)();
	}
}

void Timer1_init(const Timer1_configType *Timer1_configType_Ptr) {
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);
	TCCR1A = (TCCR1A & 0b11111100)
			| ((Timer1_configType_Ptr->mode & 0b00000011) << (WGM10));
	TCCR1B = (TCCR1B & 0b11100111)
			| (((Timer1_configType_Ptr->mode & 0b00001100) >> 2) << (WGM12));
	TCCR1B = (TCCR1B & 0b11111000)
			| ((Timer1_configType_Ptr->clock & 0b00000111) << (CS10));
	ICR1 = Timer1_configType_Ptr->valueICR1;
}

void Timer1_normalMode(uint16 initialValueTimer) {
	SREG = (1 << 7);
	TCNT1 = initialValueTimer;
}

void Timer1_compareMode_OCR1A(const Timer1_compare_1A *Timer1_OCR1A_compare_Ptr) {
	SREG = (1 << 7);
	TCCR1A = (TCCR1A & 0b00111111) | ((Timer1_OCR1A_compare_Ptr->compareMode_OC1A & 0b00000011)<< (COM1A0));
	TCNT1 = Timer1_OCR1A_compare_Ptr->initialValueTimer;
	OCR1A = Timer1_OCR1A_compare_Ptr->valueOCR1A;

}

void Timer1_compareMode_OCR1B(const Timer1_compare_1B *Timer1_OCR1B_compare_Ptr) {
	SREG = (1 << 7);
	TCCR1A = (TCCR1A & 0b11001111) | ((Timer1_OCR1B_compare_Ptr->compareMode_OC1B & 0b00000011)<< (COM1B0));
	TCNT1 = Timer1_OCR1B_compare_Ptr->initialValueTimer;
	OCR1B = Timer1_OCR1B_compare_Ptr->valueOCR1B;
}

void Timer1_setCallBack(void (*setCallBack_Ptr)(void)) {
	g_callBackPtr = setCallBack_Ptr;
}

