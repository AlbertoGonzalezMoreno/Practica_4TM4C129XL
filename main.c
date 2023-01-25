#include "lib/include.h"
/* Para la configuración del ADC solamente se leyeron 5 canales ya que con el secuenciador 1 y 3
este es el máximo de lecturas que se pueden realizar*/
int main(void)
{
    uint16_t terminator = 0;
    uint16_t Result[5];
    float valor;
    float valor1;
    float valor2;
    float valor3;
    float valor4;
    int precision = 3;
    char c ;
    Configurar_PLL();      //Confiuracion de velocidad de reloj a 30 MHz
    SysTick_Init();        // Inicialización del SysTick para delays
    Configurar_GPIO();
    Configurar_ADC();
    Configurar_UART0();
    Configurar_GPIO();
    Result[0] = 0;
    Result[1] = 0;
    Result[2] = 0;
    Result[3] = 0;
    Result[4] = 0;
    Result[5] = 0;
    while(1)
    {
        c = readChar();
        if(c == '5' || c == 0)
        {
        valor=(float)(((Result[0]))*3.3)/4096;
        valor1=(float)(((Result[1]))*3.3)/4096;
        valor2=(float)(((Result[2]))*3.3)/4096;
        valor3=(float)(((Result[3]))*3.3)/4096;
        valor4=(float)(((Result[4]))*3.3)/4096;
        //Lectura_ADC(Result); //Llamada a la conversion por procesador
            //Para el módulo 0 
        ADC0->PSSI = 0x00000008;             // Activa sec 3 
        while((ADC0->RIS&0x08)==0){
        printChar('A');
        float2str(valor, precision);
        printChar('B');
        float2str(valor1, precision);
        printChar('C');
        float2str(valor2, precision);
        printChar('D');
        float2str(valor3, precision);
        printChar('E');
        float2str(valor4, precision);
        printChar((char)terminator);
        };        // Espera al convertidor
        Result[0] = ADC0->SSFIFO3&0xFFF;     // Leer  el resultado del canal 10
        ADC0->ISC = 0x0008;                  // Conversion finalizada
    //Para el módulo 1
        ADC1->PSSI = 0x00000002;             // Activa sec 1
        while((ADC1->RIS&0x02)==0){
        printChar('A');
        float2str(valor, precision);
        printChar('B');
        float2str(valor1, precision);
        printChar('C');
        float2str(valor2, precision);
        printChar('D');
        float2str(valor3, precision);
        printChar('E');
        float2str(valor4, precision);
        printChar((char)terminator);
        };        // espera al convertidor
        Result[1] = ADC1->SSFIFO1&0xFFF;     // Leer el resultado del canal 7
        Result[2] = ADC1->SSFIFO1&0xFFF;     // Leer el resultado del canal 6
        Result[3] = ADC1->SSFIFO1&0xFFF;     // Leer el resultado del canal 2
        Result[4] = ADC1->SSFIFO1&0xFFF;     // Leer el resultado del canal 1
        ADC1->ISC = 0x0002;                  //Conversion finalizada
        }
    }
}