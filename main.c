#include "lib/include.h"

int main(void)
{

    Configurar_PLL(_20MHZ);  //Confiuracion de velocidad de reloj
    Configura_Reg_ADC();
    Configurar_UART0();
    Configurar_GPIO();

    while(1)
    {   
       

    }
}


