#ifndef PID_PID_H_
#define PID_PID_H_
#include "PID_values.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include "../1wire/ds18x20.h"
#include "../Lcd/HD44780.h"
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "../1wire/ds18x20.h"

#define PWM_F PB3 //Pin sprzetowego kanalu PWM Timer2
#define PWM_H PB1// Pin sprzetowego kana³u PWM (czêœc A timera 1)
struct PID1{
uint8_t Kp;	//Wzmocnienie
uint8_t Ti;			//Sta³a czasowa ca³kowania
uint8_t Td;			//Sta³a czasowa ró¿niczkowania
float dt;	//Czas zmian wielkoœci
float deviation;
float deviation_prev;
float integral_memory;
int out;
float temp_expected;//Ma byc zmieniana przy pomocy klawiszy
};

extern const char temp_text [] PROGMEM;
extern const char error[] PROGMEM;
extern const char temp_zad_text [] PROGMEM ;
extern const char fanpowertext [] PROGMEM ;


uint8_t sensors;
uint8_t temp1,temp1_fraction,sign;//Odczyt aktualnej temperatury (Pojawia sie problem czesci ulamkowej)

void Pwm_init(void);
void Display();
void ask_sensors(void);
// Calka metoda trapezow
float integral();
//Pochodna int(bo pochodna moze byc ujemna)
float deriverate();
///W tej funkcji odbywa sie sterowanie PID
int Pid_control();

#endif /* PID_PID_H_ */
