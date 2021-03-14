/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 17/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : EXTI       *************************/
/*****************************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#define EXTI_u8_INT0         0  
#define EXTI_u8_INT1         1
#define EXTI_u8_INT2         2 


#define EXTI_u8_FALLING_EDGE        		0  
#define EXTI_u8_RISING_EDGE         		1
#define EXTI_u8_ANY_LOGICAL_CHAINGE         2 
#define EXTI_u8_LOW_LEVEL         			3 

u8 EXTI_u8ExtiEnable					(u8 Copy_u8INTNum,u8 Copy_u8INTSrc);
u8 EXTI_u8ExtiDisable					(u8 Copy_u8INTNum);
u8 EXTI_u8SetCallBackFunc				(void (*Copy_PtrFunc)(void),u8 Copy_u8EXTINum);

#endif
