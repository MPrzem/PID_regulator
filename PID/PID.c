/*
 * Pwm.c
 *
 *  Created on: 8 mar 2019
 *      Author: Student241580
 */

#include "../PID/PID.h"
const char temp_text [] PROGMEM = "T:";
const char temp_zad_text [] PROGMEM = " T zad.:";

const char error[] PROGMEM="Awaria czujnika";
const char fanpowertext [] PROGMEM ="Moc wiatr.:" ;
struct PID1 Pid ={KP,TI,TD,DT,0,0,0,0,TEMP_EXPECTED};

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
	LCD_WriteText_P(temp_zad_text);
	LCD_WriteText(itoa(Pid.temp_expected,buf,10));
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
if(!(DS18X20_OK==DS18X20_read_meas(gSensorIDs[0],&sign,&temp1,&temp1_fraction))){
	LCD_Clear();
	LCD_WriteText_P(error);
	_delay_ms(1000);
	return;
}
Pid.deviation_prev=Pid.deviation;
///fe. temp1=25 temp1_fraction 5 ->255 ->25.5
Pid.deviation=(float)(temp1*10)/10-Pid.temp_expected;
if(Pid.deviation<0.15&&Pid.deviation>-0.15)//Tolerancja +-0.15C
	Pid.deviation=0;
}
//calka jedenej chwili czasowej. Podajemy wartosc poczatkowa i koncowa chwili
//Ponizsze funkcje nie zmieniaja uchybu obecnego na poprzedni, ja bym tutaj uzyl static
float integral(){
	 Pid.integral_memory+=(Pid.deviation + Pid.deviation_prev)/2*Pid.dt;
	 if(Pid.integral_memory>INTEGRAL_LIMIT)
		 Pid.integral_memory=INTEGRAL_LIMIT;
	 if(Pid.integral_memory<-INTEGRAL_LIMIT)
		 Pid.integral_memory=-INTEGRAL_LIMIT;
	 return Pid.integral_memory;

}

float deriverate(){
	return  ((Pid.deviation - Pid.deviation_prev)/Pid.dt);
}

int Pid_control(){
	 Pid.out = Pid.Kp*(Pid.deviation + integral()/Pid.Ti +Pid.Td*deriverate());
	 if(Pid.out>255)
		 Pid.out=255;
	 if(Pid.out<0)
		 Pid.out=0;
	return Pid.out;

}
