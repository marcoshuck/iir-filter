/*
 *		UTN - FRP
 *
 *		Low Pass
 *	IIR Digital Filter
 *
 *	  by Marcos Huck
 *	<marcos@huck.com.ar>
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include <util/delay.h>
#include <time.h>
#include "types.h"

#define BIQUAD(A, B, C, D , E) ((float)((A * B) + C - (D * E)))

#ifndef SAMPLE_FREQ
#define SAMPLE_FREQ 1000
#endif

static int analogRead(uint8_t pin);

int main(void) {
	const float sampleTime = (1/SAMPLE_FREQ) * 1000;
	const float numerator[] = {0.02008, 0.04017, 0.02008};
	const float denominator[] = {1.0, -1.561, 0.6414};
	static volatile float inputData;
	static float_t outputData;
	static float z1, z2;
	static unsigned int i;

	z1 = z2 = 0.0;
	outputData.value = 0.0;
  
	DDRD = 0b11111111;

	while(1) {
		inputData = analogRead(0);
		outputData.value = BIQUAD(inputData, denominator[0], z1, 0, 0);
		z1 = BIQUAD(inputData, denominator[1], z2, numerator[1], outputData.value);
		z2 = BIQUAD(inputData, denominator[2], 0, numerator[2], outputData.value);
		for(i = (sizeof(float) - 1); i >= 0; i--) {
			PORTD = (outputData.representation[i]);
		}
		_delay_ms(sampleTime);
	}
}

static int analogRead(uint8_t pin) {
	uint8_t high, low;
	if (pin >= 14) {
		pin -= 14;
	}
	
	#if defined(ADCSRB) && defined(MUX5)
	ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin >> 3) & 0x01) << MUX5);
	#endif
	
	#if defined(ADMUX)
	ADMUX = (analog_reference << 6) | (pin & 0x07);
	#endif
	
	_SFR_BYTE(ADCSRA) |= _BV(ADSC);
	loop_until_bit_is_set(ADCSRA, ADSC);
	low  = ADCL;
	high = ADCH;
	return (high << 8) | low;
}