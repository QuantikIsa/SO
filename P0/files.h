#ifndef HIST_CMD_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

#define LNULL NULL
#define MAX 4096
#define MAXF 20

typedef struct{
    int df;
    char file[MAX];
    char mode[MAX];
    int flag;
} FILES;

struct MODES{
    char *mode_cmd;
    char *mode_name;
};

char *Files_mode(char *tr);
void Files_add(int desc, char *file, char *m, int flg);
void Files_delete(int desc);
char *Files_name(int desc);
char *Files_m(int desc);
void Files_add_duplicate(int desc, char *f, char *m);
void Files_show();
void Files_init();

#endif