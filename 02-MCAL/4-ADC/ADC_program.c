/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 18/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : ADC        *************************/
/*****************************************************************/

/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"


/* Busy Flag*/
static u8 ADC_Global_u8BusyFlag=ADC_u8NotBusy;
/* Index Of array on chain*/
static u8 ADC_u8ChainIndex;
static u8 ADC_u8ChainSize;

static u16 *Global_u8ADCResult = NULL;
static u8 *Global_u8ADCChain  = NULL;

/* Global Pointers */
#ifndef ADC_u8_UseChain

static void (*ADC_Global_PtrFuncEndNotificationFunction)(u16) 	=NULL;

#else

static void (*ADC_Global_PtrFuncEndNotChain)(void) 				=NULL;

#endif

void ADC_voidInit(void){

	/* 1-Select VREF = 5*/
	CLR_BIT(ADC_u8_ADMUX_REG,ADC_u8_Channel_7);
	SET_BIT(ADC_u8_ADMUX_REG,ADC_u8_Channel_6);

	/* 2-Select Right Adjustment */
	CLR_BIT(ADC_u8_ADMUX_REG,ADC_u8_Channel_5);

	/* 3-Select Single Conversion Mode  Or Free Running
	 *
	 * we select Single conversion mode her
	 * */
	SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_5);

	/* 4-Select prescaler = 64*/
	CLR_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_0);
	SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_1);
	SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_2);

	/* 5-ADC Enable */
	SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_7);
}

/* synchronous Function that avoid blocking state
 *
 * Using Timeout mechanism
 * */

u8   ADC_u8GetDigitalValueSynchronous(u8 Copy_u8ChannelNum , u16 * Copy_pu16DigitalValue){

	u8 Local_u8ErroreState = STD_TYPES_OK;
	u32 Local_u32TimeOutCount = 0;

	if(Copy_u8ChannelNum < 32 && Copy_pu16DigitalValue != NULL){

		/* Clear First 5 Bits From ADMUX*/
		ADC_u8_ADMUX_REG &= 0XE0;

		/* Select Channel from First 5 Bits in ADMUX*/
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;

		/* Start Conversion*/

		SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_6);

		/* Waiting While ADC Flag =1 (Finish Conversion)*/

		while(!(GET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_4)) && (Local_u32TimeOutCount < Local_u32TimeOutCount)){

			++Local_u32TimeOutCount;
		}

		/*  Check that flag was set and we should read the value */
		if((GET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_4))){
			/* Clear Flag */
			SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_4);

			/* Read Value*/
			*Copy_pu16DigitalValue = (ADC_u16_ADC_REG);
		}
		else{
			Local_u8ErroreState=STD_TYPES_NOK;
		}

	}
	else{
		Local_u8ErroreState=STD_TYPES_NOK;
	}

	return Local_u8ErroreState;
}

#if ADC_u8_UseChain

