#include "lib/include.h"

extern void Configura_Reg_ADC(void)
{
    
    //Pag 352 Inicializa  modulo de reloj del adc RCGCADC
    SYSCTL->RCGCADC = (1<<0)|(1<<1);  
    
    //Pag 340 los puertos (RGCGPIO) Puertos base habilitación del reloj SE habilitan los puertos correspondientes a los canales del adc pg. 801 para canales y puerto
    //                     F     E      D       C      B     A     
    SYSCTL->RCGCGPIO |= (1<<5)|(1<<4)|(1<<3)|(0<<2)|(0<<1)|(1<<0); //Port A -> UART, Port F -> leds, Port E y D para canales 
    
    //Pag 663 (GPIODIR) Habilta los pines como I/O un cero para entrada y un uno para salida. 
    GPIOE_AHB->DIR = (0<<1) | (0<<0) | (0<<5); 
    GPIOD_AHB->DIR = (0<<3) | (0<<2) | (0<<0); 
    
    //(GPIOAFSEL) pag.672 Indicar función alternativa 
    GPIOE_AHB->AFSEL = (1<<1) | (1<<0) | (1<<5); 
    GPIOD_AHB->AFSEL = (1<<3) | (1<<2) | (1<<0); 
   
    //(GPIODEN) pag.683 desabilita el modo digital de los pines 
    GPIOE_AHB->DEN = (0<<1) | (0<<0) | (0<<5); 
    GPIOD_AHB->DEN = (0<<3) | (0<<2) | (0<<0); 
    
    //Pag 688 Y pag 1351, Se indica la función alternativa de los pines
    GPIOE_AHB->PCTL = GPIOE_AHB->PCTL & (0xFF0FFF00); 
    GPIOD_AHB->PCTL = GPIOD_AHB->PCTL & (0xFFFF00F0);  
    
    //(GPIOAMSEL) pag.687 habilitar analogico los pines de los canales
    GPIOE_AHB->AMSEL = (1<<1) | (1<<0) | (1<<5); 
    GPIOD_AHB->AMSEL = (1<<3) | (1<<2) | (1<<0); 
    
    //Pag 891 El registro (ADCPC) establece la velocidad de conversión por segundo 
    ADC0->PC = (0<<3)|(1<<2)|(1<<1)|(1<<0);//Trabaja con la max. velocidad: 1 millon
    ADC1->PC = (0<<3)|(1<<2)|(1<<1)|(1<<0);//Trabaja con la max. velocidad: 1 millon
    
    //Pag 841 Este registro (ADCSSPRI) configura la prioridad de los secuenciadores prioridad 0 (mayor), 3 (menor)
    ADC0->SSPRI = 0x2103; 
    ADC1 ->SSPRI = 0x1023; 
    
    //Pag 821 (ADCACTSS) Este registro controla la activación de los secuenciadores
    ADC0->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0); 
    ADC1->ACTSS  =   (0<<3) | (0<<2) | (0<<1) | (0<<0);
    
    //Pag 834 Este registro (ADCEMUX) selecciona el evento que activa la conversión (trigger): por procesador 
    ADC0->EMUX  = (0x0000); 
    ADC1->EMUX  = (0x0000); 
    
    //Pag 867 Este registro (ADCSSMUX2) define las entradas analógicas con el canal y secuenciador seleccionado
    ADC0->SSMUX1 = 0x0357; // Los canales 3,5, 7 se definen para el mux 1 del sec. 1 en el modulo 0
    ADC1->SSMUX2 = 0x0042; // Los canales 4,2  se definen para el mux 2 del sec. 2 en el modulo 1
    ADC1->SSMUX3 = 0x8;  // El canal 8  se define para el mux 3 del sec. 3 en el modulo 1 
    
    //pag 868 Este registro (ADCSSCTL2), configura el bit de control de muestreo y la interrupción 
    ADC0->SSCTL1 = (1<<2) | (1<<1)| (1<<6) | (1<<5) | (1<<10) | (1<<9);  
    ADC1->SSCTL2 = (1<<2) | (1<<1)| (1<<6) | (1<<5);
    ADC1->SSCTL3 = (1<<2) | (1<<1);

    // Pag 825 Enable ADC Interrupt - Interrumpe la conversión del secuenciador a usar 
    ADC0->IM |= (1<<1); /* Unmask ADC0 sequence 2 interrupt*/ 
    ADC1->IM |= (1<<2) | (1<<3); 
    //NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFFFF00) | 0x00000020;
    //NVIC_EN0_R = 0x00010000;

    //Pag 821 (ADCACTSS) Este registro controla la activación de los secuenciadores utilizados 
    ADC0->ACTSS = (0<<3) | (0<<2) | (1<<1) | (0<<0); 
    ADC1->ACTSS = (1<<3) | (1<<2) | (0<<1) | (0<<0); 
    ADC0->PSSI |= (1<<1); //configura el adc en modo de procesador 
    ADC1->PSSI |= (1<<2) | (1<<3); //configura el adc en modo de procesador 

}









































































