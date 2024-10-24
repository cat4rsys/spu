#include "stack.h"
#include "spu.h"
#include "log.h"
#include "utilities.h"
#include <cstdio>
#include <cmath>

void spuRun(SPU * program)
{
    Stack stk = {};
    Stack funcStack = {};

    stk.logFile = fopen("logfile.htm", "w");
    logInit(stk.logFile);

    double * data = program->data;

    DO_STACK_CTOR(&stk, 50);
    DO_STACK_CTOR(&funcStack, 10);

    int  ip  = 0;
    bool run = 1;

    while ( run ) {
        switch ( ((int) data[ip] ) / 1000 )
        {
            case CMD_PUSH:
            {
                switch ( ((int) data[ip] ) % 1000 )
                {
                    case NUM:
                    {
                        DO_STACK_PUSH(&stk, data[ip+1]);
                        break;
                    }

                    case REG:
                    {
                        DO_STACK_PUSH(&stk, program->registers[(int) data[ip+1]]);
                        break;
                    }

                    case RAM_NUM:
                    {
                        DO_STACK_PUSH(&stk, program->RAM[(int) data[ip+1]]);
                        break;
                    }

                    case RAM_REG:
                    {
                        DO_STACK_PUSH(&stk, program->RAM[(int) program->registers[ (int) data[ip+1]]]);
                        break;
                    }

                    default:
                    {
                        fprintf(stderr, "COMPILE ERROR\n");
                        break;
                    }

                }

                ip += 2;

                break;
            }
            case CMD_POP:
            {
                switch ( ((int) data[ip] ) % 1000 )
                {
                    case REG:
                    {
                        DO_STACK_POP(&stk, &(program->registers[(int) data[ip+1]]));
                        break;
                    }

                    case RAM_NUM:
                    {
                        DO_STACK_POP(&stk, &(program->RAM[(int) data[ip+1]]));
                        break;
                    }

                    case RAM_REG:
                    {
                        DO_STACK_POP(&stk, &(program->RAM[(int) program->registers[ (int) data[ip+1]]]));
                        break;
                    }

                    default:
                    {
                        fprintf(stderr, "COMPILE ERROR\n");
                        break;
                    }

                }

                ip += 2;
                break;
            }
            case CMD_ADD:
            {
                double firstOperand  = 0;
                double secondOperand = 0;

                DO_STACK_POP(&stk, &firstOperand);
                DO_STACK_POP(&stk, &secondOperand);

                double result = firstOperand + secondOperand;

                DO_STACK_PUSH(&stk, result);

                ip += 1;

                break;
            }
            case CMD_SUB:
            {
                double firstOperand  = 0;
                double secondOperand = 0;

                DO_STACK_POP(&stk, &secondOperand);
                DO_STACK_POP(&stk, &firstOperand);

                double result = firstOperand - secondOperand;

                DO_STACK_PUSH(&stk, result);

                ip += 1;

                break;
            }
            case CMD_MUL:
            {
                double firstOperand  = 0;
                double secondOperand = 0;

                DO_STACK_POP(&stk, &secondOperand);
                DO_STACK_POP(&stk, &firstOperand);

                double result = firstOperand * secondOperand;

                DO_STACK_PUSH(&stk, result);

                ip += 1;

                break;
            }
            case CMD_DIV:
            {
                double firstOperand  = 0;
                double secondOperand = 0;

                DO_STACK_POP(&stk, &secondOperand);
                DO_STACK_POP(&stk, &firstOperand);

                double result = firstOperand / secondOperand;

                DO_STACK_PUSH(&stk, result);

                ip += 1;

                break;
            }
            case CMD_OUT:
            {
                double poppedElement = 0;

                DO_STACK_POP(&stk, &poppedElement);

                fprintf(stdout, "Element for out = %lg\n", poppedElement);

                ip += 1;

                break;
            }
            case CMD_IN:
            {
                double elementForPush = 0;

                fscanf(stdin, "%lg", &elementForPush);

                DO_STACK_PUSH(&stk, elementForPush);

                ip += 1;

                break;
            }
            case CMD_SQRT:
            {
                double number = 0;

                DO_STACK_POP(&stk, &number);

                if (number < 0) {
                    DO_STACK_PUSH(&stk, -1);
                    fprintf(stderr, "MATH ERROR: can`t sqrt negative number. Filled -1\n");
                }
                else {
                    number = sqrt(number);
                    DO_STACK_PUSH(&stk, number);
                }

                ip += 1;

                break;
            }
            case CMD_SIN:
            {
                double number = 0;

                DO_STACK_POP(&stk, &number);

                number = sin(number);
                DO_STACK_PUSH(&stk, number);

                ip += 1;

                break;
            }
            case CMD_COS:
            {
                double number = 0;

                DO_STACK_POP(&stk, &number);

                number = cos(number);
                DO_STACK_PUSH(&stk, number);

                ip += 1;

                break;
            }
            case CMD_DUMP:
            {
                DO_STACK_DUMP(&stk);

                ip += 1;

                break;
            }
            case CMD_HLT:
            {
                DO_STACK_DTOR(&stk);

                run = 0;
                break;
            }
            case CMD_JMP:
            {
                ip = (int) data[ip+1];

                break;
            }
            case CMD_JA:
            {
                double firstOperand  = 0;
                double secondOperand = 0;

                DO_STACK_POP(&stk, &secondOperand);
                DO_STACK_POP(&stk, &firstOperand);

                if (compareDouble(firstOperand, secondOperand) == GREATER) ip = (int) data[ip+1];
                else ip += 2;

                break;
            }
            case CMD_JAE:
            {
                double firstOperand  = 0;
                double secondOperand = 0;

                DO_STACK_POP(&stk, &secondOperand);
                DO_STACK_POP(&stk, &firstOperand);

                StatusDouble result = compareDouble(firstOperand, secondOperand);

                if (result == GREATER || result == EQUALS) ip = (int) data[ip+1];
                else ip += 2;

                break;
            }
            case CMD_JB:
            {
                double firstOperand  = 0;
                double secondOperand = 0;

                DO_STACK_POP(&stk, &secondOperand);
                DO_STACK_POP(&stk, &firstOperand);

                if (compareDouble(firstOperand, secondOperand) == LESS) ip = (int) data[ip+1];
                else ip += 2;

                break;
            }
            case CMD_JBE:
            {
                double firstOperand  = 0;
                double secondOperand = 0;

                DO_STACK_POP(&stk, &secondOperand);
                DO_STACK_POP(&stk, &firstOperand);

                StatusDouble result = compareDouble(firstOperand, secondOperand);

                if (result == LESS || result == EQUALS) ip = (int) data[ip+1];
                else ip += 2;

                break;
            }
            case CMD_JE:
            {
                double firstOperand  = 0;
                double secondOperand = 0;

                DO_STACK_POP(&stk, &secondOperand);
                DO_STACK_POP(&stk, &firstOperand);

                if (compareDouble(firstOperand, secondOperand) == EQUALS) ip = (int) data[ip+1];
                else ip += 2;

                break;
            }
            case CMD_JNE:
            {
                double firstOperand  = 0;
                double secondOperand = 0;

                DO_STACK_POP(&stk, &secondOperand);
                DO_STACK_POP(&stk, &firstOperand);

                if (compareDouble(firstOperand, secondOperand) != EQUALS) ip = (int) data[ip+1];
                else ip += 2;

                break;
            }
            case CMD_CALL:
            {
                DO_STACK_PUSH(&funcStack, ip + 2.0);
                ip = (int) data[ip + 1];


                break;
            }
            case CMD_RET:
            {
                double ipp = 0;
                DO_STACK_POP(&funcStack, &ipp);

                ip = (int) ipp;

                break;
            }
            default:
            {
                fprintf(stderr, "SNTXERR %d\n", (int) data[ip]);

                run = 0;
                break;
            }
        }
    }
}

void spuReadSizeOfData(FILE * inputFile, SPU * program)
{
    if (!inputFile || !program) {
        fprintf(stderr, "Pointer equals NULL, check input data\n");
        return;
    }

    size_t size = 0;
    double fictitiousVar = 0;

    while ( fscanf(inputFile, "%lf", &fictitiousVar) ) {
        size++;

        if ( feof(inputFile) ) break;
    }

    program->size = size - 1;
    fseek(inputFile, 0, SEEK_SET);

    return;
}

void spuReadData(FILE * inputFile, SPU * program)
{
    if (!inputFile || !program) {
        fprintf(stderr, "Pointer equals NULL, check input data\n");
        return;
    }

    size_t size = program->size;

    double * data = (double *)calloc(size, sizeof(double));
    if (!data) {
        fprintf(stderr, "Can`t make program array of this size, try make your file smaller\n");
        return;
    }

    for (size_t i = 0; i < size; i++) {
        fscanf(inputFile, "%lg", (data + i));
    }

    program->data = data;

    return;
}

