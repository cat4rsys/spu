#include <cstdio>
#include "asm.h"
#include "utilities.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>

int main( const int argc, char * argv[] )
{
    switch ( argc ) {
    case 1:
    {
        File text = readFile(fopen("program.asm", "rb"));
        prepareFile(&text);

        SPU program = {};

        FILE * inputFile = fopen("program.asm", "rb");

        spuReadSizeOfData(inputFile, &program);

        spuReadLabels(&program, text);
        spuAssemble(fopen("program.asm", "rb"), fopen("program.obj", "wb"), &program);

        closeLabels(program.firstLabel);

        break;
    }
    case 2:
    {
        size_t pathLenght = strlen(argv[1]);

        char * buf = (char *)calloc(sizeof(char), pathLenght);

        strncpy(buf, argv[1], pathLenght - 3);

        buf[pathLenght - 3] = 'o';
        buf[pathLenght - 2] = 'b';
        buf[pathLenght - 1] = 'j';

        File text = readFile(fopen(argv[1], "rb"));
        prepareFile(&text);

        SPU program = {};

        FILE * inputFile = fopen(argv[1], "rb");

        spuReadSizeOfData(inputFile, &program);

        spuReadLabels(&program, text);
        spuAssemble(fopen(argv[1], "rb"), fopen(buf, "wb"), &program);

        closeLabels(program.firstLabel);

        break;
    }
    default:
    {
        fprintf(stderr, "Usage: ./assemble \"path to file\"\n");
    }
    }
}
