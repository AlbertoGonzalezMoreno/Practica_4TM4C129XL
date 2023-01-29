#include "lib/include.h"
/* Para la configuración del ADC solamente se leyeron 5 canales ya que con el secuenciador 1 y 3
este es el máximo de lecturas que se pueden realizar*/
    int flag = 0;
extern void IntGPIOH(void){
flag = 1;
 GPIOH_AHB ->ICR |= (1<<2);
}
int main(void)
{
    uint16_t terminator = 0;
    float valor;
    float valor1;
    float valor2;
    float valor3;
    float valor4;
    int precision = 3;
    uint16_t Result[5];
    char c ;
    Configurar_PLL();      //Confiuracion de velocidad de reloj a 30 MHz
    Configurar_ADC();
    Configurar_UART0();
    Result[0] = 500;
    Result[1] = 0;
    Result[2] = 1056;
    Result[3] = 0;
    Result[4] = 899;
    Configurar_GPIO();
    while(1)
    {
      c = readChar();//c = '5';// c = readChar();
        if(c == '5' || c == 0)
        {
            if(flag == 1)
            {
                 Lectura_ADC(Result);
                flag = 0;
            }
        valor=(float)(((Result[0]))*3.3)/4096;
        valor1=(float)(((Result[1]))*3.3)/4096;
        valor2=(float)(((Result[2]))*3.3)/4096;
        valor3=(float)(((Result[3]))*3.3)/4096;
        valor4=(float)(((Result[4]))*3.3)/4096;
        //Lectura_ADC(Result); //Llamada a la conversion por procesador
            //Para el módulo 0 
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