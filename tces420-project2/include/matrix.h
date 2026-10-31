#ifndef MATRIX_TYPE_BEAT
#define MATRIX_TYPE_BEAT

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MATRIX_SIZE 2000

//Just more readble
#define RANDOM_MATRIX_ENTRIES 1
#define UNDEFINED_MATRIX_ENTRIES 0


//This creates an arbitrary matrix 
void* create_matrix(int _size, char rand);


#endif

