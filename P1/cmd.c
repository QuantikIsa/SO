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

void Cmd_create (char *tr[]){
    if(tr[0]==NULL) printf("Faltan argumentos");
    
    else if (!strcmp(tr[0],"-f")){
        if(tr[1]==NULL) printf("Falta el nombre del archivo\n");
        else{
            if (open(tr[1],O_CREAT, 0775)==-1)
                perror ("Imposible abrir fichero\n");
        }
    }
    else{
        if (mkdir(tr[0], 0775)==-1)
            perror ("Imposible abrir fichero\n");
            
                
    }
    

}

void Cmd_setdirparams (char *tr[]){
    if(tr[0]==NULL) printf("Faltan parámetros\n");
    else if(!strcmp(tr[0], "long")) longitud = LONG;
    else if(!strcmp(tr[0], "short")) longitud = SHORT;
    else if(!strcmp(tr[0], "link")) linkeado = LINK;
    else if(!strcmp(tr[0], "nolink")) linkeado = NOLINK;
    else if(!strcmp(tr[0], "hid")) oculto = HID;
    else if(!strcmp(tr[0], "nohid")) oculto = NOHID;
    else if(!strcmp(tr[0], "reca")) rec = RECA;
    else if(!strcmp(tr[0], "recb")) rec = RECB;
    else if(!strcmp(tr[0], "norec")) rec = NOREC;
    else printf ("Parametro no valido\n");

}

void Cmd_getdirparams (){
    char *recstr;
    if (rec==RECA) recstr = "recursivo (despues)";
    else if (rec==RECB) recstr = "recursivo (antes)";
    else recstr = "no recursivo";
    printf("Listado: %s %s %s %s\n", longitud?"corto":"largo", linkeado?"sin links": "con links", recstr, oculto?"":"con fichero ocultos");
}

char LetraTF (mode_t m){
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */ 
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }
}

char * ConvierteModo (mode_t m, char *permisos){
    strcpy (permisos,"---------- ");
    
    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';  // Es rarito 
    
    return permisos;
}

int esDirectorio (char * dir){
    struct stat s;
    if (lstat(dir,&s)==-1)    
            return 0;
    return (S_ISDIR(s.st_mode));
}


void print_info(char *path){
    struct stat s;
    char permisos[MAX];
    char fecha[MAX];
    struct tm *tm_info;
    struct passwd *pw;
    struct group *gr;

    if(lstat(path, &s) == -1) {
        perror(path);
        return;
    }

    char *nombre = strrchr(path, '/');
    if (nombre) nombre++;
    else nombre = path;

    if(longitud==LONG){
        
        ConvierteModo(s.st_mode, permisos);

        tm_info = localtime(&s.st_mtime);
        strftime(fecha, sizeof(fecha), "%Y/%m/%d-%H:%M", tm_info);

        pw = getpwuid(s.st_uid);
        gr = getgrgid(s.st_gid);

        printf("%s   %lu (%6lu)   %-8s %-8s %s %6lld %s\n",
            fecha,
            (unsigned long)s.st_nlink,
            (unsigned long)s.st_ino,
            pw ? pw->pw_name : "???",
            gr ? gr->gr_name : "???",
            permisos,
            (long long)s.st_size,
            nombre);
    }
    else{
        printf("  %6ld  %s\n", s.st_size, nombre);
    }

}

void list_dir(char *dir){
    DIR *d = opendir(dir);
    if(!d){
        perror(dir);   
        return;
    }
    
    struct dirent *entry;
    char path[MAX];

    printf("************%s\n", dir);

    // Primera pasada: listar contenido
    while ((entry = readdir(d)) != NULL) {
        // Ignorar . y .. siempre
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // FILTRO DE ARCHIVOS OCULTOS
        if (oculto == NOHID && entry->d_name[0] == '.')
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

        // FILTRO DE ENLACES
        if (linkeado == NOLINK) {
            struct stat s_tmp;
            if (lstat(path, &s_tmp) != -1 && S_ISLNK(s_tmp.st_mode))
                continue; // saltar links si no se quieren mostrar
        }

        // Mostrar información usando print_info
        print_info(path);
    }

    // Segunda pasada para recursividad
    if (rec != NOREC) {
        rewinddir(d);

        while ((entry = readdir(d)) != NULL) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            // FILTRO OCULTOS también para recursión
            if (oculto == NOHID && entry->d_name[0] == '.')
                continue;

            snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

            if (esDirectorio(path)) {
                list_dir(path);
            }
        }
    }

    closedir(d);
}


void list_nodir (char *nodir){
    print_info(nodir);
}

void Cmd_dir (char *tr[]){
    if(tr[0]==NULL) printf("Faltan parametros\n"); //Estaría bien hacer que liste el actual
    else if(!strcmp(tr[0], "-d")){
        for (int i=1; tr[i]!=NULL;i++){
            if(esDirectorio(tr[i])) list_dir(tr[i]);
            else list_nodir(tr[i]);
        }
    }
    else 
        for (int i=0; tr[i]!=NULL;i++) list_nodir(tr[i]);
}

void Cmd_erase (char *tr[]){
    int i;

    if(tr[0]==NULL){
        printf("Faltan argumentos\n");
        return;
    } 
    for(i=0;tr[i]!=NULL;i++){
        if(remove(tr[i])==-1) perror("El directorio no está vacío");
        
    }
}


void erase_recursive(const char *path) {
    struct stat s;
    struct dirent *entry;
    char fullpath[1024];

    if (lstat(path, &s) == -1) {
        perror(path);
        return;
    }

    // Si es un archivo o link, lo borramos directamente
    if (!S_ISDIR(s.st_mode) || S_ISLNK(s.st_mode)) {
        if (remove(path) == -1) {
            perror(path);
        }
        return;
    }

    // Si es un directorio, abrimos y borramos su contenido recursivamente
    DIR *d = opendir(path);
    if (!d) {
        perror(path);
        return;
    }

    while ((entry = readdir(d)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        erase_recursive(fullpath);
    }

    closedir(d);

    // Finalmente borramos el directorio vacío
    if (rmdir(path) == -1) {
        perror(path);
    }
}

void Cmd_delrec (char *tr[]){
    if (tr[0] == NULL) {
        printf("Faltan argumentos\n");
        return;
    }

    for (int i = 0; tr[i] != NULL; i++) {
        erase_recursive(tr[i]);
    }

}

void Cmd_lseek(char *tr[]){
    int mode;
    if(tr[0]==NULL || tr[1]==NULL || tr[2]==NULL){
        printf("Faltan paramentros\n");
        return;
    }

    if (!strcmp(tr[2],"SEEK_SET")) mode=SEEK_SET;
    else if (!strcmp(tr[2],"SEEK_CUR")) mode=SEEK_CUR;
    else if (!strcmp(tr[2],"SEEK_END")) mode=SEEK_END; 


    if(lseek(atoi(tr[0]),atoi(tr[1]),mode)==-1) perror("Fallo");

}

void Cmd_writestr(char *tr[]){
    if(tr[0]==NULL || tr[1]==NULL){
        printf("Faltan parametros\n");
        return;
    }

    int df = atoi(tr[0]);

    if (write(df, tr[1], strlen(tr[1])) == -1)
        perror("Error al escribir");
    else
        printf("Escrito en fd=%d: \"%s\"\n", df, tr[1]);

}

