#include <16F877A.h>
#device ADC=10

#FUSES PUT                      //Power Up Timer
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOPROTECT                //Code not protected from reading

#use delay(crystal=8MHz)
#define S1   PIN_B0
#define S2   PIN_B1
#define S3   PIN_B2
#define LED  PIN_D7
#define LED8  PIN_B7
#define LED9  PIN_B6
#define LED10  PIN_B5
#define LED11  PIN_B4


