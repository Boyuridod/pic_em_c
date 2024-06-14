#include <p1-yuriduarte.h>

int1 fim_tempo = 0, isLigado = 0;
int8 filtro = 0;
int8 cod_frequencia = 0, frequencia[11] = {500, 250, 200, 150, 120, 100, 80, 60, 50, 40};
int8 conversao[11] = {254, 56, 221 ,125, 59, 119, 247, 60, 255, 127};
int16 tempo = 500;

#INT_TIMER0
void  TIMER0_isr(void){
   
   tempo--;
   
   if(tempo == 0){
   
      tempo = frequencia[cod_frequencia];
      
      fim_tempo = 1;
   
   }
   
}

void main(){
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_BIT);      //1,0 ms overflow

   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   
   output_b(conversao[cod_frequencia]);
   output_low(LED);

   while(TRUE){

      if(isLigado == 1){
      
         if(fim_tempo){
         
            output_toggle(LED);
            
            fim_tempo = 0;
         
         }
         
         if(!input(BTN_DESLIGA)){
      
            isLigado = 0;
            
            output_low(LED);
         
         }
      
      }
      
      else{
      
         if(!input(BTN_LIGA)){
      
            isLigado = 1;
            
            output_high(LED);
         
         }
      
         if(!input(BTN_MAIS)){
         
            for(filtro = 0; filtro <= 100; filtro++){
            
               if(!input(BTN_MAIS))
                  filtro = 0;
            
            }
         
            if(cod_frequencia < 9){
            
               cod_frequencia++;
               
               output_b(conversao[cod_frequencia]);
            
            }
         
         }
         
         if(!input(BTN_MENOS)){
         
            for(filtro = 0; filtro <= 100; filtro++){
            
               if(!input(BTN_MENOS))
                  filtro = 0;
            
            }
         
            if(cod_frequencia > 0){
            
               cod_frequencia--;
               
               output_b(conversao[cod_frequencia]);
            
            }
         
         }
         
      }
      
   }

}
