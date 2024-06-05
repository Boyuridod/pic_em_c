#include <rx232_lcd.h>
#include <lcd_8bits.c>

int1 fim_rx = 0;
int8 x = 0, y = 0;
char rx_aux;
char rx_pacote[2][5];

#int_RDA

void  RDA_isr(void) {

   rx_aux = getc();
   
   if(rx_aux == 'I'){
   
      x = y = 0;
   
   }
   
   else if(rx_aux == 'F'){
   
      fim_rx = 1;
   
   }
   
   else if(rx_aux == ';'){
   
      x++;
      y = 0;
   
   }
   
   else{
   
      rx_pacote[x][y] = rx_aux;
      y++;
   
   }

}

#int_TIMER0

void  TIMER0_isr(void) {
}

void main(){
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_16|RTCC_8_BIT);//4, 0 ms overflow
   setup_timer_2(T2_DIV_BY_1, 199, 1);//200 us overflow, 200 us interrupt
   setup_ccp1(CCP_PWM);
   set_pwm1_duty((int16)0);
   enable_interrupts(int_RDA);
   enable_interrupts(int_TIMER0);
   enable_interrupts(GLOBAL);
   
   rx_pacote[0][4] = rx_pacote[1][4] = 0;
   lcd_init();

   while(TRUE){
      if(fim_rx){
      
         fim_rx = 0;
         lcd_gotoxy(1,1);
         printf(lcd_write_dat, "%s", rx_pacote[0]);
         lcd_gotoxy(8,1);
         printf(lcd_write_dat, "%s", rx_pacote[1]);
         
      
      }
   }
}

