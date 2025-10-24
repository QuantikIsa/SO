#ifndef CMD_H
#define CMD_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>



#include "help.h"
#include "files.h"

#define MAX 4096

enum LONGITUD{
    LONG,
    SHORT
};
enum LINKEADO{
    LINK,
    NOLINK
};
enum OCULTO{
    HID,
    NOHID
};
enum REC{
    RECA,
    RECB,
    NOREC
};

int longitud = SHORT;
int linkeado = NOLINK;
int oculto = NOHID;
int rec = NOREC;


/* Tabla de comandos */
struct CMD {
    char *name;
    void (*func)(char **);
};

//P0
void Cmd_authors (char *tr[]);
void Cmd_getpid (char *tr[]);
void Cmd_getcwd (char *tr[]);
void Cmd_chdir (char *tr[]);
void Cmd_date (char *tr[]);
void Cmd_hour (char *tr[]);
void Cmd_historic (char *tr[]);
void Cmd_open (char *tr[]);
void Cmd_close (char *tr[]);
void Cmd_dup (char *tr[]);
void Cmd_listopen (char *tr[]);
void Cmd_infosys (char *tr[]);
void Cmd_quit ();
void Cmd_exit ();
void Cmd_bye ();
//P1
void Cmd_create (char *tr[]);
void Cmd_setdirparams (char *tr[]);
void Cmd_getdirparams ();
void Cmd_dir (char *tr[]);
void Cmd_erase (char *tr[]);
void Cmd_delrec (char *tr[]);
void Cmd_lseek(char *tr[]);
void Cmd_writestr(char *tr[0]);


void procesarEntrada(char *command);

#endif
