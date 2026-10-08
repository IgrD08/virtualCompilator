#include "stack.h"
#include "interpreter.h"

int main(int argc, char *argv[])
{
    char *buffer = NULL;

    struct stat fileInfo;
    if (stat("data.asm", &fileInfo) == -1) return INTERPRETER_ERROR;

    buffer = (char *)(calloc(fileInfo.st_size + 1, sizeof(char)));

    int dp = fileOpenDp("data.asm", O_RDONLY);

    read(dp, buffer, fileInfo.st_size);

    buffer[fileInfo.st_size] = '\0';

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
    char call[10] = {};

    for (int i = 0; i < nLines; i++)
    {
        sscanf(index[i], "%s %d", call, &value);
//TODO - печатает последний элемент дважды
        printf("%s\n", call);
        printf("%d\n", value);
//TODO - в последующем заменить на switch
        if (strcmp(call, "PUSH") == 0)
        {
            printf("1\n");
            stackPush(&stk1, value);
            stackDump(&stk1, stdout);

        }
        else if (strcmp(call, "ADD") == 0)
        {
            stackPush(&stk1, stackPop(&stk1) + stackPop(&stk1));
        }
        else if (strcmp(call, "SUB") == 0)
        {
            stackPush(&stk1, -stackPop(&stk1) + stackPop(&stk1));
        }
        else if (strcmp(call, "SUB") == 0)
        {
            stackPush(&stk1, stackPop(&stk1) / (stackPop(&stk1)));
        }
        else if (strcmp(call, "OUT") == 0)
        {
            structEnum_t value = stackPop(&stk1);
            printf(SPEC, value);
            stackPush(&stk1, value);
        }
        else if (strcmp(call, "HLT") == 0)
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
