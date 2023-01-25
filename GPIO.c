#include "lib/include.h"
extern void Configurar_GPIO(void)
{
    SYSCTL->RCGCGPIO |=(1<<3); 
    SYSCTL->PRGPIO |=(1<<3); 
    GPIOD_AHB->ADCCTL = (1<<6);
    GPIOD_AHB->AMSEL = 0x00;        
    GPIOD_AHB->PCTL = 0x00000000;   
    GPIOD_AHB->DIR = (0<<6);        
    GPIOD_AHB->AFSEL = 0x00;       
    GPIOD_AHB->PUR = (1<<6);          
    GPIOD_AHB->DEN = (1<<6);          

    NVIC->IP[0] = (NVIC->IP[0]&0x00FFFFFF) | 0x80000000;;
    NVIC->ISER[0] = (1<<3);

    
    GPIOD_AHB->IM |= (0<<6); 
    GPIOD_AHB->IS |= (0<<6);
    GPIOD_AHB->IBE |= (0<<6);
    GPIOD_AHB->IEV |= (1<<6);
    GPIOD_AHB->RIS |= (0<<6);
    GPIOD_AHB->IM |= (1<<6);
}