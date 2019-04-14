

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Pwm/Pwm.h"
#include "MKUART/mkuart.h"


volatile uint8_t on_off_flag=1;
//void Interrups_init(void);
// glówna funkcja programu main()
int main(void)
{
	USART_Init( __UBRR );
	//ds18b20_set_resolution(9);
	sensors=search_sensors();
	ds18b20_set_resolution(10);
//tutaj sprawdzic zmiane rozdzielczosci!!!
	LCD_Initalize();
//	 Interrups_init();
	 Pwm_init();
		OCR2=0;
		//Pierwszy pomiar w stanie ustalonym
		_delay_ms(5000);
		ask_sensors();
	int elapsed_time_msec=0;
	int elapsed_time_sec=0;
	int elapsed_time_min=0;

	uart_putint(elapsed_time_min, 10);
	uart_puts("	");
	uart_putint(temp1, 10);
	uart_puts(".");
	uart_putint(temp1_fraction, 10);
	uart_puts("\n");

	OCR1A=80;
while(1){
	ask_sensors();
	_delay_ms(250);
	elapsed_time_msec+=(DS18B20_TCONV_12BIT/4)+252;
	elapsed_time_sec+=elapsed_time_msec/1000;
	elapsed_time_msec%=1000;
	elapsed_time_min+=elapsed_time_sec/60;
	elapsed_time_sec%=60;
	uart_putint(elapsed_time_min, 10);
	uart_puts(":");
	uart_putint(elapsed_time_sec, 10);
	uart_puts(":");
	uart_putint(elapsed_time_msec, 10);
	uart_puts("  ");
	uart_putint(temp1, 10);
	uart_puts(".");
	uart_putint(temp1_fraction, 10);
	uart_puts("\n");
	//OCR2=200;
	//OCR1A=80;
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
