#include "help.h"


struct CMD_help H[]={
    //P0
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
    //P1
    {"create", Help_create},
    {"setdirparams", Help_setdirparams},
    {"getdirparams", Help_getdirparams},
    {"dir", Help_dir},
    {"erase", Help_erase},
    {"delrec", Help_delrec},
    {"lseek", Help_lseek},
    {"writestr", Help_writestr},

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

//P1

void Help_create(){
    printf("\tSINTAXIS: create [-f] nam\n");
    printf("\tUSE: Creates a new file or a new directory\n");
    printf("\tOPTIONS:\n\t· create -f nam: Creates a new file of name nam\n\t· create nam: Creates a new directory of name nam\n");
}

void Help_setdirparams(){
    printf("\tSINTAXIS: setdirparams [long|short] [link|nolink] [hid|nohid] [reca|recb|norec]\n");
    printf("\tUSE: Stablishes parameters for listing with dir\n");
    printf("\tOPTIONS:\n\t· setdirparams [long|short]: Stablishes parameters for listing with dir: long or short format\n\t"
            "· setdirparams [link|nolink]: Stablishes parameters for listing with dir: list (or not) symbolic link destination\n\t"
            "· setdirparams [hid|nohid]:   Stablishes parameters for listing with dir: list or omit hidden files\n\t"
            "· setdirparams [reca|recb|norec]: Stablishes parameters for listing with dir: recurse directories (after), recurse directories (before) or do not recurse\n");
}

void Help_getdirparams(){
    printf("\tSINTAXIS: getdirparams\n");
    printf("\tUSE: Shows de value of the parameters for listing with dir\n");
}

void Help_dir(){
    printf("\tSINTAXIS: dir [-d] n1, n2, n3...\n");
    printf("\tUSE: Shows information for files/dirs\n");
    printf("\tOPTIONS:\n\t· dir n1, n2, n3... : Shows information for files/dirs n1, n2, n3..... Depending on the parameters long|short does a short (just name and size) or long listing.\n\t"
            "The parameter link|nolink decides whether the link (in case of symbolic links) is printed or not.\n\t"
            "· dir -d n1, n2, n3... :  The same as dir, but in the case en of the names n1, n2 ...is a directory, ITS CONTENTS are listed.\n\t"
            "Besides the parameters long|short and link|nolink we can use hid|nohid to list hidden files inside the directories reca|recb|norec to make directory listing recursive\n");
}

void Help_erase(){
    printf("\tSINTAXIS: erase n1, n2, n3...\n");
    printf("\tUSE: Deletes files and/or empty directories, named n1, n2, n3 ...\n");
}

void Help_delrec(){
    printf("\tSINTAXIS: delrec n1, n2, n3...\n");
    printf("\tUSE: Deletes files and/or non empty directories (recursively) named n1, n2, n3...\n");
}

void Help_lseek(){
    printf("\tSINTAXIS: lseek [df|off|ref]\n");
    printf("\tUSE: Indicates the positions of the offset in an open file\n");
    printf("\tOPTIONS:\n\t· df: File descriptor for the open file\n\t"
            "· off: New offset\n\t"
            "· ref: Reference, SEEK_SET (offset is from the beginning), SEEK_CUR (offset is from the current position), SEEK_END (offset is from the end)\n");
}

void Help_writestr(){
    printf("\tSINTAXIS: writestr df str\n");
    printf("\tUSE: Write the string str in the open file with descriptor df\n");
}

