#include <TXrs232.h>
#include <lcd_8bits.c>

// Vari�veis
int1 fim_tempo1, fim_tempo2;
int8 contador1 = 250, contador2 = 4;
int16 temperatura, potenciometro1, potenciometro2, rotacao;
float relacao_pot = 800 / 1023.0, relacao_helices = 60 / 7;

// Constantes
// Interrup��o por TIMER0
#int_TIMER0

void  TIMER0_isr(void){
   set_timer0(get_timer0() + 6);
   contador1--;
   
   if( ! contador1){
      
      contador1 = 250;
      fim_tempo1 = 1;
      contador2--;
      if( ! contador2){
         
         contador2 = 4;
         fim_tempo2 = 1;
      }
   }
}

void main(){
   setup_adc_ports(AN0_AN1_AN2_AN3_AN4);
   setup_adc(ADC_CLOCK_INTERNAL);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_4|RTCC_8_BIT); //1, 0 ms overflow
   setup_timer_1(T1_EXTERNAL|T1_DIV_BY_1); //65, 5 ms overflow
   setup_timer_2(T2_DIV_BY_1, 199, 1); //200 us overflow, 200 us interrupt
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);
   set_pwm1_duty((int16)0);
   set_pwm2_duty((int16)0);
   enable_interrupts(int_TIMER0);
   enable_interrupts(GLOBAL);
   
   lcd_init();
   while(TRUE){
      if(fim_tempo1){
      
         fim_tempo1 = 0;
         
         set_adc_channel(0);
         delay_us(40);
         temperatura = read_adc();
         
         set_adc_channel(1);
         delay_us(40);
         potenciometro1 = read_adc() * relacao_pot; //(pot1 / 1023) * 800
         
         set_adc_channel(2);
         delay_us(40);
         potenciometro2 = read_adc() * relacao_pot;
         
         lcd_gotoxy(1, 1);
         printf(lcd_write_dat, "%04Lu", temperatura);
         printf("Temp: %04Lu\n", temperatura);
         
         lcd_gotoxy(7, 1);
         printf(lcd_write_dat, "%04Lu", potenciometro1);
         
         lcd_gotoxy(13, 1);
         printf(lcd_write_dat, "%04Lu", potenciometro2);
         
         set_pwm1_duty(potenciometro1);
         set_pwm2_duty(potenciometro2);
      }

   
      if(fim_tempo2){
         fim_tempo2 = 0;
         
         rotacao = get_timer1() * relacao_helices; //(Valor das rota��es / 7 helices) * 60 - > valor rotacao * (60 / 7)
         
         set_timer1(0);
         
         lcd_gotoxy(1, 2);
         printf(lcd_write_dat, "%05Lu", rotacao);
        
      }
   }
}

