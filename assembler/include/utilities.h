#ifndef UTILITIES_H
#define UTILITIES_H

#include "stdio.h"
#include "input.h"

#define CASSERT(expression) {                                               \
    if( !(expression) ) {                                                   \
        printf("Assertion failed: file %s, line %d\n", __FILE__, __LINE__); \
    }                                                                       \
}

typedef int (* compare_funcptr)(const void * firstElem, const void * secondElem);

int readSizeOfFile( FILE * file );

void printText( InfoAboutLine ** arrayOfLines, size_t numOfLines, FILE * outputFile );

void printAllText( char * text, size_t numOfElements, FILE * outputFile );

#endif // UTILITIES_H
