#include "stack.h"
#include "virtualMachine.h"

int main(int argc, char *argv[])
{
    char *buffer = NULL;

    struct stat fileInfo;
    if (stat("data.asm", &fileInfo) == -1) return INTERPRETER_ERROR;

    buffer = (char *)(calloc(fileInfo.st_size + 1, sizeof(char)));

    int dp = fileOpenDp("data.asm", O_RDONLY);

    int realCount = read(dp, buffer, fileInfo.st_size);

    buffer[realCount] = '\0';

    int nLines = 0;
    char *pointer = buffer;

    while ((pointer = strchr(pointer, '\n')) != NULL)
    {
        nLines++;
        pointer += 1;
    }

    pointer = buffer;

    char **index = NULL;
    index = (char **)calloc(nLines, sizeof(char *));

    int i = 1;
    index[0] = pointer;
    while ((pointer = strchr(pointer, '\n')) != NULL && i < nLines)
    {
        *pointer = '\0';
        pointer += 1;
        index[i] = pointer;
        i++;
    }

    fileCloseDp(dp);
    //------------------------------------------------------------------------
    stack_t stk1 = {};
    size_t initialCapacity = 10;
    STACK_INIT(&stk1, initialCapacity);

    int value = 0;
    char command[10] = {};

    for (int i = 0; i < nLines; i++)
    {
        command[0] = '\0';
        value = 0;

        int number = sscanf(index[i], "%s %d", command, &value);
        if (number <= 0)
            continue;
//TODO - в последующем заменить на switch

        if (strcmp(command, "PUSH") == 0)
        {
            stackPush(&stk1, value);
        }
        else if (strcmp(command, "ADD") == 0)
        {
            structEnum_t a = stackPop(&stk1);
            structEnum_t b = stackPop(&stk1);
            stackPush(&stk1, a + b);
        }
        else if (strcmp(command, "SUB") == 0)
        {
            structEnum_t a = stackPop(&stk1);
            structEnum_t b = stackPop(&stk1);
            stackPush(&stk1, b - a);
        }
        else if (strcmp(command, "DIV") == 0)
        {
            structEnum_t a = stackPop(&stk1);
            structEnum_t b = stackPop(&stk1);
            if (a != 0)
            {
                stackPush(&stk1,  b / a);
            }
            else
            {
                fprintf(stderr, "Unable operation");

                return INTERPRETER_ERROR;
            }
        }
        else if (strcmp(command, "OUT") == 0)
        {
            structEnum_t value = stackPop(&stk1);
            printf(SPEC, value);
        }
        else if (strcmp(command, "HLT") == 0)
        {
            break;
        }
    }

    stackDestroy(&stk1);

    free(buffer);
    free(index);

    return INTERPRETER_CORRECT;
}

int fileOpenDp(const char *fileName, int flag)
{
    int fileDescriptor = open(fileName, flag);

    if (fileDescriptor == -1)
    {
        fprintf(stderr, "Unable to open %s\n", fileName);

        return INTERPRETER_ERROR;
    }

    return fileDescriptor;
}

returnValue fileCloseDp(int descriptor)
{
    if (close(descriptor) == -1)
    {
        return INTERPRETER_ERROR;
    }

    return INTERPRETER_CORRECT;
}
