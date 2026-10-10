#include "commands.h"
#include "stack.h"
#include "virtualMachine.h"

int main(int argc, char *argv[])
{
    processor proc = {};
    proc.stk = {};
    STACK_INIT(&(proc.stk), initialCapacity);

    struct stat fileInfo;
    if (stat("numericData.asm", &fileInfo) == -1) return INTERPRETER_ERROR;

    proc.code = (int *) calloc(fileInfo.st_size / sizeof(int), sizeof(int));

    FILE *filePointer = NULL;
    fileOpening(&filePointer, "numericData.asm", "r");

    int count = fread(proc.code, sizeof(int), fileInfo.st_size / sizeof(int), filePointer);

    closeFile(&filePointer);

    for (proc.IP = 0; proc.IP < count; proc.IP++)
    {
        switch (proc.code[proc.IP])
        {
            case HLT:
                return INTERPRETER_CORRECT;

                break;

            case PUSH:
                push(&proc);

                break;

            case ADD:
            {
                structEnum_t a = stackPop(&proc.stk);
                structEnum_t b = stackPop(&proc.stk);
                stackPush(&proc.stk, a + b);
            }

                break;

            case SUB:
            {
                structEnum_t a = stackPop(&proc.stk);
                structEnum_t b = stackPop(&proc.stk);
                stackPush(&proc.stk, b - a);
            }

                break;

            case DIV:
            {
                structEnum_t a = stackPop(&proc.stk);
                structEnum_t b = stackPop(&proc.stk);
                if (a != 0)
                {
                    stackPush(&proc.stk,  b / a);
                }
                else
                {
                    fprintf(stderr, "Unable operation\n");

                    return INTERPRETER_ERROR;
                }
            }

                break;

            case OUT_OF:
            {
                structEnum_t value = stackPop(&proc.stk);
                printf(SPEC"\n", value);
            }

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
