#include "commands.h"
#include "stack.h"
#include "virtualMachine.h"

returnValue(*arrayOfFunctionPointers[NUMBER_OF_FUNCTIONS])(processor *proc) = {
                                                                               hlt, push, add, sub, mul, div,
                                                                               out, pop, pushr, jmp, ja, jae,
                                                                               jb, jbe, je, jne, in, call, ret,
                                                                               pushm, popm
                                                                              };

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        fprintf(stderr, "Insufficient files\n");
        return 1;
    }

    processor proc = {};
    proc.stk = {};
    STACK_INIT(&(proc.stk), initialCapacity);
    STACK_INIT(&(proc.returnStk), initialCapacity);

    struct stat fileInfo;
    if (stat(argv[1], &fileInfo) == -1)
        return INTERPRETER_ERROR;

    proc.code = (int *) calloc((size_t)fileInfo.st_size / sizeof(int), sizeof(int));

    FILE *filePointer = NULL;
    if (fileOpening(&filePointer, "numericData.asm", "rb") == 1)
            return 1;

    size_t count = fread(proc.code, sizeof(int), (size_t)fileInfo.st_size / sizeof(int), filePointer);

    if (closeFile(&filePointer) == 1)
        return 1;

    for (size_t i = 0; i < (size_t)fileInfo.st_size / sizeof(int); i++)
        printf("%d ", proc.code[i]);
    getchar();

    for (proc.IP = 0; proc.IP < count; proc.IP++)
    {
        printf("COMMAND NUMBER: <%d>", proc.code[proc.IP]);
        getchar();

        if (proc.code[proc.IP] >= 0 || proc.code[proc.IP] <= NUMBER_OF_FUNCTIONS)
            arrayOfFunctionPointers[proc.code[proc.IP]](&proc);
        else
        {
            fprintf(stderr, "Segmentation fault...");

            return 1;
        }
        stackDump(&proc.stk, stdout);

        printf("%d %d\n", proc.RAM[0], proc.RAM[1]);
    }

    processorDestroyer(&proc);

    return INTERPRETER_CORRECT;
}
