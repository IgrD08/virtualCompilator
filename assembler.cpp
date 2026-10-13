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
    char regist[10] = {};
    int *data = (int *)calloc(nLines * 2, sizeof(int));
    int dataIndex = 0;

    for (int i = 0; i < nLines; i++)
    {
        command[0] = '\0';
        regist[0] = '\0';
        value = 0;

        if (sscanf(index[i], "%s", command) <= 0)
            continue;

        switch (command[0])
        {
            case 'P':
                if (!strcmp(command, "PUSH"))
                {
                    if (sscanf(index[i], "%*s %s", regist) <= 0)
                        break;

                    if (atoi(regist) == 0)
                    {
                        data[dataIndex] = PUSH;
                        dataIndex++;

                        if (!strcmp(regist, "AX"))
                            data[dataIndex] = AX;
                        else if (!strcmp(regist, "BX"))
                            data[dataIndex] = BX;
                        else if (!strcmp(regist, "CX"))
                            data[dataIndex] = CX;
                        else if (!strcmp(regist, "DX"))
                            data[dataIndex] = DX;
                        else
                            printf("Register does not found");

                        dataIndex++;
                    }
                    else
                    {
                        value = atoi(regist);
                        data[dataIndex] = PUSH;
                        dataIndex++;
                        data[dataIndex] = value;
                        dataIndex++;
                    }
                }

                if (!strcmp(command, "POPr"))
                {
                    if (sscanf(index[i], "%*s %s", regist) <= 0)
                        break;

                    data[dataIndex] = POPr;
                    dataIndex++;

                    if (!strcmp(regist, "AX"))
                        data[dataIndex] = AX;
                    else if (!strcmp(regist, "BX"))
                        data[dataIndex] = BX;
                    else if (!strcmp(regist, "CX"))
                        data[dataIndex] = CX;
                    else if (!strcmp(regist, "DX"))
                        data[dataIndex] = DX;
                    else
                        printf("Register does not found");

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

            case 'M':

                if (!strcmp(command, "MUL"))
                {
                    data[dataIndex] = MUL;
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

            case 'J':

                if (!strcmp(command, "JMP"))
                {
                    if (sscanf(index[i], "%*s %d", &value) <= 0)
                        break;
                    data[dataIndex] = JMP;
                    dataIndex++;
                    data[dataIndex] = value;
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

