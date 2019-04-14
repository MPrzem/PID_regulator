#ifndef PWM_PWM_H_
#define PWM_PWM_H_
#include <stdlib.h>
#include "../1wire/ds18x20.h"
#include "../Lcd/HD44780.h"
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "../1wire/ds18x20.h"

#define PWM_F PB3 //Pin sprzetowego kanalu PWM Timer2
#define PWM_H PB1// Pin sprzetowego kana³u PWM (czêœc A timera 1)
struct {
uint8_t Kp;	//Wzmocnienie
uint8_t Ti;			//Sta³a czasowa ca³kowania
uint8_t Td;			//Sta³a czasowa ró¿niczkowania
uint8_t dt;		//Czas zmian wielkoœci
int deviation;
int deviation_prev;
int integral_memory;
uint8_t out;
uint8_t temp_expected;//Ma byc zmieniana przy pomocy klawiszy

} Pid;
extern const char temp_text [] PROGMEM;
extern const char error[] PROGMEM;
extern const char temp_zad_text [] PROGMEM ;
extern const char fanpowertext [] PROGMEM ;


uint8_t sensors;
uint8_t temp1,temp1_fraction,sign;//Odczyt aktualnej temperatury (Pojawia sie problem czesci ulamkowej)
//w zasadzie i tak trzeba bedzie przekazac PID floata. Albo uchyb pomnozyc x10 dodac czesc ulamkowa a wartosci nastaw PID /10

//void fan_control(void);
void Pwm_init(void);
void Display();
void ask_sensors(void);
// Calka metoda trapezow
int integral();
//Pochodna int(bo pochodna moze byc ujemna)
int deriverate();
///W tej funkcji odbywa sie sterowanie PID, wersja testowa- tylko czesc calkowita
int Pid_control(uint8_t current_temp);

#endif /* PWM_PWM_H_ */
