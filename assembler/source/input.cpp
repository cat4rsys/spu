#include <stdio.h>
#include <stdlib.h>
#include <input.h>
#include <utilities.h>

File readFile( FILE * inputFile )
{
    CASSERT(inputFile != NULL);

    File allFile = {};

    allFile.numOfElements = readSizeOfFile(inputFile);

    allFile.str = (char * )calloc( allFile.numOfElements, sizeof(char) );
    CASSERT(allFile.str != NULL);

    fread(allFile.str, sizeof(char), allFile.numOfElements, inputFile);

    fclose(inputFile);

    return allFile;
}

void prepareFile( File * inputFile )
{
    divisionLines(inputFile);
    readPointersOfLines(inputFile);
}

void divisionLines(File * allFile)
{
    allFile->numOfLines = 1;

    for (int currentFilePos = 0; currentFilePos < allFile->numOfElements; currentFilePos++) {
        if ( *(allFile->str + currentFilePos) == '\r' ) {
            *(allFile->str + currentFilePos) = '\0';
            allFile->numOfLines++;
        }
    }

    *( (allFile->str) + (allFile->numOfElements - 1) ) = '\0';
}

void readPointersOfLines(File * allFile)
{
    allFile->arrayOfInfoAboutLines = (InfoAboutLine ** )calloc(allFile->numOfLines, sizeof(InfoAboutLine *));
    InfoAboutLine * arrayOfLines = (InfoAboutLine * )calloc(allFile->numOfLines, sizeof(InfoAboutLine));

    *(arrayOfLines) = {allFile->str, 0};
    *(allFile->arrayOfInfoAboutLines) = arrayOfLines;
    int readedLines = 1;

    for (int currentFilePos = 0; currentFilePos < allFile->numOfElements; currentFilePos++) {
        if ( *(allFile->str + currentFilePos) == '\n' ) {
            arrayOfLines[readedLines].pointerOfBeginning = allFile->str + currentFilePos + 1;
            allFile->arrayOfInfoAboutLines[readedLines] = &(arrayOfLines[readedLines]);

            arrayOfLines[readedLines - 1].lenghtOfLine = (size_t) ( arrayOfLines[readedLines].pointerOfBeginning -
                                                                    arrayOfLines[readedLines - 1].pointerOfBeginning - 2 );

            readedLines += 1;

            if (readedLines == allFile->numOfLines) {
                currentFilePos = allFile->numOfElements;
            }
        }
    }

    if ( *( (allFile->str) + (allFile->numOfElements - 2) ) == '\n' ) {
        allFile->numOfLines -= 1;
    }
    else {
        arrayOfLines[readedLines - 1].lenghtOfLine = arrayOfLines[0].pointerOfBeginning + allFile->numOfElements -
                                                     arrayOfLines[readedLines - 1].pointerOfBeginning - 1;
    }
}


