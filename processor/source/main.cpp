#include "spu.h"
#include <cstdio>

int main(const int argc, char * argv[])
{
    switch (argc) {
    case 1:
    {
        SPU program = {};
        FILE * inputFile = fopen("program.obj", "r");

        if (!inputFile) {
            fprintf(stderr, "Can't run program. Is in your directory program.asm file?\n");
            return -1;
        }

        spuReadSizeOfData(inputFile, &program);
        spuReadData(inputFile, &program);

        spuRun(&program);

        fclose(inputFile);

        return 0;
    }
    case 2:
    {
        SPU program = {};
        FILE * inputFile = fopen(argv[1], "r");

        if (!inputFile) {
            fprintf(stderr, "Can't run program. Is in your directory program.asm file?\n");
            return -1;
        }

        spuReadSizeOfData(inputFile, &program);
        spuReadData(inputFile, &program);

        spuRun(&program);

        fclose(inputFile);

        return 0;
    }
    default:
    {
                        // FAIL! Usage ...
        fprintf(stderr, "Incorrect input. You should write path to your *.asm file or just write \"spu\"\n");

        return -1;
    }
    }
}
