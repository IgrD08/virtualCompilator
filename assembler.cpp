#include "commands.h"
#include "stack.h"
#include "assembler.h"

int main(int argc, char *argv[])
{
    char *buffer = NULL;

    struct stat fileInfo;
    if (stat("data.asm", &fileInfo) == -1) return INTERPRETER_ERROR;

    buffer = (char *)(calloc(fileInfo.st_size + 1, sizeof(char)));

    FILE *fileAssemblerRead = NULL;
    fileOpening(&fileAssemblerRead, "data.asm", "r");

    int realCount = fread(buffer, sizeof(char), fileInfo.st_size, fileAssemblerRead);

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

    closeFile(&fileAssemblerRead);
    //------------------------------------------------------------------------

    int value = 0;
    char command[10] = {};
    int *data = (int *)calloc(nLines * 2, sizeof(int));
    int dataIndex = 0;

    for (int i = 0; i < nLines; i++)
    {
        command[0] = '\0';
        value = 0;

        int number = sscanf(index[i], "%s %d", command, &value);
        if (number <= 0)
            continue;

        switch (command[0])
        {
            case 'P':
                if (!strcmp(command, "PUSH"))
                {
                    data[dataIndex] = PUSH;
                    dataIndex++;
                    data[dataIndex] = value;
                    dataIndex++;
                }

                break;

            case 'A':
                if (!strcmp(command, "ADD"))
                {
                    data[dataIndex] = ADD;
                    dataIndex++;
                }

                break;

            case 'S':
                if (!strcmp(command, "SUB"))
                {
                    data[dataIndex] = SUB;
                    dataIndex++;
                }

                break;

            case 'D':
                if (!strcmp(command, "DIV"))
                {
                    data[dataIndex] = DIV;
                    dataIndex++;
                }

                break;

            case 'O':
                if (!strcmp(command, "OUT_OF"))
                {
                    data[dataIndex] = OUT_OF;
                    dataIndex++;
                }

                break;

            case 'H':
                if (!strcmp(command, "HLT"))
                {
                    data[dataIndex] = HLT;
                    dataIndex++;
                }

                break;

            default:
                fprintf(stderr, "No such command");

                break;
        }
    }

    FILE *filePointerWrite = NULL;
    fileOpening(&filePointerWrite, "numericData.asm", "wb");

    fwrite(data, sizeof(int), dataIndex, filePointerWrite);
    free(data);
    free(buffer);
    free(index);

    closeFile(&filePointerWrite);

    return INTERPRETER_CORRECT;
}

