#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctype.h>
#include "asm.h"
#include "input.h"

void spuReadSizeOfData(FILE * inputFile, SPU * program)
{
    if (!inputFile || !program) {
        fprintf(stderr, "Pointer equals NULL, check input data\n");
        return;
    }

    size_t size = 0;
    char * fictitiousVar = (char *)calloc(10, 1);

    while ( fscanf(inputFile, "%s", fictitiousVar) ) {
        size++;

        if ( feof(inputFile) ) break;
    }

    program->size = size - 1;

    fclose(inputFile);

    return;
}

void spuReadLabels(SPU * data, File text)
{
    int ip = 0;

    for (int i = 0; i < text.numOfLines; i++) {
        InfoAboutLine thisLine = (*(text.arrayOfInfoAboutLines[i]));
        if (thisLine.pointerOfBeginning[thisLine.lenghtOfLine - 1] == ':') {
            printf("%s\n", thisLine.pointerOfBeginning);
            createNewLabel(data, thisLine.pointerOfBeginning, ip, thisLine.lenghtOfLine - 1);
        }
        else if (strstr(thisLine.pointerOfBeginning, "push")) ip += 2;
        else if (strstr(thisLine.pointerOfBeginning, "pop")) ip += 2;
        else if (strstr(thisLine.pointerOfBeginning, "jmp")) ip += 2;
        else if (strstr(thisLine.pointerOfBeginning, "ja")) ip += 2;
        else if (strstr(thisLine.pointerOfBeginning, "jae")) ip += 2;
        else if (strstr(thisLine.pointerOfBeginning, "jb")) ip += 2;
        else if (strstr(thisLine.pointerOfBeginning, "jbe")) ip += 2;
        else if (strstr(thisLine.pointerOfBeginning, "je")) ip += 2;
        else if (strstr(thisLine.pointerOfBeginning, "jne")) ip += 2;
        else if (strstr(thisLine.pointerOfBeginning, "call")) ip += 2;
        else ip += 1;
    }
}

void spuAssemble(FILE * inputFile, FILE * outputFile, SPU * data)
{
    if (!inputFile || !data) {
        fprintf(stderr, "Pointer equals NULL, check input data\n");
        return;
    }

    size_t size = data->size;
    char cmd[15] = {};
    double number = 0;
    char * pointer = 0;

    //fprintf(outputFile, "CODE CMD   ARG  \n");

    for (size_t i = 0; i < size; i++) {
        fscanf(inputFile, "%s", cmd);
        if (!strcmp(cmd, "push")) {
            fprintf(outputFile, "%05d", CMD_PUSH);

            fscanf(inputFile, "%s", cmd);
            BinaryAttributes typeOfArgument = checkArgument(cmd);
            fprintf(outputFile, "%03d ", typeOfArgument);

            if (typeOfArgument == NUM) fprintf(outputFile, "%lg\n", atof(cmd));
            if (typeOfArgument == REG) printReg(outputFile, cmd);
            if (typeOfArgument == RAM_NUM) printRamNum(outputFile, cmd);
            if (typeOfArgument == RAM_REG) printRamReg(outputFile, cmd);
            i++;
            continue;
        }

        if (!strcmp(cmd, "add")) {
            fprintf(outputFile, "%05d000\n", CMD_ADD);
            continue;
        }

        if (!strcmp(cmd, "sub")) {
            fprintf(outputFile, "%05d000\n", CMD_SUB);
            continue;
        }

        if (!strcmp(cmd, "mul")) {
            fprintf(outputFile, "%05d000\n", CMD_MUL);
            continue;
        }

        if (!strcmp(cmd, "div")) {
            fprintf(outputFile, "%05d000\n", CMD_DIV);
            continue;
        }

        if (!strcmp(cmd, "out")) {
            fprintf(outputFile, "%05d000\n", CMD_OUT);
            continue;
        }

        if (!strcmp(cmd, "in")) {
            fprintf(outputFile, "%05d000\n", CMD_IN);
            continue;
        }

        if (!strcmp(cmd, "sqrt")) {
            fprintf(outputFile, "%05d000\n", CMD_SQRT);
            continue;
        }

        if (!strcmp(cmd, "sin")) {
            fprintf(outputFile, "%05d000\n", CMD_SIN);
            continue;
        }

        if (!strcmp(cmd, "cos")) {
            fprintf(outputFile, "%05d000\n", CMD_COS);
            continue;
        }

        if (!strcmp(cmd, "dump")) {
            fprintf(outputFile, "%05d000\n", CMD_DUMP);
            continue;
        }

        if (!strcmp(cmd, "jmp")) {
            fprintf(outputFile, "%05d000 ", CMD_JMP);

            fscanf(inputFile, "%s", cmd);
            int ip = replaceLabel(data, cmd);

            if (ip == -1) break;
            else fprintf(outputFile, "%d\n", ip);
            i++;

            continue;
        }

        if (!strcmp(cmd, "ja")) {
            fprintf(outputFile, "%05d000 ", CMD_JA);

            fscanf(inputFile, "%s", cmd);
            int ip = replaceLabel(data, cmd);

            if (ip == -1) break;
            else fprintf(outputFile, "%d\n", ip);
            i++;

            continue;
        }

        if (!strcmp(cmd, "jae")) {
            fprintf(outputFile, "%05d000 ", CMD_JAE);

            fscanf(inputFile, "%s", cmd);
            int ip = replaceLabel(data, cmd);

            if (ip == -1) break;
            else fprintf(outputFile, "%d\n", ip);
            i++;

            continue;
        }

        if (!strcmp(cmd, "jb")) {
            fprintf(outputFile, "%05d000 ", CMD_JB);

            fscanf(inputFile, "%s", cmd);
            int ip = replaceLabel(data, cmd);

            if (ip == -1) break;
            else fprintf(outputFile, "%d\n", ip);
            i++;

            continue;
        }

        if (!strcmp(cmd, "jbe")) {
            fprintf(outputFile, "%05d000 ", CMD_JBE);

            fscanf(inputFile, "%s", cmd);
            int ip = replaceLabel(data, cmd);

            if (ip == -1) break;
            else fprintf(outputFile, "%d\n", ip);
            i++;

            continue;
        }

        if (!strcmp(cmd, "je")) {
            fprintf(outputFile, "%05d000 ", CMD_JE);

            fscanf(inputFile, "%s", cmd);
            int ip = replaceLabel(data, cmd);

            if (ip == -1) break;
            else fprintf(outputFile, "%d\n", ip);
            i++;

            continue;
        }

        if (!strcmp(cmd, "jne")) {
            fprintf(outputFile, "%05d000 ", CMD_JNE);

            fscanf(inputFile, "%s", cmd);
            int ip = replaceLabel(data, cmd);

            if (ip == -1) break;
            else fprintf(outputFile, "%d\n", ip);
            i++;

            continue;
        }

        if (!strcmp(cmd, "hlt")) {
            fprintf(outputFile, "%05d000\n", CMD_HLT);
            continue;
        }

        if (!strcmp(cmd, "pop")) {
            fprintf(outputFile, "%05d", CMD_POP);

            fscanf(inputFile, "%s", cmd);
            BinaryAttributes typeOfArgument = checkArgument(cmd);
            fprintf(outputFile, "%03d ", typeOfArgument);

            if (typeOfArgument == NUM) fprintf(outputFile, "%lg\n", atof(cmd));
            if (typeOfArgument == REG) printReg(outputFile, cmd);
            if (typeOfArgument == RAM_NUM) printRamNum(outputFile, cmd);
            if (typeOfArgument == RAM_REG) printRamReg(outputFile, cmd);

            i++;
            continue;
        }

        if (!strcmp(cmd, "call")) {
            fprintf(outputFile, "%05d000 ", CMD_CALL);

            fscanf(inputFile, "%s", cmd);
            int ip = replaceLabel(data, cmd);

            if (ip == -1) break;
            else fprintf(outputFile, "%d\n", ip);
            i++;

            continue;
        }

        if (!strcmp(cmd, "ret")) {
            fprintf(outputFile, "%05d000\n", CMD_RET);
            continue;
        }

        if (strstr(cmd, ":")) {
            continue;
        }

        else fprintf(stderr, "COMPILE ERROR: %s\n", cmd);
    }

    fclose(inputFile);
    fclose(outputFile);

    return;
}

