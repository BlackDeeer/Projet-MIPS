#ifndef __CONVERSION_H__
#define __CONVERSION_H__

#include <stdlib.h>
#include <math.h>

int bin_to_int(char* bin, int length);
void int_to_binary( int x, int length, int binary[]);
void bin_to_hexa(int length, int bin_operation[], char hexa_operation[] );
void hexa_to_bin(int length, char *hexa, int bin[32], int length_bin);

#endif