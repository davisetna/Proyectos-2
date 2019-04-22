/* ###################################################################
**     Filename    : main.c
**     Project     : potenciometro ADC
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2019-02-16, 19:08, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "AD1.h"
#include "TI1.h"
#include "AS1.h"
#include "Bit1.h"
#include "Bit2.h"
#include "Bit3.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
//Declaramos variables a utilizar

char i;
char f=0; //Declaramos un flag
unsigned char a;//Variables a utilizar para cada byte a enviar
unsigned char b;
unsigned char c;
unsigned char d;
unsigned char block[4] ={0x00,0x00,0x00,0x00};

bool s_digital_1;//Variables booleanas para cada canal digital 
bool s_digital_2;
bool s_digital_3;
unsigned char trama1[2] = {0x00, 0x00};//Vectores que reciben los valores del ADC 
unsigned char trama2[2] = {0x00, 0x00};
unsigned char CodError; //Variable en la que se almacena el valor del error de la funcion SendBlock


void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  AD1_Start();//Inicializa el puerto serial
  
  for (;;){
	  
	  if(f){
		  // channel 0 
		  	  AD1_MeasureChan(TRUE ,0); //Mide el canal 1
			  AD1_GetChanValue(0, &trama1);//Guarda el valor leido en trama1

		  	  b = trama1[1] >> 6; // el bloque 2 se shiftea a la derecha para que queden los 2 bits al final (000000XX)
			  a = trama1 [0]<< 2;  // el bloque 1 llega como 0000XXXX, shifteo dos veces a la izquierda para poder tener espacio
			  a = a | b;  // sumo ambas tramas para concatenar los 6 bits mas significativos en el primer byte
			  	
			  b = trama1[1] << 2 ; // al bloque dos le quito los 2 bits mas significativos, shifteando a la izquierda
			  b= b>>2;  // lo vuelvo a shiftear a la derecha para dejar espacio al bit digital y a la flag 1
			  b= b | 0x80;  // 1 0 [5-0]  // le sumo la flag 1 al inicio del byte
			    
		//channel 1
			  AD1_MeasureChan(TRUE ,1); //Mide el canal 2
			  AD1_GetChanValue(1, &trama2); //Guarda el valor leido en trama2
			  //Se hace un procedimiento similar al canal 1 solo que se hace con trama2
			  c = trama2[1] >> 6; 
			  d = trama2 [0]<< 2;  
			  c = c | d;
			  c = c | 0x80;
				  	
			  d = trama2[1] << 2 ;
			  d= d>>2;
			  d= d | 0x80;  // 1 0 [5-0]
			  
			  //Canales digitales
			  
			  s_digital_1 = Bit1_NegVal();//
			  if(s_digital_1){ //Si el valor digital 1 esta activado se coloca en 1 el bit 6 del bloque b( segundo a enviar
				b = b | 0x40;
				}

			  s_digital_2= Bit2_GetVal();
			  if(s_digital_2){ //Si el valor digital 2 esta activado se coloca en 1 el bit 7 del bloque c 
				c = c | 0x40;
				}		
				
			  s_digital_3= Bit3_GetVal();
			  if(s_digital_3){
				d=d|0x40;
				}
				
			  block[0]=a;
			  block[1]=b;
			  block[2]=c;
			  block[3]=d;
			  
				do{ 
					CodError = AS1_SendBlock(&block, 4, &i);
				} while (CodError != ERR_OK);
				
				/*do{
					CodError = AS1_SendBlock(&b, 1, &i);
				} while (CodError != ERR_OK);
				do{
					CodError = AS1_SendBlock(&c, 1, &i);
				} while (CodError != ERR_OK);
				
				do{
					CodError = AS1_SendBlock(&d, 1, &i);
				} while (CodError != ERR_OK);*/
			   f=0;
	  }

}
  
  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
