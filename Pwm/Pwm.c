/*
 * Pwm.c
 *
 *  Created on: 8 mar 2019
 *      Author: Student241580
 */

#include"Pwm.h"
const char temp_text [] PROGMEM = "Temp : ";
const char temp_zad_text [] PROGMEM = "Temp zadan. :";

const char error[] PROGMEM="Awaria czujnika";
const char fanpowertext [] PROGMEM ="Moc wiatraka: " ;

/// ow-BYTE-WR = OW-WRITE

void Pwm_init(void){
	/*Init of fan pwm*/
	DDRB |= (1<<PWM_F);					//Seting OC2 as an output
	TCCR2 |= (1<<WGM21)|(1<<WGM20);		// FastPwm selected
	TCCR2 |= (1<<COM21)|(1<<COM20);				// Setting OC2 after overflow of TCNT2
	TCCR2 |= (1<<CS22);					// prescaler = 64
	OCR2=0;							// conts 0 as defalute value at output
	/*Init of heater pwm*/
	DDRB |= (1<<PWM_H);
	TCCR1A |= (1<<WGM10);// FastPwm selected 8 bit
	TCCR1B |= (1<<WGM12);
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0);//jednak invert Clear OCR1A on Compare Match, set OC1A/OC1B at BOTTOM
	TCCR1B |= (1<<CS10)|(1<<CS11);//Preksaler = 64 ~1kHz
	OCR1A=0;
}
void Display(){
	int power;
	char buf[10];
	LCD_Clear();
	LCD_WriteText_P(temp_text);
	LCD_WriteText(itoa(temp1,buf,10));
	LCD_GoTo(0,1);
	LCD_WriteText_P(fanpowertext);
	power=OCR2;
	power *=100;
	power =power/255;
	LCD_WriteText(itoa(power,buf,10));
	LCD_WriteText("%");


}
void ask_sensors(void){
	DS18X20_start_meas(DS18X20_POWER_PARASITE,NULL);
_delay_ms(DS18B20_TCONV_10BIT);
if(!(DS18X20_OK==DS18X20_read_meas(gSensorIDs[0],&sign,&temp1,&temp1_fraction)))
	LCD_WriteText_P(error);
}
//calka jedenej chwili czasowej. Podajemy wartosc poczatkowa i koncowa chwili
//Ponizsze funkcje nie zmieniaja uchybu obecnego na poprzedni, ja bym tutaj uzyl static
int integral(){
	 Pid.integral_memory+=(Pid.deviation + Pid.deviation_prev)/2*Pid.dt;
	 return Pid.integral_memory;
}

int deriverate(){
	 return  ((Pid.deviation - Pid.deviation_prev)/Pid.dt);
}

int Pid_control(uint8_t current_temp){
	 Pid.out = Pid.Kp*(Pid.deviation + (1/Pid.Ti)*integral() + Pid.Td*deriverate());
	return Pid.out;

}


/*
void fan_control(void){
//********************************************************
	//factorization to format (XX,X)*10
	int diff=temp1-temp2;
	int diff_fraction=temp1_fraction-temp2_fraction;

	diff_fraction &=(1<<0);
	diff *=10;
	diff +=diff_fraction;
//********************************************************
	//low-pass filter
	static int diffsr;
diffsr=(5*diffsr+diff)/6;
//********************************************************
	if(diffsr>50)
		OCR2=255;
	else if(diffsr>45)
			OCR2=220;
	else if(diffsr>40)
			OCR2=200;
	else if(diffsr>35)
			OCR2=170;
	else if(diffsr>30)
			OCR2=150;
	else if(diffsr>25)
			OCR2=130;
	else if(diffsr>20)
			OCR2=100;
	else if(diffsr>15)
			OCR2=100;
	else if(diffsr>10)
			OCR2=0;
}
*/
