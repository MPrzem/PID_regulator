

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Pwm/Pwm.h"



volatile uint8_t on_off_flag=1;
//void Interrups_init(void);
// glówna funkcja programu main()
int main(void)
{

	sensors=search_sensors();
//tutaj sprawdzic zmiane rozdzielczosci!!!
	LCD_Initalize();
//	 Interrups_init();
	 Pwm_init();
		OCR1A=255;
while(1){
	ask_sensors();
	OCR2=200;
	OCR1A=80;
	//fan_control();
	Display();
	//	while(!on_off_flag){};
	//_delay_ms(1000);
}
}
/*

ISR(INT0_vect)
{
	on_off_flag=0;
    OCR2=0;
    _delay_ms(50);
}
ISR(INT1_vect)
{
	on_off_flag=1;
    _delay_ms(50);
}
void Interrups_init(void){
	MCUCR |=(1<<ISC11)|(1<<ISC01);		 //external interrupts seted at falling edge
	GICR |=(1<<INT1)|(1<<INT0);			// external interrupts enabled
	DDRD &=~((1<<PD2)|(1<<PD3));		//PD2,PD3 as an output
	PORTD |= (1<<PD2)|(1<<PD3);			//added internal conection to VCC
	sei();//alow to interupts
}

*/
