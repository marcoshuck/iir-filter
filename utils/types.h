/*
 *		UTN - FRP
 *
 *		types.h
 *	Different representations of types
 *
 *	  by Marcos Huck
 *	<marcos@huck.com.ar>
 */


#ifndef TYPES_H_
#define TYPES_H_

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

typedef union {
	int value;
	byte representation[sizeof(int)];
} int_t;



#endif /* TYPES_H_ */