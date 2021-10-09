/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 21/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : UART       *************************/
/*****************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

/* Busy Flag*/
static u8 UART_Global_u8BusyFlag=UART_u8NotBusy;
/* Index Of array on Buffer */
static u8 UART_u8BufferIndex;
static u8 UART_u8BufferSize;
static u8 *Global_u8UARTBuffer  = NULL;

/* Index Of array on Buffer */
static u8 UART_u8RBufferIndex;
static u8 UART_u8RBufferSize;
static u8 *Global_u8UARTRBuffer  = NULL;


static void (*UART_Global_PtrFuncEndNot)(void) 				=NULL;
static void (*UART_Global_PtrResiveFuncEndNot)(void) 	    =NULL;

void UART_voidUARTInit(void)
{
	/*
	 * bit 7 = 1 to write UCSRC
	 * Select UART Not USART bit 6 =0
	 * bit 5 = 0 & bit 4= 0 for no parity
	 * bit 3 = 0 one stop bit
	 * bit 1 = 1 bit 2 = 1 for 8 bit mode
	 */
	UART_u8_UCSRC_REG =0b10000110;
	
	/*
	 * in UCSRB
	 * bit 2 =0 relative to 8 bit mode
	 *bit 4 =0  resave enable & bit 3 =1 transmit enable
	 *set bit 6 & 7 to Disable Inttrupt
	 */
	CLR_BIT(UART_u8_UCSRB_REG,2);
	SET_BIT(UART_u8_UCSRB_REG,3);
	SET_BIT(UART_u8_UCSRB_REG,4);
	CLR_BIT(UART_u8_UCSRB_REG,6);
	CLR_BIT(UART_u8_UCSRB_REG,7);
	/*
	 * U2X bit 1 in UCSRA = 1 to controal BudRate 8
	 */
	SET_BIT(UART_u8_UCSRA_REG,1);
	UART_u8_UBRRL_REG=0x67;
	UART_u8_UBRRH_REG=0x00;

}
void UART_vidSend(u8 data){

	/*
	 * awl ma y5alsb3t bykon el flag =1
	 *
	 */
	UART_u8_UDR_REG=data;
	while(GET_BIT(UART_u8_UCSRA_REG,5)==0);

}

u8 UART_u8Resive(void){

	/*
	 * awl ma yst2bl bykon el flag =1
	 *
	 */
	while(GET_BIT(UART_u8_UCSRA_REG,7)==0);

	return UART_u8_UDR_REG;
}

u8 	UART_u8SendBufferSynchronous(u8 * Copy_pu8Buffer,u8 Copy_u8BufferSize){
	u8 Local_u8ErroreState = STD_TYPES_OK,Local_u8IterOnBuffer;
	
	if(Copy_pu8Buffer != NULL){
		for(Local_u8IterOnBuffer = 0; Local_u8IterOnBuffer < Copy_u8BufferSize ;++Local_u8IterOnBuffer){
			
			UART_vidSend(Copy_pu8Buffer[Local_u8IterOnBuffer]);
		}
	}
	else{
		Local_u8ErroreState = STD_TYPES_NOK;
	}
	return Local_u8ErroreState;
}

u8 	UART_u8SendBufferASynchronous(u8 * Copy_pu8Buffer ,u8 Copy_u8BufferSize, void (* Copy_pfunctionNotification)(void)){
	
	u8 Local_u8ErroreState = STD_TYPES_OK;
	if(Copy_pu8Buffer != NULL && (Copy_pfunctionNotification != NULL) && (UART_Global_u8BusyFlag == UART_u8NotBusy) ){

		/* Set Busy Flag */

		UART_Global_u8BusyFlag = UART_u8Busy;

		/* Update Global Pointers */

		UART_Global_PtrFuncEndNot 		= Copy_pfunctionNotification;

		UART_u8BufferSize 				= Copy_u8BufferSize;


		Global_u8UARTBuffer 			= Copy_pu8Buffer;

		UART_u8BufferIndex=0;
		
		/* Send Data by Assign UDR Register */
		UART_u8_UDR_REG= Global_u8UARTBuffer[UART_u8BufferIndex] ;

		/* Enable UART Empty UDR Interrupt*/

		SET_BIT(UART_u8_UCSRB_REG,5);

	}
	else{
		Local_u8ErroreState = STD_TYPES_NOK;
	}
	return Local_u8ErroreState;

}

