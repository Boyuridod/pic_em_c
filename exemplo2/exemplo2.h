#include <16F628A.h>

#FUSES PUT                   	//Power Up Timer
#FUSES MCLR                  	//Master Clear pin enabled
#FUSES BROWNOUT              	//Reset when brownout detected
#FUSES NOLVP                 	//No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                 	//No EE protection
#FUSES NOPROTECT             	//Code not protected from reading

#use delay(internal=4MHz)
#use FIXED_IO( A_outputs=PIN_A0 )
#define LED	PIN_A0
#define BTN_LIGA	PIN_A1
#define BTN_DESLIGA	PIN_A2


