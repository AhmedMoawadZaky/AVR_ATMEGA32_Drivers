/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 21/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : UART       *************************/
/*****************************************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H


#define      UART_u8_UDR_REG			*((volatile u8 *)0X2C)

#define      UART_u8_UCSRA_REG			*((volatile u8 *)0X2B)

#define      UART_u8_UCSRB_REG			*((volatile u8 *)0X2A)

#define      UART_u8_UBRRL_REG			*((volatile u8 *)0X29)

/* URSEL if this bit =1 we update her */
#define      UART_u8_UCSRC_REG			*((volatile u8 *)0X40)

/* URSEL if this bit =0 we update her */
#define      UART_u8_UBRRH_REG			*((volatile u8 *)0X40)


#endif