#ifndef INPUT_H
#define INPUT_H

typedef struct
{
    char * pointerOfBeginning;
    size_t lenghtOfLine;
} InfoAboutLine;

typedef struct
{
    char * str;
    int numOfElements;
    int numOfLines;
    InfoAboutLine ** arrayOfInfoAboutLines;
} File;

File readFile( FILE * inputFile );

void prepareFile( File * inputFile );

void divisionLines(File * allFile);

void readPointersOfLines(File * allFile);

#endif // INPUT_H
