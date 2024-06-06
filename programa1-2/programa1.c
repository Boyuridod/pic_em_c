#include <programa1.h>

int1 ligado = 0;
int8 qual_display = -1, tempo = 0;
int8 centena = 0, dezena = 0, unidade = 0, decimal = 0;
int8 conversao[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};

#INT_TIMER0
void  TIMER0_isr(VOID) {

   tempo++;

   if(tempo == 100 && ligado == 1){

      decimal++;

      if(decimal == 10){

         decimal = 0;
         unidade++;

      }

      if(unidade == 10){

         unidade = 0;
         dezena++;

      }

      if(dezena == 10){

         dezena = 0;
         centena++;

      }

      if(centena == 10){

         decimal = unidade = dezena = centena = 0;

      }
      
      tempo = 0;

   }

   qual_display++;

   if(qual_display == 0){

      output_low(DISPLAY4);
      output_high(DISPLAY1);      
      output_d(conversao[decimal]);

   }

   else if(qual_display == 1){

      output_low(DISPLAY1);
      output_high(DISPLAY2);   
      output_d(conversao[unidade]);
      output_high(PONTO);

   }

   else if(qual_display == 2){
  
      output_low(DISPLAY2);
      output_high(DISPLAY3);      
      output_d(conversao[dezena]);

   }

   else if(qual_display == 3){
 
      output_low(DISPLAY3);
      output_high(DISPLAY4);      
      output_d(conversao[centena]);

      qual_display = -1;

   }

}

void main(){
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_BIT); //1, 0 ms overflow
   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   WHILE(TRUE){
       
      if(!input(BTN_INICIAR)){
      
         ligado = 1;
         
      }
      
      else if(!input(BTN_PARAR)){
      
         ligado = tempo = 0;
      
      }
      
      else if(!input(BTN_ZERAR)){
      
         if(ligado == 0){
      
            decimal = unidade = dezena = centena = 0;
            tempo = 0;
         
         }
      
      }
   }
}
