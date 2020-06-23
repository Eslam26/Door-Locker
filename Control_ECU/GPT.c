/*******************************************************************************************************
 *  [MODULE]      :      <GPT>                                                                         *
 *  [FILE NAME]   :      <GPT.c>                                                                       *
 *  [AUTHOR]      :      <Eslam EL-Naggar>                                                             *
 *  [DATE CREATED]:      <Dec 6, 2019>                                                                 *
 *  [Description} :      <Source file for the ATmega16 GPT driver>                                     *
 ******************************************************************************************************/

#include "GPT.h"
#define NULL_PTR ((void *)0)

/*------------------------------------------GLOBAL VARIABLES------------------------------------------*/
static volatile void (*g_GPT_0_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_GPT_1_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_GPT_2_callBackPtr)(void) = NULL_PTR;
static const Gpt_timerConfig *GPT_timerStructurePtr = NULL_PTR;
static uint8 GPT_0_prescalerValue = ZERO;
static uint8 GPT_1_prescalerValue = ZERO;
static uint8 GPT_2_prescalerValue = ZERO;
static uint8 GPT_0_enableState = GPT_DISABLED;
static uint8 GPT_1_enableState = GPT_DISABLED;
static uint8 GPT_2_enableState = GPT_DISABLED;
static uint8 GPT_0_runningMode = GPT_CH_MODE_ONESHOT;
static uint8 GPT_1_runningMode = GPT_CH_MODE_ONESHOT;
static uint8 GPT_2_runningMode = GPT_CH_MODE_ONESHOT;

/*----------------------------------------------ISR---------------------------------------------------*/
ISR(TIMER0_COMP_vect) {
	if (g_GPT_0_callBackPtr != NULL_PTR) {
		(*g_GPT_0_callBackPtr)();
		/* if running mode is one shot mode -> disable the timer */
		if (GPT_0_runningMode == GPT_CH_MODE_ONESHOT) {
			GPT_disable(CHANNEL_ID_0);
		}

	}
}

ISR(TIMER1_COMPA_vect) {
	if (g_GPT_1_callBackPtr != NULL_PTR) {
		(*g_GPT_1_callBackPtr)();
		/* if running mode is one shot mode -> disable the timer */
		if (GPT_1_runningMode == GPT_CH_MODE_ONESHOT) {
			GPT_disable(CHANNEL_ID_1);
		}
	}

}

ISR(TIMER2_COMP_vect) {
	if (g_GPT_2_callBackPtr != NULL_PTR) {
		(*g_GPT_2_callBackPtr)();
		/* if running mode is one shot mode -> disable the timer */
		if (GPT_2_runningMode == GPT_CH_MODE_ONESHOT) {
			GPT_disable(CHANNEL_ID_2);
		}
	}
}

