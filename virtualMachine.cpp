#include "commands.h"
#include "stack.h"
#include "virtualMachine.h"

int main(int argc, char *argv[])
{
    processor proc = {};
    proc.stk = {};
    STACK_INIT(&(proc.stk), initialCapacity);
    STACK_INIT(&(proc.returnStk), initialCapacity);

    struct stat fileInfo;
    if (stat("numericData.asm", &fileInfo) == -1) return INTERPRETER_ERROR;

    proc.code = (int *) calloc(fileInfo.st_size / sizeof(int), sizeof(int));

    FILE *filePointer = NULL;
    fileOpening(&filePointer, "numericData.asm", "r");

    int count = fread(proc.code, sizeof(int), fileInfo.st_size / sizeof(int), filePointer);

    closeFile(&filePointer);

    // for (int i = 0; i < fileInfo.st_size / sizeof(int); i++)
    //     printf("%d ", proc.code[i]);
    // getchar();

    for (proc.IP = 0; proc.IP < count; proc.IP++)
    {
        switch (proc.code[proc.IP])
        {
            case HLT:
                hlt(&proc);

                break;

            case PUSH:
                push(&proc);

                break;

            case ADD:
                add(&proc);

                break;

            case SUB:
                sub(&proc);

                break;

            case MUL:
                mul(&proc);

                break;

            case DIV:
                div(&proc);

                break;

            case OUT_OF:
                out(&proc);

                break;

            case POPr:
                pop(&proc);

                break;

            case PUSHr:
                pushr(&proc);

                break;

            case JMP:
                jmp(&proc);

                break;

            case JA:
                ja(&proc);

                break;

            case JAE:
                jae(&proc);

                break;

            case JB:
                jb(&proc);

                break;

            case JE:
                je(&proc);

                break;

            case JNE:
                jne(&proc);

                break;

            case IN_OF:
                in(&proc);

                break;

            case CALL:
                call(&proc);

                break;

            case RET:
                ret(&proc);

                break;

            default:
                fprintf(stderr, "No such command\n");

                break;
        }
    }

    stackDestroy(&proc.stk);

    free(proc.code);

    return INTERPRETER_CORRECT;
}
