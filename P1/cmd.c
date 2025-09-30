#include "cmd.h"

void Cmd_authors (char *tr[]){
    if(tr[0]==NULL) 
        printf("Nuria García García: n.ggarcia@udc.es\nIsabel Villar García: i.villar@udc.es\n");
    else if (strcmp(tr[0],"-l")==0) 
        printf("n.ggarcia@udc.es\ni.villar@udc.es\n");
    else if (strcmp(tr[0],"-n")==0) 
        printf("Nuria García García\nIsabel Villar García\n");
    else 
        printf("Comando inválido\n");
}

void Cmd_getpid (char *tr[]){
    int pid;
    if(tr[0]==NULL){
        pid = getpid();
        printf("Pid del shell: %d\n", pid);
    } 
    else if (strcmp(tr[0],"-p")==0){
        pid = getppid();
        printf("Pid del padre del shell: %d\n", pid);
    } 
    else 
        printf("Comando inválido\n");
}

void Cmd_getcwd (char *tr[]){
    char dir[MAX];

    if (getcwd(dir, MAX) == NULL) {
        perror("error");
        return;
    }

    if (tr[0] == NULL) {
        printf("%s\n", dir);
    } 
    else
        perror("error");
}

void Cmd_chdir (char *tr[]){
    if(tr[0]==NULL) Cmd_getcwd(tr);
    else{
        if(chdir(tr[0])==0) printf("%s\n", tr[0]);
        else perror(NULL);
    }
}

void Cmd_date (char *tr[]){
    time_t t;
    struct tm *tm_info;
    char hour[MAX];
    char date[MAX];

    time(&t);
    tm_info = localtime(&t);

    if(tm_info == NULL) perror("error");

    strftime(hour, sizeof(hour), "%H:%M:%S", tm_info);
    strftime(date, sizeof(date), "%d/%m/%Y", tm_info);
    if(tr[0]==NULL)
        printf("%s\n%s\n", hour, date);
    else if(!strcmp(tr[0],"-d"))
        printf("%s\n", date);
    else if(!strcmp(tr[0],"-t"))
        printf("%s\n", hour);
    else 
        perror("error");
}

void Cmd_hour (char *tr[]){
    time_t t;
    struct tm *tm_info;
    char hour[MAX];

    time(&t);
    tm_info = localtime(&t);

    if(tm_info == NULL) perror("error");

    strftime(hour, sizeof(hour), "%H:%M:%S", tm_info);

    if(tr[0]==NULL) printf("%s\n", hour);
    else perror("error");
}

void Cmd_historic (char *tr[]){
    int ncommand;
    char *command;
    
    if(tr[0]==NULL)
        HList_show_all();
    else if (!strcmp(tr[0],"-count")){
        ncommand = HList_total();
        printf("Numero de elementos en el historico: %d\n", ncommand);
    }
    else if (!strcmp(tr[0],"-clear"))
        HList_delete();    
    else{
        ncommand = atoi(tr[0]);
        if(ncommand > 0){
            command = HList_show_n(ncommand);
            if (command != NULL) {
                procesarEntrada(command);
            } else {
                printf("No existe el comando número %d en el histórico.\n", ncommand);
            }
        }
        else if (ncommand < 0){
            HList_show_last_n(-ncommand);
        } 
    }
}

void Cmd_open (char *tr[]){
    int i, df, mode=0;
    char *aux;
    char mode_c[MAX];
    if(tr[0]==NULL){
        Files_show();
        return;
    }
    strcpy(mode_c,"");
    for (i=1; tr[i]!=NULL; i++){
        aux = Files_mode(tr[i]);
        strcat(mode_c, aux);
    }

    for (i=1; tr[i]!=NULL; i++)
      if (!strcmp(tr[i],"cr")) mode|=O_CREAT;
      else if (!strcmp(tr[i],"ex")) mode|=O_EXCL;
      else if (!strcmp(tr[i],"ro")) mode|=O_RDONLY; 
      else if (!strcmp(tr[i],"wo")) mode|=O_WRONLY;
      else if (!strcmp(tr[i],"rw")) mode|=O_RDWR;
      else if (!strcmp(tr[i],"ap")) mode|=O_APPEND;
      else if (!strcmp(tr[i],"tr")) mode|=O_TRUNC; 
      else break;
    
      
      
    if ((df=open(tr[0],mode,0777))==-1)
        perror ("Imposible abrir fichero");
    else{
        Files_add(df, tr[0], mode_c, mode);
        printf ("Anadida entrada %d a la tabla ficheros abiertos\n",df);

    }
}


void Cmd_close (char *tr[]){
    int df;
    
    if (tr[0]==NULL || (df=atoi(tr[0]))<0) { 
        Files_show();
        return;
    }
    
    if (close(df)==-1)
        perror("Imposible cerrar descriptor");
    else
       Files_delete(df);
}

void Cmd_dup (char *tr[]){
    int df, duplicado, flags;
    char aux[MAX],*p;
    char mode_c[MAX];
    
    if (tr[0]==NULL || (df=atoi(tr[0]))<0) { /*no hay parametro*/
        Files_show();        /*o el descriptor es menor que 0*/
        return;
    }
    
    p = Files_name(df);
    sprintf (aux,"dup %d (%s)",df, p);
    strcpy(mode_c, Files_m(df));

    duplicado = dup(df);
    if(duplicado==-1){
        perror("dup");
        return;
    }

    flags = fcntl(duplicado,F_GETFL);

    Files_add(duplicado, aux, mode_c, flags);
}

void Cmd_listopen (char *tr[]){
    if(tr[0]==NULL)
        Files_show();
    else 
        printf("Argumentos inválidos");
}

void Cmd_infosys (char *tr[]){
    struct utsname info;
    if(tr[0]==NULL){
        if (uname(&info)==0)
            printf("%s (%s), OS: %s-%s-%s\n", info.nodename, info.machine, info.sysname, info.release, info.version);
        else
            perror(NULL);
    }
    else printf("Argumentos inválidos\n");
}

void Cmd_quit (){
    exit(0);
}

void Cmd_exit (){
    exit(0);
}

void Cmd_bye (){
    exit(0);
}