u8   ADC_u8startChainConversion(ADC_Chain * Copy_Chain){

	u8 Local_u8ErroreState = STD_TYPES_OK;
	if(Copy_Chain -> ChainSize <= ADC_u8_Channel_7 && (Copy_Chain ->EndNotificationFunc != NULL) && (ADC_Global_u8BusyFlag == ADC_u8NotBusy) ){

		/* Set Busy Flag */

		ADC_Global_u8BusyFlag = ADC_u8Busy;

		/* Update Global Pointers */

		ADC_Global_PtrFuncEndNotChain 	= Copy_Chain -> EndNotificationFunc;

		ADC_u8ChainSize 				= Copy_Chain -> ChainSize;

		Global_u8ADCResult 				= Copy_Chain -> ArrayofADCResults;

		Global_u8ADCChain 				= Copy_Chain -> Arrayofchannels;

		/* Clear First 5 Bits From ADMUX*/
		ADC_u8_ADMUX_REG &= 0XE0;

		/* Select Channel from First 5 Bits in ADMUX*/
		ADC_u8_ADMUX_REG |= Copy_Chain -> Arrayofchannels[ADC_u8ChainIndex] ;

		/* Enable ADC Interrupt*/

		SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_3);

		/* Start Conversion*/

		SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_6);

	}
	else{
		Local_u8ErroreState = STD_TYPES_NOK;
	}
	return Local_u8ErroreState;
}
#else
u8   ADC_u8GetDigitalValueAsynchronous(u8 Copy_u8ChannelNum , void (* Copy_pfunctionNotification)(u16)){

	u8 Local_u8ErroreState = STD_TYPES_OK;
	if(Copy_u8ChannelNum < 32 && (Copy_pfunctionNotification != NULL) && (ADC_Global_u8BusyFlag == ADC_u8NotBusy) ){

		/* Set Busy Flag */

		ADC_Global_u8BusyFlag = ADC_u8Busy;

		/* Update Global Pointers */

		ADC_Global_PtrFuncEndNotificationFunction = Copy_pfunctionNotification;

		/* Clear First 5 Bits From ADMUX*/
		ADC_u8_ADMUX_REG &= 0XE0;

		/* Select Channel from First 5 Bits in ADMUX*/
		ADC_u8_ADMUX_REG |= Copy_u8ChannelNum;

		/* Enable ADC Interrupt*/

		SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_3);

		/* Start Conversion*/

		SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_6);

	}
	else{
		Local_u8ErroreState = STD_TYPES_NOK;
	}
	return Local_u8ErroreState;
}
#endif

#define _INTR_ATTRS used,externally_visible
/* ISR Function For ADC */
void __vector_16(void)__attribute__((signal,_INTR_ATTRS));
void __vector_16(void){

#if ADC_u8_UseChain


	if(ADC_Global_PtrFuncEndNotChain != NULL){

			/* Update ADC Result and move on to the next Channel*/
			Global_u8ADCResult[ADC_u8ChainIndex] = ADC_u16_ADC_REG;

			/* Move to start conversion for the next Channel*/
			ADC_u8ChainIndex++;

			/* Check if index is out of range or no in ADC Chain Array */
			if(ADC_u8ChainIndex < ADC_u8ChainSize){

				/* Clear First 5 Bits From ADMUX*/
				ADC_u8_ADMUX_REG &= 0XE0;

				/* Select Channel from First 5 Bits in ADMUX*/
				ADC_u8_ADMUX_REG |=Global_u8ADCChain[ADC_u8ChainIndex] ;

				/* Start Conversion*/

				SET_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_6);
			}
			else{
				/*Disable Interrupt*/

				CLR_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_3);

				/* Set Busy Flag
				 * To enable Calling  Function again that it enable interrupt again
				 * when we call function to read another ADC chain Value
				 * */
				ADC_Global_PtrFuncEndNotChain();
				ADC_u8ChainIndex = 0;
				ADC_Global_u8BusyFlag = ADC_u8NotBusy;
			}
		}

#else
	if(ADC_Global_PtrFuncEndNotificationFunction != NULL){

		/* Call End Notification Function to tell user that ADC Conversion was Finish
		 * And we will passing ADC_u16_ADC_REG Digital Value
		 * */
		ADC_Global_PtrFuncEndNotificationFunction((ADC_u16_ADC_REG));

		/*Disable Interrupt*/

		CLR_BIT(ADC_u8_ADCSRA_REG,ADC_u8_Channel_3);

		/* Set Busy Flag
		 * To enable Calling Asynchronous Function again that it enable interrupt again
		 * when we call Asynchronous function to read another ADC Value
		 * */

		ADC_Global_u8BusyFlag = ADC_u8NotBusy;
	}
#endif

}

/*
 * u8 ADC_u8SetCallBackFunc(void (*Copy_PtrFunc)(void)){

	u8 Local_u8ErroreState = STD_TYPES_OK;

	if(Copy_PtrFunc != NULL){

		ADC_Global_PtrFuncEndNotificationFunction=Copy_PtrFunc;
	}
	else{
		Local_u8ErroreState = STD_TYPES_NOK;
	}
	return Local_u8ErroreState;
}
*/
