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
    Configurar_ADC();
    Configurar_UART0();
    Configurar_GPIO();
    while(1)
    {
        c = readChar();
        if(c == '5' || c == 0)
        {
        Lectura_ADC(Result); //Llamada a la conversion por procesador
        valor=(float)(((Result[0]))*3.3)/4096;
        valor1=(float)(((Result[1]))*3.3)/4096;
        valor2=(float)(((Result[2]))*3.3)/4096;
        valor3=(float)(((Result[3]))*3.3)/4096;
        valor4=(float)(((Result[4]))*3.3)/4096;
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
        }
    }
}