u8 	UART_u8ResiveBufferASynchronous(u8 * Copy_pu8Buffer ,u8 Copy_u8BufferSize, void (* Copy_pfunctionNotification)(void)){

	u8 Local_u8ErroreState = STD_TYPES_OK;
	if(Copy_pu8Buffer != NULL && (Copy_pfunctionNotification != NULL) && (UART_Global_u8BusyFlag == UART_u8NotBusy) ){

		/* Set Busy Flag */

		UART_Global_u8BusyFlag = UART_u8Busy;

		/* Update Global Pointers */

		UART_Global_PtrResiveFuncEndNot 		= Copy_pfunctionNotification;

		UART_u8RBufferSize 						= Copy_u8BufferSize;

		Global_u8UARTRBuffer 					= Copy_pu8Buffer;

		UART_u8RBufferIndex=0;

		/* Enable UART RX Complete UDR Interrupt*/

		SET_BIT(UART_u8_UCSRB_REG,7);
	}
	else{
		Local_u8ErroreState = STD_TYPES_NOK;
	}
	return Local_u8ErroreState;

}

u8 	UART_u8ResiveBufferSynchronous(u8 * Copy_pu8Buffer,u8 Copy_u8BufferSize){
	u8 Local_u8ErroreState = STD_TYPES_OK,Local_u8IterOnBuffer;

	if(Copy_pu8Buffer != NULL){
		for(Local_u8IterOnBuffer = 0; Local_u8IterOnBuffer < Copy_u8BufferSize ;++Local_u8IterOnBuffer){

			Copy_pu8Buffer[Local_u8IterOnBuffer] = UART_u8Resive();
		}
	}
	else{
		Local_u8ErroreState = STD_TYPES_NOK;
	}
	return Local_u8ErroreState;
}


#define _INTR_ATTRS used,externally_visible
void __vector_14(void)__attribute__((signal,_INTR_ATTRS));
void __vector_14(void){
	
	if(UART_Global_PtrFuncEndNot != NULL){
		
		++UART_u8BufferIndex;
		
		if(UART_u8BufferIndex != UART_u8BufferSize){
			
			UART_u8_UDR_REG= Global_u8UARTBuffer[UART_u8BufferIndex] ;

		}
		else{
			
			UART_Global_PtrFuncEndNot();
			
			/* Disable Interrupt */ 
			CLR_BIT(UART_u8_UCSRB_REG,5);

			UART_u8BufferIndex =0;
			Global_u8UARTBuffer =NULL;
			/* Set Flag */
			UART_Global_u8BusyFlag = UART_u8NotBusy;
		}
	}
}

void __vector_13(void)__attribute__((signal,_INTR_ATTRS));
void __vector_13(void){

	if(UART_Global_PtrResiveFuncEndNot != NULL){

		Global_u8UARTRBuffer[UART_u8RBufferIndex] = UART_u8_UDR_REG;
		++UART_u8RBufferIndex;

		if(UART_u8RBufferIndex == UART_u8RBufferSize){

			UART_Global_PtrResiveFuncEndNot();

			/* Disable Interrupt */
			CLR_BIT(UART_u8_UCSRB_REG,7);

			UART_u8RBufferIndex =0;
			Global_u8UARTRBuffer =NULL;
			/* Set Flag */
			UART_Global_u8BusyFlag = UART_u8NotBusy;
		}
	}
}
