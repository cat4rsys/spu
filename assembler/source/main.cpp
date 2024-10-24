#include <cstdio>
#include "asm.h"
#include "utilities.h"
#include "input.h"

int main()
{
    File text = readFile(fopen("program.asm", "rb"));
    prepareFile(&text);

    SPU program = {};

    FILE * inputFile = fopen("program.asm", "rb");

    spuReadSizeOfData(inputFile, &program);

    spuReadLabels(&program, text);
    printf("%s\n", program.firstLabel->name);
    spuAssemble(fopen("program.asm", "rb"), fopen("program.obj", "wb"), &program);
}