/*-----------------------------------Functions Definitions--------------------------------------------*/

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  GPT_init
 *  [Description]  :  This function is responsible for initializing the GPT Driver
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void GPT_init(const GPT_configType *GPT_configStructurePtr) {
	uint8 counter = ZERO;
	GPT_timerStructurePtr = GPT_configStructurePtr->Timers_Channels;

	/* looping over all timer channels */
	while (counter < NUM_TIMERS) {
		/* if timer is initialized, configure the timer with the required configurations,
		 * if not, go to the next timer channel
		 */
		if (GPT_timerStructurePtr->intializedNotIntializedConfig
				== GPT_CHANNEL_INTIALIZED) {

			switch (GPT_timerStructurePtr->channelNumberConfig) {
			case CHANNEL_ID_0:
				/* set initial value of the counter to zero */
				TCNT0 = ZERO;
				/* set number of ticks */
				OCR0 = GPT_timerStructurePtr->ticksNumberConfig;
				/* set timer mode to compare match */
				TCCR0 = (TCCR0 & 0b10000111) | (ONE) << (WGM01);
				TCCR0 = (TCCR0 & 0b01111111) | (ONE) << (FOC0);
				/* get prescaler value */
				GPT_0_prescalerValue =
						GPT_timerStructurePtr->clockPrescalerConfig;
				/* get timer running mode */
				GPT_0_runningMode =
						GPT_timerStructurePtr->continousNotContinousModeConfig;
				break;
			case CHANNEL_ID_1:
				/* set initial value of the counter to zero */
				TCNT1 = ZERO;
				/* set number of ticks */
				OCR1A = GPT_timerStructurePtr->ticksNumberConfig;
				/* get prescaler value */
				GPT_1_prescalerValue =
						GPT_timerStructurePtr->clockPrescalerConfig;
				/* set timer mode to compare match */
				TCCR1B = (TCCR1B & 0b111110111) | (ONE) << (WGM12);
				TCCR1A = (TCCR1A & 0b111110111) | (ONE) << (FOC1B);
				TCCR1A = (TCCR1A & 0b111111011) | (ONE) << (FOC1A);
				/* get timer running mode */
				GPT_1_runningMode =
						GPT_timerStructurePtr->continousNotContinousModeConfig;
				break;
			case CHANNEL_ID_2:
				/* set initial value of the counter to zero */
				TCNT2 = ZERO;
				/* set number of ticks */
				OCR2 = GPT_timerStructurePtr->ticksNumberConfig;
				/* set timer mode to compare match */
				TCCR2 = (TCCR0 & 0b10000111) | (ONE) << (WGM21);
				TCCR2 = (TCCR0 & 0b01111111) | (ONE) << (FOC0);
				/* get prescaler value */
				GPT_2_prescalerValue =
						GPT_timerStructurePtr->clockPrescalerConfig;
				/* get timer running mode */
				GPT_2_runningMode =
						GPT_timerStructurePtr->continousNotContinousModeConfig;
				break;
			default:
				break;
			}
		}
		GPT_timerStructurePtr++;
		counter++;
	}
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  GPT_enable
 *  [Description]  :  This function is responsible for enabling the required Gpt channel
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void GPT_enable(uint8 channelID) {
	switch (channelID) {
	case CHANNEL_ID_0:
		if (GPT_0_enableState == GPT_DISABLED) {
			GPT_0_enableState = GPT_ENABLED;
			/* enable compare match interrupt */
			TIMSK = (TIMSK & 0b11111101) | ((ONE) << (OCIE0));
			/* set the prescaler value */
			TCCR0 = (TCCR0 & 0b11111000)
					| ((GPT_0_prescalerValue & 0b00000111) << (CS00));
		} else {

		}
		break;
	case CHANNEL_ID_1:
		if (GPT_1_enableState == GPT_DISABLED) {
			GPT_1_enableState = GPT_ENABLED;
			/* enable compare match interrupt */
			TIMSK = (TIMSK & 0b11101111) | ((ONE) << (OCIE1A));
			/* set the prescaler value */
			TCCR1B = (TCCR0 & 0b11111000)
					| ((GPT_1_prescalerValue & 0b00000111) << (CS00));
		} else {

		}
		break;
	case CHANNEL_ID_2:
		if (GPT_2_enableState == GPT_DISABLED) {
			GPT_2_enableState = GPT_ENABLED;
			/* enable compare match interrupt */
			TIMSK = (TIMSK & 0b01111111) | ((ONE) << (OCIE2));
			/* set the prescaler value */
			TCCR2 = (TCCR0 & 0b11111000)
					| ((GPT_2_prescalerValue & 0b00000111) << (CS00));
		} else {

		}
		break;
	}
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  GPT_disable
 *  [Description]  :  This function is responsible for disabling the required Gpt channel
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void GPT_disable(uint8 channelID) {
	switch (channelID) {
	case CHANNEL_ID_0:
		if (GPT_0_enableState == GPT_ENABLED) {
			GPT_0_enableState = GPT_DISABLED;
			TCNT0 = 0;
			/* disable compare match interrupt */
			TIMSK = (TIMSK & 0b11111101) | ((ONE) << (OCIE0));
			/* set the clock prescaler to no clock source */
			TCCR0 = (TCCR0 & 0b11111000) | ((ZERO & 0b00000111) << (CS00));
		} else {

		}

		break;
	case CHANNEL_ID_1:
		if (GPT_1_enableState == GPT_ENABLED) {
			GPT_1_enableState = GPT_DISABLED;
			TCNT1 = 0;
			/* disable compare match interrupt */
			TIMSK = (TIMSK & 0b11101111) | ((ONE) << (OCIE1A));
			/* set the clock prescaler to no clock source */
			TCCR1B = (TCCR0 & 0b11111000) | ((ZERO & 0b00000111) << (CS00));
		} else {

		}

		break;
	case CHANNEL_ID_2:
		if (GPT_2_enableState == GPT_ENABLED) {
			GPT_2_enableState = GPT_DISABLED;
			TCNT2 = 0;
			/* disable compare match interrupt */
			TIMSK = (TIMSK & 0b01111111) | ((ONE) << (OCIE2));
			/* set the clock prescaler to no clock source */
			TCCR2 = (TCCR0 & 0b11111000) | ((ZERO & 0b00000111) << (CS00));
		} else {

		}

		break;
	default:
		break;
	}
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  GPT_0_setCallBack
 *  [Description]  :  This function is responsible for getting the address of the function which
 *  					will be executed every Timer 0 compare match
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void GPT_0_setCallBack(void (*GPT_0_setCallBack_Ptr)(void)) {
	g_GPT_0_callBackPtr = GPT_0_setCallBack_Ptr;
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  GPT_1_setCallBack
 *  [Description]  :  This function is responsible for getting the address of the function which
 *  					will be executed every Timer 1 compare match
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/
void GPT_1_setCallBack(void (*GPT_1_setCallBack_Ptr)(void)) {
	g_GPT_1_callBackPtr = GPT_1_setCallBack_Ptr;
}

/*----------------------------------------------------------------------------------------------------
 *  [Function Name]:  GPT_0_setCallBack
 *  [Description]  :  This function is responsible for getting the address of the function which
 *  					will be executed every Timer 2 compare match
 *  [Returns]      :  This function returns void
 ----------------------------------------------------------------------------------------------------*/

void GPT_2_setCallBack(void (*GPT_2_setCallBack_Ptr)(void)) {
	g_GPT_2_callBackPtr = GPT_2_setCallBack_Ptr;
}

