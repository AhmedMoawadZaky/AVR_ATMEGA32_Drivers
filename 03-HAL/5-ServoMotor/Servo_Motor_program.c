/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 3/1/2021   *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : Servo Motor   **********************/
/*****************************************************************/

/* MCAL */
#include "TMR_interface.h"

/* HAL */
#include "Servo_Motor_interface.h"
#include "Servo_Motor_private.h"
#include "Servo_Motor_config.h"

/* PORT_D5 OC1A*/

void Servo_voidInit(void){
	
	TMR_voidSetCompareeMatchOcr1A(Servo_Angle180);
	TMR_voidTime1Init();
	
}

void Servo_voidSetAngle(u8 Angle){
		
	TMR_voidSetCompareeMatchOcr1A(Servo_Angle0 + ( Servo_2500_Sub_450_Div_180 * Angle));
	
}