#include <avr/io.h>
#include <avr/interrupt.h>

/*
	Tbum = 1s
    prescale = 1024
    t_osc = 1/f_osc
    f_osc = 8 MHz
    
    Como:
    Tbum = (TOP + 1)(prescale)(t_osc)
    
    então:
    
    TOP + 1 = (Tbum * f_osc)/prescale
    
    logo:
    
    TOP + 1 = (1 * (8*10^6))/256
    TOP + 1 = 31256
    
    Sendo assim, precisamos de um registrador que conte até 31256.
    
    Isso não é possível com um de 8 bits. Logo, precisaremos
    de um de 16 bits que conta até 65535 que é maior que o número
    que buscamos de 31256.
    
    Dessa forma, podemos usar o Timer/Counter 1 que atingirá nossas expectativas e
    contará até 31256 em 1s que é o tempo de estouro desejado.
*/

// Código utilizando interrupção
int main(void){
  sei();

  DDRD |= (1 << PD4);

  OCR1A = 0x7A18; // Timer/Counter1 contará até 31256 em 1s
  TCCR1B |= (1 << WGM12) | (1 << CS12); // Modo CTC e clk(I/O)/256 (from prescaler)
  TIMSK1 |= (1 << OCIE1A); // Timer/Counter1 comparação de saída A

  while(1);
  
  return 0;
}

ISR(TIMER1_COMPA_vect) {
  PORTD ^= (1 << PD4); // inverte o estado do led
}

