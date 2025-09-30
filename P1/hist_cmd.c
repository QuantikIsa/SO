#include "hist_cmd.h"

tList historic;

void createEmptyList(tList *L) {
    L->total = 0;
    L->start = LNULL;
}

bool isEmptyList(tList L) {
    return (L.start = LNULL);
}

tPosL first(tList L){ 
    return L.start; 
}

tPosL last(tList L){ 
    tPosL p = L.start;
    if(p == LNULL) return LNULL;
    while(p->next != LNULL) p = p->next;
    return p;
}

tPosL next(tPosL p){ 
    return p->next;
}

bool createNode(tPosL *p){
    *p = malloc(sizeof(**p));
    return *p != LNULL;
}

bool insertItem(tItemL comando, tList *L) {
    tPosL q;
    if(!createNode(&q)) return false;

    strcpy(q->comando, comando);
    q->next = NULL;

    if (L->start == NULL) {
        L->start = q;
    } else {
        tPosL r = L->start;
        while (r->next != NULL) r = r->next;
        r->next = q;
    }
    L->total++;  
    return true;
}

void deleteList(tList *L){
    tPosL p;
    while (L->start != LNULL) {
        p = L->start;
        L->start = L->start->next;
        free(p);
    }
    L->total = 0;
}





void HList_show_all() {
    if (isEmptyList(historic)) printf("Historial vacío.\n");
    int i = 1;
    for (tPosL p = historic.start; p != LNULL; p = p->next) {
        printf("%d. %s", i++, p->comando);
    }
}

char* HList_show_n(int n) {
    if (n <= 0 || n > historic.total) {
        printf("No existe el comando número %d\n", n);
        return NULL;   // <- Muy importante
    }
    int i = 1;
    tPosL p = historic.start;
    while (p != NULL && i < n) {
        p = p->next;
        i++;
    }
    printf("%d. %s", i, p->comando);
    return p->comando;   // Devuelves el puntero al comando
}


void HList_show_last_n(int n) {
    if (isEmptyList(historic)) {
        printf("Historial vacio\n");
        return;
    }
    if (n <= 0 || n > historic.total) {
        printf("No existen %d comandos\n", n);
        return;
    }
    int j = historic.total - n + 1;
    int i = 1;
    for (tPosL p = historic.start; p != LNULL; p = p->next) {
        if (i >= j) printf("%d. %s", i, p->comando);
        i++;
    }
}

int HList_total() {
    return historic.total;
}

void HList_add(char *command) {
    insertItem(command, &historic);
}

void HList_delete(){
    deleteList(&historic);
}

void HList_init(){
    createEmptyList(&historic);
}