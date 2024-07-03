#include <serialtank.h>

//! Declara��o de vari�veis

int1 teste = 0;
int16 leitura = 0, setpoint = 25, histerese = 5;
void setValvula(int8 acao);
void setHeater(int8 acao);
int1 isCheio();
int16 getTemperatura();
void setDespeja(int8 acao);
int1 isVazio();

void main()
{
//!   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_8|RTCC_8_BIT);      //1,0 ms overflow

//!   enable_interrupts(INT_TIMER0);
//!   enable_interrupts(GLOBAL);

   while(TRUE)
   {
//!      if(!isCheio() e isVazio()){
//!         
//!      }

      leitura = 0;
      teste = 0;

      setValvula(1);
      
      do{
      
         teste = isCheio();
      
      } while(teste == 0);
      
      setValvula(0);
      
      setHeater(1);
      
      do{
      
         leitura = getTemperatura();
      
      } while(leitura < setpoint);
      
      setHeater(0);
      
      setDespeja(1);
      
      do{
      
         teste = isVazio();
         
      } while(teste == 1);
      
      setDespeja(0);

   }

}

//! Fun��es

void setValvula(int8 acao){

   putc(0x00);
   putc(acao);

}

void setHeater(int8 acao){

   putc(0x02);
   putc(acao);

}

int1 isCheio(){

   putc(0x10);
   return getc();

}

int16 getTemperatura(){

   putc(0x31);
   return getc();

}

void setDespeja(int8 acao){

   putc(0x01);
   putc(acao);

}

int1 isVazio(){

   putc(0x11);
   if(getc() == 1)
      return 0;
   else
      return 1;

}
