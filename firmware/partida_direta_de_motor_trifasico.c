/****************************************************
        Produzido por Mauricio Baron
        data 21/05/21
        Fiemware produzido com intuito de acionar um motor trifasico 
        via bluetooth com partida e parada       
*/
#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(crystal=4MHz)
#use FIXED_IO( A_outputs=PIN_A2,PIN_A1,PIN_A0 )
#use rs232(baud=9600,parity=N,xmit=PIN_B2,rcv=PIN_B1,bits=8,stream=PORT1)

//definicoes portas
#define RELE_NA PIN_A0
#define RELE_NF PIN_A1
#define RELE_SINAL PIN_A2

//prototipos de função
void Partida();   //inicia a rotação do motor
void Parada();    //inicia a parada do motor
void Zera_Rele(); //volta a o estado inicial

char dado;


void main()
{

   while(TRUE)
   {
   
   if(kbhit())
   {
   dado = getc();
   if(dado == 'p')
   {
     Partida();
     delay_ms(10);
   }
   if(dado == 'i')
   {
     Parada();
     delay_ms(10);
   }
   if(dado == 'z')
   {
     Zera_Rele();
     delay_ms(10);
   }
   } 
     delay_ms(10);
   }

}
void Partida()
{
   printf("%d",'0');              //envia dados para o rs232
   output_bit(RELE_NA,1);
   delay_ms(100);
   output_bit(RELE_NA,0);
   output_bit(RELE_NF,0);
   output_bit(RELE_SINAL,1);
   delay_ms(10);
}
void Parada()
{
   printf("%d",'1');              //envia dados para o rs232
   output_bit(RELE_NA,0);
   output_bit(RELE_NF,1);
   delay_ms(100);
    output_bit(RELE_NF,0);
   output_bit(RELE_SINAL,0);
   delay_ms(10);
}
void Zera_Rele()
{
   printf("%d",'2');              //envia dados para o rs232
   output_bit(RELE_NA,0);
   output_bit(RELE_NF,0);
   output_bit(RELE_SINAL,0);
   delay_ms(10);
}
