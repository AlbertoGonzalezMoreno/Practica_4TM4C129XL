#include "lib/include.h"
extern void Configurar_GPIO(void)
{
    SYSCTL->RCGCGPIO |=(1<<7); 
    SYSCTL->PRGPIO |=(1<<7); 
    GPIOH_AHB->ADCCTL = (1<<2);
    GPIOH_AHB->AMSEL = 0x00;        
    GPIOH_AHB->PCTL = 0x00000000;   
    GPIOH_AHB->DIR = (0<<2);        
    GPIOH_AHB->AFSEL = 0x00;       
    GPIOH_AHB->PUR = (1<<2);          
    GPIOH_AHB->DEN = (1<<2);          

    NVIC->IP[0] = (NVIC->IP[0]&0xFFFFFF00) | 0x00000080;
    NVIC->ISER[1] = (1<<0);

    
    GPIOH_AHB->IM |= (0<<2); 
    GPIOH_AHB->IS |= (0<<2);
    GPIOH_AHB->IBE |= (0<<2);
    GPIOH_AHB->IEV |= (1<<2);
    GPIOH_AHB->RIS |= (0<<2);
    GPIOH_AHB->IM |= (1<<2);
}