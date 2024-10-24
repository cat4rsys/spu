#include <cstdio>
#include "utilities.h"
#include "input.h"

int readSizeOfFile( FILE * file )
{
    fseek(file, 0L, SEEK_END);
    int sizeOfFile = (int)ftell(file) + 1;

    fseek(file, 0L, SEEK_SET);

    return sizeOfFile;
}

void printText( InfoAboutLine ** arrayOfLines, size_t numOfLines, FILE * outputFile )
{
    CASSERT(outputFile);

    for (size_t numOfReadedLines = 0; numOfReadedLines < numOfLines; numOfReadedLines++) {
        fputs( (*(arrayOfLines[numOfReadedLines])).pointerOfBeginning, outputFile );
        fputc('\r', outputFile);
        fputc('\n', outputFile);
    }

    fclose(outputFile);
}

void printAllText( char * text, size_t numOfElements, FILE * outputFile )
{
    CASSERT(outputFile);

    for (size_t numOfReadedSymbols = 0; numOfReadedSymbols < numOfElements; numOfReadedSymbols++) {
        (text[numOfReadedSymbols] != '\0') ? ( fputc(text[numOfReadedSymbols], outputFile) ) :
                                             ( fputc('\r', outputFile) ) ;
    }

    fclose(outputFile);
}
