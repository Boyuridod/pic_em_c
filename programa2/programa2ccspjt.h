#include <16F877A.h>
#device ADC=10

#FUSES PUT                      //Power Up Timer
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES NOPROTECT                //Code not protected from reading

#use delay(crystal=4MHz)
#define SENS_TEMPERATURA   PIN_A0
#define POTENCIOMETRO   PIN_A1
#define DISPLAY1  PIN_B4
#define DISPLAY2  PIN_B5
#define DISPLAY3  PIN_B6
#define DISPLAY4  PIN_B7
#define PONTO PIN_D7
