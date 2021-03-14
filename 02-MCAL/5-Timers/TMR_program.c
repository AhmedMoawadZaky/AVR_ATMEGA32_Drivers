/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 21/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : TMR        *************************/
/*****************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TMR_interface.h"
#include "TMR_private.h"
#include "TMR_config.h"

/* Global Pointers to Function */
static void(*TMR_PfTimer0OvfCallBack)(void) = NULL;
static void(*TMR_PfTimer0CTCCallBack)(void) = NULL;

void TMR_voidTime0Init(void)
{
	/* Timer 0 Init */
	//	/* Select Mode = Normal Mode */
	//	CLR_BIT(TMR_u8_TMR0_TCCR0_REG,6);
	//	CLR_BIT(TMR_u8_TMR0_TCCR0_REG,3);

	//	/* Init Timer register with the preload Value */
	//	TMR_u8_TMR0_TCNT0_REG = TMR_u8_TMR0_PRELOAD_VALUE;


	/* Select Mode = CTC Mode */
	CLR_BIT(TMR_u8_TMR0_TCCR0_REG,6);
	SET_BIT(TMR_u8_TMR0_TCCR0_REG,3);

	//	/* Enable OVF Interrupt */
	//	SET_BIT(TMR_u8_TMR_TIMSK_REG,0);


	/* Enable CTC Interrupt */
	SET_BIT(TMR_u8_TMR_TIMSK_REG,1);
	/* Select Prescaler Value = 8 */
	CLR_BIT(TMR_u8_TMR0_TCCR0_REG,2);
	SET_BIT(TMR_u8_TMR0_TCCR0_REG,1);
	CLR_BIT(TMR_u8_TMR0_TCCR0_REG,0);
}

u8   TMR_u8TMR0OVFSetCallBack(void(*Copy_PfCallBack)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_PfCallBack != NULL)
	{
		TMR_PfTimer0CTCCallBack = Copy_PfCallBack;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}

u8   TMR_u8TMR0CTCSetCallBack(void(*Copy_PfCallBack)(void))
{
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_PfCallBack != NULL)
	{
		TMR_PfTimer0OvfCallBack = Copy_PfCallBack;
	}
	else
	{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}


/* Prototype For ISR of TMR 0 OVR */
void __vector_11(void)   __attribute__((signal));
void __vector_11(void)
{
	static u16 Local_u16Counter = 0;
	Local_u16Counter++;
	if(Local_u16Counter == TMR_u16_TMRO_OVERFLOW_COUNTER)
	{
		/* Set Preload Value */
		TMR_u8_TMR0_TCNT0_REG = TMR_u8_TMR0_PRELOAD_VALUE;
		/* Clear Counter */
		Local_u16Counter = 0;
		/* Call Call Back function */
		if(TMR_PfTimer0OvfCallBack != NULL)
		{
			TMR_PfTimer0OvfCallBack();
		}

	}
}

/* Prototype For ISR of TMR 0 CTC */
void __vector_10(void)   __attribute__((signal));
void __vector_10(void)
{
	static u16 Local_u16Counter = 0;
	Local_u16Counter++;
	if(Local_u16Counter == 10000)
	{
		Local_u16Counter = 0;
		/* Call Call Back function */
		if(TMR_PfTimer0CTCCallBack != NULL)
		{
			TMR_PfTimer0CTCCallBack();
		}

	}
}
