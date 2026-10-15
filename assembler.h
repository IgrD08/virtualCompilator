#ifndef ASSEMBLER_H
#define ASSEMBLER_H

struct fileInfoStruc_t
{
    char **individualLines;
    const char *name;
    FILE *filePointer;
    int numberOfLines;
    char *buffer;
};

returnValue fileProc(fileInfoStruc_t *fileToReadInfo);
returnValue choseRegister(char *regist, int **data, int *dataIndex);

#endif
