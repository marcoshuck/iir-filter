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
#include <stdio.h>
#include <util/delay.h>
#include <time.h>

#define BIQUAD(A, B, C, D , E) ((float)((A * B) + C - (D * E)))

#ifndef SAMPLE_FREQ
#define SAMPLE_FREQ 1000
#endif

typedef unsigned char byte;

typedef struct {
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} bits_t;

typedef union {
	byte value;
	bits_t representation;
} byte_t;

typedef union {
	float value;
	byte representation[sizeof(float)];
} float_t;

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
		inputData = 0.0;
		outputData.value = BIQUAD(inputData, denominator[0], z1, 0, 0);
		z1 = BIQUAD(inputData, denominator[1], z2, numerator[1], outputData.value);
		z2 = BIQUAD(inputData, denominator[2], 0, numerator[2], outputData.value);
		for(i = (sizeof(float) - 1); i >= 0; i--) {
			PORTD = (outputData.representation[i]);
		}
		_delay_ms(sampleTime);
	}
}