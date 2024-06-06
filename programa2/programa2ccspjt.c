#include <programa2ccspjt.h>

int1 qual_ler = 1, fim_5s = 0, fim_500ms = 0;
int8 qual_display = 0;
int8 unidade = 0, dezena = 0, centena = 0, milhar = 0;
int8 conversao[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
int16 valor = 0, tempo_5s = 0, tempo_500ms = 0;

#int_TIMER0
void  TIMER0_isr(void) {

   tempo_5s++;
   
   if(tempo_5s == 5000){
   
      fim_5s = 1;
      tempo_5s = 0;
   
   }
   
   tempo_500ms++;
   
   if(tempo_500ms == 500){
   
      fim_500ms = 1;
      tempo_500ms = 0;
   
   }
   
   qual_display++;
   
}

void converte_valor(int16 num){

   milhar = centena = dezena = unidade = 0;

   while(num >= 1000){
      
      num -= 1000;
      milhar++;
      
   }
   
   while(num >= 100){
      
      num -= 100;
      centena++;
      
   }
   
   while(num >= 10){
      
      num -= 10;
      dezena++;
      
   }
   
   unidade = num;

}

void acende_display(){

   if(qual_display == 0){

      output_low(DISPLAY4);
      output_high(DISPLAY1);
      output_d(conversao[unidade]);
   
   }
   
   else if(qual_display == 2){
   
      output_low(DISPLAY1);
      output_high(DISPLAY2);
      output_d(conversao[dezena]);
   
   }
   
   else if(qual_display == 4){
   
      output_low(DISPLAY2);
      output_high(DISPLAY3);
      output_d(conversao[centena]);
   
   }
   
   else if(qual_display == 6){
   
      output_low(DISPLAY3);
      output_high(DISPLAY4);
      output_d(conversao[milhar]);
      
      qual_display = -1;
   
   }

}

void main(){
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_4|RTCC_8_BIT);//1, 0 ms overflow
   enable_interrupts(int_TIMER0);
   enable_interrupts(GLOBAL);
   
   set_adc_channel(1);
   delay_us(40);
   valor = read_adc();
   converte_valor(valor);
   
   while(TRUE){
   
   acende_display();
      
      if(fim_5s) {
         
         qual_ler = !qual_ler;
         
         set_adc_channel(qual_ler);
         delay_us(40);
         valor = read_adc();
         
         converte_valor(valor);
         
         fim_5s = 0;
         
      }

      if(fim_500ms) {
         
         if(qual_ler == 0) {
            
            valor = read_adc();
            
         }

         
         else{
            
            valor = read_adc();
            
         }
         
         converte_valor(valor);
         
         fim_500ms = 0;
         
      }
   }
}

//TODO Tirar tudo q for poss�vel da interrup��o | Se n funcionar usa PWM
