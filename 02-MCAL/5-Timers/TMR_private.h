/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 21/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : TMR        *************************/
/*****************************************************************/
#ifndef TMR_PRIVATE_H
#define TMR_PRIVATE_H

/* Timer0 Registers */
#define TMR_u8_TMR0_TCCR0_REG                   *((volatile u8 *)0x53)
#define TMR_u8_TMR0_TCNT0_REG                   *((volatile u8 *)0x52)
#define TMR_u8_TMR0_OCR0_REG                    *((volatile u8 *)0x5C)



#define TMR_u8_TMR_TIMSK_REG                    *((volatile u8 *)0x59)
#define TMR_u8_TMR_TIFR_REG                     *((volatile u8 *)0x58)

#endif