/*
 * PID_values.h
 *
 *  Created on: 20 kwi 2019
 *      Author: Student241580
 */

#ifndef PID_PID_VALUES_H_
#define PID_PID_VALUES_H_


#define KP 70
#define TI 20
#define TD  0			//Sta³a czasowa ró¿niczkowania
#define TEMP_EXPECTED 40
#define INTEGRAL_LIMIT 85
//#define DT DS18B20_TCONV_10BIT/1000 // Czas konwersji w sekundach,czas do oblicznia calki i pochodnej
#define RESOLUTION 10

#define DS18B20_TCONV_S   0.75f

#if RESOLUTION==12
#define DT DS18B20_TCONV_S
#elif RESOLUTION==11
#define DT DS18B20_TCONV_S/2
#elif RESOLUTION==10
#define DT DS18B20_TCONV_S/4
#elif RESOLUTION==9
#define DT DS18B20_TCONV_S/8
#else
#error WRONG RESOLUTION
#endif

#endif /* PID_PID_VALUES_H_ */
