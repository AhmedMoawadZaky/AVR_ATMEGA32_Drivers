/*********************************************************************************/
/** Author    : Ahmed Zaky                                                      **/
/** Version   : V01                                                             **/
/** Date      : 15 August 2020                                                  **/
/*********************************************************************************/
#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

typedef struct{
	u8 PortNumb;
	u8 PinNumb;
	u8 ConnectionType;
}LED_Temp;

void LED_voidOnMode		(LED_Temp * Copy_u8Data);
void LED_voidOffMode	(LED_Temp * Copy_u8Data);
void LED_voidToglMode	(LED_Temp * Copy_u8Data);

/* Options For LED:    	
				Active_High
				Active_Low
               			   */
#define			Active_Low		0
#define			Active_High		1

#endif
