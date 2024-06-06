#include <controle_temperatura.h>
#include <lcd_8bits.c>

int1 sistema = 0, fim_250ms = 0;
int8 tempo_250ms = 0;
int16 temperatura_desejada = 450, temperatura_atual = 0, histerese = 10;

#int_TIMER0
void  TIMER0_isr(void){

   tempo_250ms++;
   
   if(tempo_250ms == 250){
   
      tempo_250ms = 0;
      
      fim_250ms = 1;
   
   }

}

void main(){

   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_BIT); //1, 0 ms overflow
   enable_interrupts(int_TIMER0);
   enable_interrupts(GLOBAL);
   
   lcd_init();
   lcd_gotoxy(1,1);
   printf(lcd_write_dat, "Td %04Lu", temperatura_desejada);
   
   set_adc_channel(0);
   delay_us(40);
   
   lcd_gotoxy(1,2);
   printf(lcd_write_dat, "SIOF");
   
   lcd_gotoxy(7,2);
   printf(lcd_write_dat, "HTOF");
   
   lcd_gotoxy(13,2);
   printf(lcd_write_dat, "CLOF");
   
   while(TRUE){
   
      if(fim_250ms){
   
         temperatura_atual = read_adc();
         lcd_gotoxy(10,1);
         printf(lcd_write_dat, "Ta %04Lu", temperatura_atual);
      }
   
      if(!input(S1)){
      
         sistema = 1;
         
         lcd_gotoxy(1,2);
         printf(lcd_write_dat, "SION");
      
      }
      
      if(sistema){
      
         if(temperatura_atual < (temperatura_desejada - histerese)){
         
            output_high(HEATER);
            output_low(COOLER);
            
            lcd_gotoxy(7,2);
            printf(lcd_write_dat, "HTON");
            
            lcd_gotoxy(13,2);
            printf(lcd_write_dat, "CLOF");
         
         }
         
         else if(temperatura_atual > (temperatura_desejada + histerese)){
         
            output_low(HEATER);
            output_high(COOLER);
            
            lcd_gotoxy(7,2);
            printf(lcd_write_dat, "HTOF");
            
            lcd_gotoxy(13,2);
            printf(lcd_write_dat, "CLON");
         
         }
         
         if(!input(S2)){
      
            sistema = 0;
            
            output_low(HEATER);
            output_low(COOLER);
            
            lcd_gotoxy(1,2);
            printf(lcd_write_dat, "SIOF");
            
            lcd_gotoxy(7,2);
            printf(lcd_write_dat, "HTOF");
            
            lcd_gotoxy(13,2);
            printf(lcd_write_dat, "CLOF");
         
         }
      
      }
      
   }
   
}

