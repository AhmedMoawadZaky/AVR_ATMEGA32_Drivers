/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 17/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : EXTI       *************************/
/*****************************************************************/

/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

/* Global Array of Pointers To Function*/
static void (*Global_APtrToFunc[3])(void) ={NULL,NULL,NULL};

u8 EXTI_u8ExtiEnable(u8 Copy_u8INTNum,u8 Copy_u8INTSrc){
	
	u8 Local_u8ErroreState = STD_TYPES_OK;
	
	switch(Copy_u8INTNum){
		
		case EXTI_u8_INT0:
			switch(Copy_u8INTSrc){
				case EXTI_u8_FALLING_EDGE:
					SET_BIT(EXTI_u8MCUCR_REG,1);
					CLR_BIT(EXTI_u8MCUCR_REG,0);
					SET_BIT(EXTI_u8GICR_REG,6);
					break;
					
				case EXTI_u8_RISING_EDGE:
					SET_BIT(EXTI_u8MCUCR_REG,1);
					SET_BIT(EXTI_u8MCUCR_REG,0);
					SET_BIT(EXTI_u8GICR_REG,6);

					break;
					
				case EXTI_u8_ANY_LOGICAL_CHAINGE:
					CLR_BIT(EXTI_u8MCUCR_REG,1);
					SET_BIT(EXTI_u8MCUCR_REG,0);
					SET_BIT(EXTI_u8GICR_REG,6);

					break;
					
				case EXTI_u8_LOW_LEVEL:
				
					CLR_BIT(EXTI_u8MCUCR_REG,1);
					CLR_BIT(EXTI_u8MCUCR_REG,0);					
					SET_BIT(EXTI_u8GICR_REG,6);

					break;
					
				default:
						Local_u8ErroreState = STD_TYPES_NOK;

			}
		
		break;
		
		case EXTI_u8_INT1:
			switch(Copy_u8INTSrc){
				case EXTI_u8_FALLING_EDGE:
					SET_BIT(EXTI_u8MCUCR_REG,3);
					CLR_BIT(EXTI_u8MCUCR_REG,2);					
					SET_BIT(EXTI_u8GICR_REG,7);

					break;
					
				case EXTI_u8_RISING_EDGE:
					SET_BIT(EXTI_u8MCUCR_REG,3);
					SET_BIT(EXTI_u8MCUCR_REG,2);
					SET_BIT(EXTI_u8GICR_REG,7);
					
					break;
					
				case EXTI_u8_ANY_LOGICAL_CHAINGE:
					CLR_BIT(EXTI_u8MCUCR_REG,3);
					SET_BIT(EXTI_u8MCUCR_REG,2);
					SET_BIT(EXTI_u8GICR_REG,7);
					
					break;
					
				case EXTI_u8_LOW_LEVEL:
					CLR_BIT(EXTI_u8MCUCR_REG,3);
					CLR_BIT(EXTI_u8MCUCR_REG,2);
					SET_BIT(EXTI_u8GICR_REG,7);
					
					break;
					
				default:
						Local_u8ErroreState = STD_TYPES_NOK;

			}
		
		break;
		
		case EXTI_u8_INT2:
			switch(Copy_u8INTSrc){
				case EXTI_u8_FALLING_EDGE:
					CLR_BIT(EXTI_u8MCUCSR_REG,6);
					SET_BIT(EXTI_u8GICR_REG,5);
					break;
					
				case EXTI_u8_RISING_EDGE:
					SET_BIT(EXTI_u8MCUCSR_REG,6);
					SET_BIT(EXTI_u8GICR_REG,5);
					break;
					
				
				default:
						Local_u8ErroreState = STD_TYPES_NOK;

			}
		
			break;
		
		default:
			Local_u8ErroreState = STD_TYPES_NOK;

	}
	
	return Local_u8ErroreState;
}
u8 EXTI_u8ExtiDisable(u8 Copy_u8INTNum){
	
	u8 Local_u8ErroreState = STD_TYPES_OK;

	switch(Copy_u8INTNum){
		case EXTI_u8_INT0:
			CLR_BIT(EXTI_u8GICR_REG,6);
			break;
		
		case EXTI_u8_INT1:
			CLR_BIT(EXTI_u8GICR_REG,7);
			break;
			
		case EXTI_u8_INT2:
			CLR_BIT(EXTI_u8GICR_REG,5);
			break;
			
		default:
			Local_u8ErroreState = STD_TYPES_NOK;

	}
	
	return Local_u8ErroreState;
}

u8 EXTI_u8SetCallBackFunc(void (*Copy_PtrFunc)(void),u8 Copy_u8EXTINum){

	u8 Local_u8ErroreState = STD_TYPES_OK;

	if(Copy_u8EXTINum <= EXTI_u8_INT2 && Copy_PtrFunc != NULL){

		Global_APtrToFunc[Copy_u8EXTINum]=Copy_PtrFunc;
	}
	else{
		Local_u8ErroreState = STD_TYPES_NOK;
	}
	return Local_u8ErroreState;
}

#define _INTR_ATTRS used,externally_visible


/* ISR Function For EXT_INT0 */
void __vector_1(void)__attribute__((signal,_INTR_ATTRS));
void __vector_1(void){

	if(Global_APtrToFunc[EXTI_u8_INT0] != NULL){
		Global_APtrToFunc[EXTI_u8_INT0]();
	}
	else{

	}
}

/* ISR Function For EXT_INT1 */
void __vector_2(void)__attribute__((signal,_INTR_ATTRS));
void __vector_2(void){

	if(Global_APtrToFunc[EXTI_u8_INT1] != NULL){
			Global_APtrToFunc[EXTI_u8_INT1]();
	}
	else{

	}
}

/* ISR Function For EXT_INT2 */
void __vector_3(void)__attribute__((signal,_INTR_ATTRS));
void __vector_3(void){

	if(Global_APtrToFunc[EXTI_u8_INT2] != NULL){
			Global_APtrToFunc[EXTI_u8_INT2]();
		}
	else{

	}

}
