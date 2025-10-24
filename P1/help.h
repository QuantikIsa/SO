#ifndef HELP_H
#define HELP_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "hist_cmd.h"


struct CMD_help {
    char *name;
    void (*func)();
};


void Cmd_help (char *tr[]);
// P0
void Help_authors();
void Help_getpid();
void Help_chdir();
void Help_getcwd();
void Help_date();
void Help_hour();
void Help_historic();
void Help_open();
void Help_close();
void Help_dup();
void Help_listopen();
void Help_infosys();
void Help_help();
void Help_quit();
void Help_exit();
void Help_bye();
// P1
void Help_create();
void Help_setdirparams();
void Help_getdirparams();
void Help_dir();
void Help_erase();
void Help_delrec();
void Help_lseek();
void Help_writestr();

#endif