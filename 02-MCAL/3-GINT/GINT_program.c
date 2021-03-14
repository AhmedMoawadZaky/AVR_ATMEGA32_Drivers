/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 17/1/2021   *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : GINT       *************************/
/*****************************************************************/

/* Lib Layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "GINT_interface.h"
#include "GINT_private.h"
#include "GINT_config.h"


void GINT_voidEnable(void){
	
	SET_BIT(GINT_u8_SREG,7);
	
}
void GINT_voidDisable(void){
		
	CLR_BIT(GINT_u8_SREG,7);

}