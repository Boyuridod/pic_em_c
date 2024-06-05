#include <programa1.h>
#include <lcd.c>
int1 step = 0;
float count = 0;
int8 i = 0;
int8 num = 0;

void set(int8 aux){
   if(aux == 0)
      output_d(0x3f);
   if(aux == 1)
      output_d(0x06);
   if(aux == 2)
      output_d(0x57);
   if(aux == 3)
      output_d(0x4f);
   if(aux == 4)
      output_d(0x66);
   if(aux == 5)
      output_d(0x5D);
   if(aux == 6)
      output_d(0x70);
   if(aux == 7)
      output_d(0x00);
   if(aux == 8)
      output_d(0x7f);
   if(aux == 9)
      output_d(0x6f);
}

#INT_TIMER0

void  TIMER0_isr(VOID) {
   if(!S1){
      i++;
   }
   set(i);
   if(num == 0){
         output_low(LED11);
         output_high(LED8);
   }else if(num == 1){
         output_low(LED8);
         output_high(LED9);
   }else if(num == 2){
         output_low(LED9);
         output_high(LED10);
   }else if(num == 3){
         output_low(LED10);
         output_high(LED11);
   }
   num+=1;
   if(num == 4){
      num = 0;
   }
}
void main(){
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_BIT); //1, 0 ms overflow
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   WHILE(TRUE){  
      
   }
}
