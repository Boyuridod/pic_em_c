#include <exemplo2.h>

void main(){

   output_low(LED);

   while(TRUE){

      if(input(BTN_LIGA) == 0){
      
         output_high(LED);
      
      }
      
      if(input(BTN_DESLIGA) == 0){
      
         output_low(LED);
      
      }

   }

}
