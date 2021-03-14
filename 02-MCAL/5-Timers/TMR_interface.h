/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 21/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : TMR        *************************/
/*****************************************************************/
#ifndef TMR_INTERFACE_H
#define TMR_INTERFACE_H

void TMR_voidTime0Init(void);

u8   TMR_u8TMR0OVFSetCallBack(void(*Copy_PfCallBack)(void));

u8   TMR_u8TMR0CTCSetCallBack(void(*Copy_PfCallBack)(void));

#endif
