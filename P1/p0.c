/*
Nuria García García   login: n.ggarcia@udc.es
Isabel Villar García  login: i.villar@udc.es
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>
#include <errno.h>

#include "cmd.h"


#define MAX 4096

//Lista de comandos
struct CMD C[]={
    {"authors", Cmd_authors},
    {"getpid", Cmd_getpid},
    {"chdir", Cmd_chdir},
    {"getcwd", Cmd_getcwd},
    {"date", Cmd_date},
    {"hour", Cmd_hour},
    {"historic", Cmd_historic},
    {"open", Cmd_open},
    {"close", Cmd_close},
    {"dup", Cmd_dup},
    {"listopen", Cmd_listopen},
    {"infosys", Cmd_infosys},
    {"help", Cmd_help},  //La función se incluye en help.c
    {"quit", Cmd_quit},
    {"exit", Cmd_exit},
    {"bye", Cmd_bye},
    {NULL, NULL}
};


int TrocearCadena(char *cadena, char *tr[]){
    int i=1;
    if ((tr[0]=strtok(cadena," \n\t"))==NULL)
        return 0;
    while ((tr[i]=strtok(NULL," \n\t"))!=NULL)
        i++;
    return i;
}


void DoCommand (char *tr[]){
    int i;
    
    if(tr[0]==NULL) return; 

    for (i = 0; C[i].name != NULL; i++) {
        if (!strcmp(tr[0], C[i].name)) {
            (*C[i].func)(tr+1);
            return;
        }
    }
    printf("Comando inválido\n");
}

//Funciones del main

void imprimirPrompt(){
    printf("$ ");
}

void leerEntrada(char *command){
    fgets(command, MAX, stdin);
}


void procesarEntrada(char *command) {
    char *tr[MAX/2];

    HList_add(command);
    

    TrocearCadena(command, tr);

    

    DoCommand(tr); 
}



int main (){
    char command[MAX];

    Files_init();
    HList_init();

    while(true){
        imprimirPrompt();
        leerEntrada(command);
        procesarEntrada(command);
    }

}

