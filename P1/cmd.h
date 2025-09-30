#ifndef CMD_H
#define CMD_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>


#include "help.h"
#include "files.h"

#define MAX 4096


/* Tabla de comandos */
struct CMD {
    char *name;
    void (*func)(char **);
};

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

void procesarEntrada(char *command);

#endif
