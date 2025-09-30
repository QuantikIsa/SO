#include "help.h"


struct CMD_help H[]={
    {"authors", Help_authors},
    {"getpid", Help_getpid},
    {"chdir", Help_chdir},
    {"getcwd", Help_getcwd},
    {"date", Help_date},
    {"hour", Help_hour},
    {"historic", Help_historic},
    {"open", Help_open},
    {"close", Help_close},
    {"dup", Help_dup},
    {"listopen", Help_listopen},
    {"infosys", Help_infosys},
    {"help", Help_help},
    {"quit", Help_quit},
    {"exit", Help_exit},
    {"bye", Help_bye},
    {NULL, NULL}
};


void Cmd_help (char *tr[]){
    int i;
    if(tr[0]==NULL){
        printf("'help [cmd|-lt|-T topic|-all]' ayuda sobre comandos\n\t\tComandos disponibles:\n");
        //bucle para imprimir todos seguidos con espacio
        for (i = 0; H[i].name != NULL; i++) {
                printf("%s\n", H[i].name);
        }
    }
    else{
        for (i = 0; H[i].name != NULL; i++) {
            if (strcmp(tr[0], H[i].name) == 0) {
                (*H[i].func)(tr+1);
                return;
            }
        }
        printf("Comando no encontrado\n");
    }
}

void Help_authors(){
    printf("\tSINTAXIS: authors [-n|-l]\n");
    printf("\tUSE: Prints the names and logins of the program authors\n");
    printf("\tOPTIONS:\n\t· authors -l: Prints only the logins\n\t· authors -n: Prints only the names\n");
}

void Help_getpid(){
    printf("\tSINTAXIS: getpid [-p]\n");
    printf("\tUSE: Prints the pid of the process executing the shell\n");
    printf("\tOPTIONS:\n\t· getpid -p Prints the pid of the shell’s parent process\n");
}

void Help_chdir(){
    printf("\tSINTAXIS: chdir [dir]\n");
    printf("\tUSE: Changes the current working directory of the shell to dir. When invoked without auguments it prints the current working directory\n");
}

void Help_getcwd(){
    printf("\tSINTAXIS: getcwd\n");
    printf("\tUSE: Prints the current working directory of the shell\n");
}

void Help_date(){
    printf("\tSINTAXIS:date [-d|-t]\n");
    printf("\tUSE: Prints the current date in the format DD/MM/YYYY and the current time in the format hh:mm:ss\n");
    printf("\tOPTIONS:\n\t· date -d: Prints the current date in the format DD/MM/YYYY\n\t· date: -t Prints the current time in the format hh:mm:ss  \n");
}

void Help_hour(){
    printf("\tSINTAXIS: hour\n");
    printf("\tUSE: Prints the current time in the format hh:mm:ss\n");
}

void Help_historic(){
    printf("\tSINTAXIS: historic [-clear|-count|-N|N]\n");
    printf("\tUSE: Shows the historic of commands executed by this shell\n");
    printf("\tOPTIONS:\n\t· historic  N: Repeats command number N (from historic list)\n\t· historic -N: Prints only the lastN comands\n\t· historic -clear: Clear the historic list or report its number of elements\n\t· historic -count: Reports how many commands there are on the historic list\n");
}

void Help_open(){
    printf("\tSINTAXIS: open fich m1 m2...\n");
    printf("\tUSE: Opens a file and adds it to the list of shell open files\n\tOpen without arguments lists the shell open files. \n\tFor each file it lists its descriptor, the file name and the opening mode:\n");
    printf("\tcr: O_CREAT\n\tap: O_APPEND\n\tex: O_EXCL\n\tro: O_RDONLY\n\trw: O_RDWR\n\two: O_WRONLY\n\ttr: O_TRUNC\n");
}

void Help_close(){
    printf("\tSINTAXIS: close df\n");
    printf("\tUSE: Closes the df file descriptor and eliminates the corresponding item from the list\n");
}

void Help_dup(){
    printf("\tSINTAXIS: dup df\n");
    printf("\tUSE: Duplicates the df file descriptor\n");
}

void Help_listopen(){
    printf("\tSINTAXIS: listopen [n]\n");
    printf("\tUSE: Lists the shell open files (At least n)\n");
}

void Help_infosys(){
    printf("\tSINTAXIS: infosys\n");
    printf("\tUSE: Prints information on the machine running the shell\n");
}

void Help_help(){
    printf("\tSINTAXIS: help [cmd]\n");
    printf("\tUSE: Displays a list of available commands, help cmd gives a brief help on the usage of comand cmd\n");
}

void Help_quit(){
    printf("\tSINTAXIS: quit\n");
    printf("\tUSE: Ends the shell\n");
}

void Help_exit(){
    printf("\tSINTAXIS: exit\n");
    printf("\tUSE: Ends the shell\n");

}

void Help_bye(){
    printf("\tSINTAXIS: bye\n");
    printf("\tUSE: Ends the shell\n");
}

