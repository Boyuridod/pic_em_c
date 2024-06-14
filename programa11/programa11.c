#include <programa11.h>
#include <lcd_8bits.c>

int1 isLigado = 0, fim500ms = 0, vizualisacao = 0;
int8 i = 0;
int16 cont500ms = 0, valor_temp = 0, valor_potenciometro = 0;
float histerese = 0.1, temperatura = 0, temperatura_desejada = 0, conversao = 1.0/1022.0;

#INT_TIMER0
void  TIMER0_isr(void) {

   cont500ms++;
   
   if(cont500ms == 500){
      
      cont500ms = 0;
      fim500ms = 1;
   
   }

}

void main(){
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_BIT);      //1,0 ms overflow
   setup_timer_2(T2_DIV_BY_4,99,1);      //200 us overflow, 200 us interrupt

//!   setup_ccp1(CCP_PWM);
//!   set_pwm1_duty((int16)0);

   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
   
   lcd_init();
   
   lcd_gotoxy(1,2);
   printf(lcd_write_dat, "S:OF");
   
   lcd_gotoxy(6,2);
   printf(lcd_write_dat, "R:OF");
   
   lcd_gotoxy(12,2);
   printf(lcd_write_dat, "H:%.1f",histerese);
   
   while(TRUE){

      if(!input(S1)){
      
         for(i = 0; i <= 100; i++){
         
            if(!input(S1))
               i = 0;
         
         }
      
         if(isLigado == 1){
         
            output_low(HEATER);
         
            lcd_gotoxy(1,2);
            printf(lcd_write_dat, "S:OF");
            
            lcd_gotoxy(6,2);
            printf(lcd_write_dat, "R:OF");
            
            isLigado = 0;
         
         }
         
         else{
         
            output_high(HEATER);
            
            lcd_gotoxy(1,2);
            printf(lcd_write_dat, "S:ON");
            
            isLigado = 1;
         
         }
      
      }
      
      if(!input(S2)){
      
         for(i = 0; i <= 100; i++){
         
            if(!input(S2))
               i = 0;
         
         }
         
         if(histerese < 9.9)
            histerese += 0.1;
            
         lcd_gotoxy(12,2);
         printf(lcd_write_dat, "H:%.1f",histerese);
      
      }
      
      if(!input(S3)){
      
         for(i = 0; i <= 100; i++){
         
            if(!input(S3))
               i = 0;
         
         }
      
         if(histerese > 0.1)
            histerese -= 0.1;
            
         lcd_gotoxy(12,2);
         printf(lcd_write_dat, "H:%.1f",histerese);
      
      }
      
      if(!input(S4)){
      
         for(i = 0; i <= 100; i++){
         
            if(!input(S4))
               i = 0;
         
         }
      
         vizualisacao = !vizualisacao;
      
      }
      
      if(isLigado){
      
         if(temperatura > (temperatura_desejada + histerese)){
         
            output_low(HEATER);
         
            lcd_gotoxy(6,2);
            printf(lcd_write_dat, "R:OF");
         
         }
         
         else if(temperatura < (temperatura_desejada - histerese)){
         
            output_high(HEATER);
            
            lcd_gotoxy(6,2);
            printf(lcd_write_dat, "R:ON");
         
         }
      
      }
      
      if(fim500ms){
      
         set_adc_channel(1);
         delay_us(40);
         valor_potenciometro = read_adc();
         
         temperatura_desejada = (valor_potenciometro * conversao * 49.98) + 27.50;
         
         set_adc_channel(0);
         delay_us(40);
         valor_temp = read_adc();
         
         temperatura = ((0.126 * valor_temp) - 15.40);
         
         if(vizualisacao){
         
            lcd_gotoxy(1,1);
            printf(lcd_write_dat, "%f*C  ", temperatura);
            
            lcd_gotoxy(9,1);
            printf(lcd_write_dat, "D%f*C", temperatura_desejada);
         
         }
         
         else{
         
            lcd_gotoxy(1,1);
            printf(lcd_write_dat, "St:%04Lu", valor_temp);
         
            lcd_gotoxy(9,1);
            printf(lcd_write_dat, "Pot:%04Lu", valor_potenciometro);
         
         }
         
         fim500ms = 0;
      
      }
      
   }

}
