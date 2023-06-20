#define F_CPU 8000000L
#include <avr/io.h>

#define RELAY_PIN PB0

void relayOn() {
	PORTB |= (1 << RELAY_PIN);
}

void relayOff() {
	PORTB &= ~(1 << RELAY_PIN);
}

int main(void) {
	DDRB |= (1 << RELAY_PIN);
	DDRB |= (1 << 3);
	ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS2);
	ADMUX |= (1<<REFS0);
	TCCR0 |= 0b00011101;
	TIMSK|= (1<<OCIE0);
	
	
	while (1) {
		ADCSRA |= (1 << ADSC);
		if(ADC > 400){
			relayOff();
			DDRB |= (1 << 3);
			OCR0 = 141;
		} else {
			relayOn();
			DDRB &= ~(1 << 3);
	
		}
	}

}