BinaryAttributes checkArgument(const char * line)
{
    if (line[0] == '[') {
        if (strstr("+", line) && atof(line) != 0) return RAM_REG_NUM;
        if (isdigit(line[1])) return RAM_NUM;
        else return RAM_REG;
    }

    else {
        if (isdigit(line[0]) || line[0] == '-') return NUM;
        else return REG;
    }
}
/*
void printHeader(FILE * outputFile)
{
    fprintf(outputFile, "cat4rsys\n1.0\n");
}
*/

void printRamNum(FILE * outputFile, char * line)
{
    char * buf = strdup(line + 1);
    int lenght = strlen(buf);

    strncpy(line, buf, lenght);

    fprintf(outputFile, "%lg\n", atof(line));
}

void printRamReg(FILE * outputFile, char * line)
{
    char * buf = strdup(line + 1);
    int lenght = strlen(buf);

    strncpy(line, buf, lenght-1);
    line[lenght-1] = '\0';

    printReg(outputFile, line);
}

void printReg(FILE * outputFile, const char * line)
{
    for (int i = 0; i < 8; i++) {
        if (!strcmp(registers[i], line)) {
            fprintf(outputFile, "%d\n", i);
            return;
        }
    }

    fprintf(stderr, "COMPILE ERROR: NO SUCH REGISTER\n");
    return;
}

int replaceLabel(SPU * data, char * name)
{
    Label * pointer = data->firstLabel;

    while ( (*pointer).nextLabel != NULL ) {
        if ( !strcmp( (*pointer).name, name ) ) {
            return (*pointer).index;
        }

        pointer = (*pointer).nextLabel;
    }

    if ( !strcmp( name, (*pointer).name ) ) {
        return (*pointer).index;
    }

    fprintf(stderr, "COMPILE ERROR: there is no %s label\n", name);
    return -1;
}

void createNewLabel(SPU * data, char * name, int index, int lenght)
{
    Label * pointer = data->firstLabel;
    char buf[maxLenghtOfLine] = {};
    strncpy(buf, name, lenght);
    buf[lenght] = '\0';
    printf("%s\n", buf);

    if (pointer) {
        if ( !strcmp( buf, (*pointer).name ) ) {
            fprintf(stderr, "COMPILE ERROR: TWO SAME LABELS\n");
            return;
        }
        while ( (*pointer).nextLabel != NULL ) {

            if ( !strcmp( buf, (*pointer).name ) ) {
                fprintf(stderr, "COMPILE ERROR: TWO SAME LABELS\n");
                return;
            }

            pointer = (*pointer).nextLabel;
        }
        Label * newLabel = (Label *)calloc(1, sizeof(Label));

        (*pointer).nextLabel = newLabel;
        (*newLabel).index = index;
        (*newLabel).name = strdup(buf);
        (*newLabel).nextLabel = NULL;
    }
    else {
        data->firstLabel = (Label *)calloc(1, sizeof(Label));

        data->firstLabel->index = index;
        data->firstLabel->name = strdup(buf);
        data->firstLabel->nextLabel = NULL;

        printf("\n\n%s\n", data->firstLabel->name);
    }
}
