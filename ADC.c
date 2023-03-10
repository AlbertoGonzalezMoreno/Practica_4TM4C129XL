/*
 * ADC.c
 *
 *  Created on: 04/11/2019
 *      Author: ravenelco
 */
#include "lib/include.h"

/* Se configurarán los siguientes módulos:
ADC módulo 0: secuenciador 3: canal 10
ADC módulo 1: secuenciador 1: canal 1 2 6 7
Se omitirá la lectura del canal 4 ya que entre el secuenciador 1 y 3 
solamente se pueden leer 5 canales como máximo 
*/
extern void Configurar_ADC(void)
{
     //Pag 396 para inicializar el modulo de reloj del adc RCGCADC
    SYSCTL->RCGCADC |= (1<<0) | (1<<1);  // Se activan los canales 1 y 0
    //Pag 382 (RGCGPIO) Puertos base habilitación del reloj
    /* Los canales respectivamente pertenecen a: 
    1 : PE2
    2 : PE1
    6 : PD5
    7 : PD4
    10 :PB4
    */
    //                     B     D      E   
    SYSCTL->RCGCGPIO |= (1<<1)|(1<<3)|(1<<4)|(1<<2);
    //Pag 760 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida
            // Para el puerto E
            GPIOE_AHB->DIR = (0<<1) | (0<<2); //PE1 y PE2
            // Para el puerto D
            GPIOD_AHB->DIR = (0<<4) | (0<<5); //PD4 y PD5
            // Para el puerto B
            GPIOB_AHB->DIR = (0<<4);          //PB4
    //(GPIOAFSEL) pag.770 Enable alternate función para que el modulo analógico tenga control de esos pines
            // Para el puerto E
            GPIOE_AHB->AFSEL =  (1<<1) | (1<<2); //PE1 y PE2
            // Para el puerto D
            GPIOD_AHB->AFSEL =  (1<<4) | (1<<5); //PD4 y PD5
            // Para el puerto B
            GPIOB_AHB->AFSEL =  (1<<4);          //PB4
    //(GPIODEN) pag.781 desabilita el modo digital
            // Para el puerto E
            GPIOE_AHB->DEN=  (0<<1) | (0<<2); //PE1 y PE2
            // Para el puerto D
            GPIOD_AHB->DEN =  (0<<4) | (0<<5); //PD4 y PD5
            // Para el puerto B
            GPIOB_AHB->DEN =  (0<<4);          //PB4
    //Pag 787 GPIOPCTL registro combinado con el GPIOAFSEL y la tabla pag 1808
            // Para el puerto E
            GPIOE_AHB->PCTL = GPIOE_AHB->PCTL & (0xFFFFF00F); //PE1 y PE2
            // Para el puerto D
            GPIOD_AHB->PCTL = GPIOD_AHB->PCTL & (0xFF00FFFF); //PD4 y PD5
            // Para el puerto B
            GPIOB_AHB->PCTL = GPIOB_AHB->PCTL & (0xFFF0FFFF); //PB4
    //(GPIOAMSEL) pag.786 habilitar analogico
            // Para el puerto E
            GPIOE_AHB->AMSEL =  (1<<1) | (1<<2); //PE1 y PE2
            // Para el puerto D
            GPIOD_AHB->AMSEL =  (1<<4) | (1<<5); //PD4 y PD5
            // Para el puerto B
            GPIOB_AHB->AMSEL =  (1<<4);          //PB4
    //Pag 1159 El registro (ADCPC) establece la velocidad de conversión por segundo
            // Para el módulo 0
            ADC0->PC = ((1<<2)|(0<<1)|(1<<0)); //1 Msps
            // Para el módulo 1
            ADC1->PC = ((1<<2)|(0<<1)|(1<<0)); //1 Msps
    //Pag 1099 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores
            // Para el módulo 0 
            ADC0->SSPRI = 0x0132;          // Se le da mayor prioridad al sec 3 (0 alta - 3 baja)
            // Para el módulo 1
            ADC1->SSPRI = 0x3102;          // Se le da mayot prioridad al sec 1 (0 alta - 3 baja)
    //Pag 1077 (ADCACTSS) Este registro controla la desactivación de los secuenciadores
            // Para el módulo 0
            ADC0->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0); 
            // Para el módulo 1
            ADC1->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0);
    //Pag 1091 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger)
            // Para el módulo 0 
            ADC0->EMUX  = 0x0; //(0x4<<12);
            // Para el módulo 1 
            ADC1->EMUX  = 0x0;// (0x4<<4);
    //Pag 1129 Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado
            // Para el módulo 0
            ADC0->SSMUX3 = (1<<3) | (0<<2) | (1<<1) | (0<<0); // Lectura 1 Canal 10 
            // Para el módulo 1
            ADC1->SSMUX1 = 0x7621;                            // Lectura 4 Canal 7  Lectura 3 Canal 6  Lectura 2 Canal 1 Lectura 1 Canal 2 
    //pag 868 Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción
            // Para el módulo 0
            ADC0->SSCTL3 = (1<<2) | (1<<1);  // La primera muestra es la última
            // Para el módulo 1
            ADC1->SSCTL1 = (1<<14) | (1<<13); // La cuarta muestra es la última
    /* Enable ADC Interrupt */
            // Para el módulo 0
            ADC0->IM |= (1<<3); /* Unmask ADC0 sequence 3 interrupt pag 1082*/
            // Para el módulo 1
            ADC1->IM |= (1<<1); /* Unmask ADC1 sequence 1 interrupt pag 1082*/
    //Pag 1077 (ADCACTSS) Este registro controla la activación de los secuenciadores
            // Para el módulo 0
            ADC0->ACTSS = (1<<3) | (0<<2) | (0<<1) | (0<<0); // Activa sec 3 
            ADC0->PSSI |= (1<<3);                            //
            // Para el módulo 11
            ADC1->ACTSS = (0<<3) | (0<<2) | (1<<1) | (0<<0); // Activa sec 1 
            ADC1->PSSI |= (1<<1);                            //
}

extern void Lectura_ADC(uint16_t *Result){

    //ADC Processor Sample Sequence Initiate (ADCPSSI)
    //Para el módulo 0 
        ADC0->PSSI = 0x00000008;             // Activa sec 3 
        while((ADC0->RIS&0x08)==0){};        // Espera al convertidor
        Result[0] = ADC0->SSFIFO3&0xFFF;     // Leer  el resultado del canal 10
        ADC0->ISC = 0x0008;                  // Conversion finalizada
    //Para el módulo 1
        ADC1->PSSI = 0x00000002;             // Activa sec 1
        while((ADC1->RIS&0x02)==0){};        // espera al convertidor
        Result[1] = ADC1->SSFIFO1&0xFFF;     // Leer el resultado del canal 7
        Result[2] = ADC1->SSFIFO1&0xFFF;     // Leer el resultado del canal 6
        Result[3] = ADC1->SSFIFO1&0xFFF;     // Leer el resultado del canal 2
        Result[4] = ADC1->SSFIFO1&0xFFF;     // Leer el resultado del canal 1
        ADC1->ISC = 0x0002;                  //Conversion finalizada
}