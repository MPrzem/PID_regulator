

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "MKUART/mkuart.h"
#include "PID/PID.h"

volatile uint8_t on_off_flag=1;
//void Interrups_init(void);
// glówna funkcja programu main()
int main(void)
{

	sensors=search_sensors();
	ds18b20_set_resolution(RESOLUTION);
	LCD_Initalize();
	Pwm_init();
	OCR2=0;
	OCR1A=130;
while(1){
	ask_sensors();
	OCR2=Pid_control();
	Display();
}
}

/*
void Interrups_init(void){
	MCUCR |=(1<<ISC11)|(1<<ISC01);		 //external interrupts seted at falling edge
	GICR |=(1<<INT1)|(1<<INT0);			// external interrupts enabled
	DDRD &=~((1<<PD2)|(1<<PD3));		//PD2,PD3 as an output
	PORTD |= (1<<PD2)|(1<<PD3);			//added internal conection to VCC
	sei();//alow to interupts
}


*/
