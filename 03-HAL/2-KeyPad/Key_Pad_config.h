/*****************************************************************/
/****************** Name    : Ahmed Zaky *************************/
/****************** Date    : 13/1/2021  *************************/
/****************** Version : 1.0V       *************************/
/****************** SWC     : KEY_PAD    *************************/
/*****************************************************************/
#ifndef KEY_PAD_CONFIG_H
#define KEY_PAD_CONFIG_H


#define  KEY_PAD_u8_Rows_Number            4
#define  KEY_PAD_u8_Cols_Number            4


#define KEY_PAD_Values      {{'1','2','3','/'},\
							 {'4','5','6','*'},\
							 {'7','8','9','-'},\
							 {'%','0','=','+'}}
							 
#define  KEY_PAD_RealPortForCol        	{KEY_PAD_u8_C1_PORT,KEY_PAD_u8_C2_PORT,KEY_PAD_u8_C3_PORT,KEY_PAD_u8_C4_PORT}

#define  KEY_PAD_RealPortForRow			{KEY_PAD_u8_R1_PORT,KEY_PAD_u8_R2_PORT,KEY_PAD_u8_R3_PORT,KEY_PAD_u8_R4_PORT}

#define  KEY_PAD_RealCol				{KEY_PAD_u8_C1_PIN,KEY_PAD_u8_C2_PIN,KEY_PAD_u8_C3_PIN,KEY_PAD_u8_C4_PIN}

#define  KEY_PAD_RealRow				{KEY_PAD_u8_R1_PIN,KEY_PAD_u8_R2_PIN,KEY_PAD_u8_R3_PIN,KEY_PAD_u8_R4_PIN}

/* KEY_PAD Configurtion 
		Rows = Output Pins
		Col  = Input  Pins
*/

#define KEY_PAD_u8_R1_PIN               DIO_u8_PIN7
#define KEY_PAD_u8_R1_PORT              DIO_u8_PORTB

#define KEY_PAD_u8_R2_PIN               DIO_u8_PIN6
#define KEY_PAD_u8_R2_PORT              DIO_u8_PORTB

#define KEY_PAD_u8_R3_PIN               DIO_u8_PIN5
#define KEY_PAD_u8_R3_PORT              DIO_u8_PORTB

#define KEY_PAD_u8_R4_PIN               DIO_u8_PIN4
#define KEY_PAD_u8_R4_PORT              DIO_u8_PORTB

#define KEY_PAD_u8_C1_PIN               DIO_u8_PIN0
#define KEY_PAD_u8_C1_PORT              DIO_u8_PORTB
				   
#define KEY_PAD_u8_C2_PIN               DIO_u8_PIN1
#define KEY_PAD_u8_C2_PORT              DIO_u8_PORTB
				   
#define KEY_PAD_u8_C3_PIN               DIO_u8_PIN2
#define KEY_PAD_u8_C3_PORT              DIO_u8_PORTB
				   
#define KEY_PAD_u8_C4_PIN               DIO_u8_PIN3
#define KEY_PAD_u8_C4_PORT              DIO_u8_PORTB


#endif
