#include <main.h>

int8 teste;

void main(){

   output_low(LED);

   while(TRUE){

      if(input(BTN_LIGA) == 0){
      
         output_high(LED);
      
      }
      
      else{
      
         output_low(LED);
      
      }
      
   }

}
