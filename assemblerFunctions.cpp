#include "commands.h"
#include "stack.h"
#include "assembler.h"

returnValue fileProc(fileInfoStruc_t *fileToReadInfo)
{
    struct stat fileInfo;
    if (stat(fileToReadInfo->name, &fileInfo) == -1)
        return INTERPRETER_ERROR;

    if ((fileToReadInfo->buffer = (char *)(calloc(fileInfo.st_size + 1, sizeof(char)))) == NULL)
        return INTERPRETER_ERROR;

    if (fileOpening(&(fileToReadInfo->filePointer), fileToReadInfo->name, "r") == 1)
        return INTERPRETER_ERROR;

    int realCount = fread(fileToReadInfo->buffer, sizeof(char), fileInfo.st_size, fileToReadInfo->filePointer);

    fileToReadInfo->buffer[realCount] = '\0';

    char *pointer = fileToReadInfo->buffer;

    while ((pointer = strchr(pointer, '\n')) != NULL)
    {
        fileToReadInfo->numberOfLines++;
        pointer += 1;
    }

    pointer = fileToReadInfo->buffer;

    if ((fileToReadInfo->individualLines = (char **)calloc(fileToReadInfo->numberOfLines, sizeof(char *))) == NULL)
        return INTERPRETER_ERROR;

    int i = 1;
    fileToReadInfo->individualLines[0] = pointer;
    while ((pointer = strchr(pointer, '\n')) != NULL && i < fileToReadInfo->numberOfLines)
    {
        *pointer = '\0';
        pointer += 1;
        fileToReadInfo->individualLines[i] = pointer;
        i++;
    }

    if (closeFile(&(fileToReadInfo->filePointer)) == 1)
        return INTERPRETER_ERROR;

    return INTERPRETER_CORRECT;
}

// returnValue choseRegister(char *regist, int **data, int *dataIndex)
// {printf("11\n");
//     if (!strcmp(regist, "AX"))
//         *(data[*dataIndex]) = AX;
//     else if (!strcmp(regist, "BX"))
//     {printf("12\n");
//     printf("%p|||\n", *(data)[*dataIndex]);
//         *(data)[*dataIndex] = BX;
// printf("13\n");
//     }
//     else if (!strcmp(regist, "CX"))
//         *(data)[*dataIndex] = CX;
//     else if (!strcmp(regist, "DX"))
//         *(data[*dataIndex]) = DX;
//     else
//     {
//         printf("Register does not found");
//
//         return INTERPRETER_ERROR;
//     }
//
//     return INTERPRETER_CORRECT;
// }
