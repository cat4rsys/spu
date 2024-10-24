#include <cstdio>

typedef struct
{
    double * data;
    size_t size;

    double registers[8];

    double RAM[30000];
} SPU;

enum BinaryCommands {                     // 5 bit for id command. max 32
    CMD_PUSH  = 1,
    CMD_ADD   = 10,
    CMD_SUB   = 11,
    CMD_MUL   = 100,
    CMD_DIV   = 101,
    CMD_OUT   = 110,
    CMD_IN    = 111,
    CMD_SQRT  = 1000,
    CMD_SIN   = 1001,
    CMD_COS   = 1010,
    CMD_DUMP  = 1011,
    CMD_JMP   = 1100,
    CMD_JA    = 1101,
    CMD_JAE   = 1110,
    CMD_JB    = 1111,
    CMD_JBE   = 10000,
    CMD_JE    = 10001,
    CMD_JNE   = 10010,
    CMD_POP   = 10011,
    CMD_CALL  = 10100,
    CMD_RET   = 10101,
    CMD_HLT   = 0
};

enum BinaryAttributes {
    ERR         = 0,
    NUM         = 1,
    REG         = 10,
    RAM_NUM     = 101,
    RAM_REG     = 110,
    RAM_REG_NUM = 111
};

void spuRun(SPU * program);

void spuReadData(FILE * inputFile, SPU * program);

void spuReadSizeOfData(FILE * inputFile, SPU * program);
