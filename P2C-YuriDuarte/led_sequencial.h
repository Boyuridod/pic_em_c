#include <16F877A.h>
#device ADC=10

#FUSES PUT                   	//Power Up Timer
#FUSES BROWNOUT              	//Reset when brownout detected
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                 	//No EE protection
#FUSES NOWRT                 	//Program memory not write protected
#FUSES NOPROTECT             	//Code not protected from reading

#use delay(crystal=8MHz)
#use FIXED_IO( B_outputs=PIN_B7,PIN_B6,PIN_B5,PIN_B4,PIN_B3,PIN_B2,PIN_B1,PIN_B0 )
#define POTENCIOMETRO	PIN_A0
#define BTN_LIGA	PIN_A1
#define BTN_MUDA	PIN_A2
#define LED0	PIN_B0
#define LED1	PIN_B1
#define LED2	PIN_B2
#define LED3	PIN_B3
#define LED4	PIN_B4
#define LED5	PIN_B5
#define LED6	PIN_B6
#define LED7	PIN_B7


