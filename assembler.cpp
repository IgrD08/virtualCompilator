#include "stack.h"
#include "assembler.h"

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
    FILE *filePointer = NULL;
    fileOpening(&filePointer, "numericData.asm");

    int value = 0;
    char command[10] = {};

    for (int i = 0; i < nLines; i++)
    {
        command[0] = '\0';
        value = 0;

        int number = sscanf(index[i], "%s %d\n", command, &value);
        if (number <= 0)
            continue;

        switch (command[0])
        {
            case 'P':
                if (!strcmp(command, "PUSH"))
                    fprintf(filePointer, "%d %d\n", 1, value);

                break;

            case 'A':
                if (!strcmp(command, "ADD"))
                    fprintf(filePointer, "%d %d\n", 2, value);

                break;

            case 'S':
                if (!strcmp(command, "SUB"))
                    fprintf(filePointer, "%d %d\n", 3, value);

                break;

            case 'D':
                if (!strcmp(command, "DIV"))
                    fprintf(filePointer, "%d %d\n", 4, value);

                break;

            case 'O':
                if (!strcmp(command, "OUT"))
                    fprintf(filePointer, "%d %d\n", 5, value);

                break;

            case 'H':
                if (!strcmp(command, "HLT"))
                    fprintf(filePointer, "%d %d\n", 0, value);

                break;
        }
    }

    free(buffer);
    free(index);

    closeFile(&filePointer);

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
