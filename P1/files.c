#include "files.h"

FILES files[MAXF]; 
int n_openfiles = 0;

struct MODES M[]={
    {"cr","O_CREAT "},
    {"ap","O_APPEND "},
    {"ex","O_EXCL "},
    {"ro","O_RDONLY "},
    {"rw","O_RDWR "},
    {"wo","O_WRONLY "},
    {"tr","O_TRUNC "},
    {NULL, NULL}
};

char *Files_mode(char *mode_cmd){
    int i;
    for (i = 0; M[i].mode_cmd != NULL; i++) {
        if (!strcmp(mode_cmd, M[i].mode_cmd)) {
            return M[i].mode_name;
        }
    }
    return " ";
}

void Files_add(int desc, char *f, char *m, int flg){
    files[desc].df = desc;
    strcpy(files[desc].file, f);
    strcpy(files[desc].mode, m);
    files[desc].flag = flg;
    n_openfiles++;
}

void Files_delete(int desc){
    strcpy(files[desc].file, "");
    strcpy(files[desc].mode, "");
    files[desc].flag = -1;
    n_openfiles--;
}

char *Files_name(int desc){
    return files[desc].file;
}

char *Files_m(int desc){
    return files[desc].mode;
}

void Files_add_duplicate(int desc, char *f, char *m){
    files[desc].df = desc;
    strcpy(files[desc].file, f);
    strcpy(files[desc].mode, m);
    n_openfiles++;
}

void Files_show(){
    int i;
    for(i=0; i<MAXF; i++){
        if(strcmp(files[i].file,"")==0)
            printf("descriptor: %d, offset: (  )-> no usado\n", i);
        else
            printf("descriptor: %d, offset: ( )-> %s %s\n", files[i].df, files[i].file, files[i].mode);
            
    }
}

void Files_init(){
    files[0].df = 0;
    strcpy(files[0].file, "entrada estandar");
    strcpy(files[0].mode, "O_RDWR");
    files[0].flag = O_RDWR;

    files[1].df = 1;
    strcpy(files[1].file, "salida estandar");
    strcpy(files[1].mode, "O_RDWR");
    files[1].flag = O_RDWR;

    files[2].df = 2;
    strcpy(files[2].file, "error estandar");
    strcpy(files[2].mode, "O_RDWR");
    files[2].flag = O_RDWR;

    for(int i=3;i<MAXF;i++){
        strcpy(files[i].file, "");
        files[i].flag = -1;
    }
    n_openfiles = 3;
}

