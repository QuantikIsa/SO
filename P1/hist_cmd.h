#ifndef HIST_CMD_H
#define HIST_CMD_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LNULL NULL
#define MAX 4096


typedef char tItemL[MAX];

typedef struct tNode {
    tItemL comando;
    struct tNode *next;
} tNode;

typedef tNode* tPosL;

typedef struct {
    int total;
    tPosL start;
} tList;


/*
void createEmptyList(tList *L);
bool isEmptyList(tList L);
tPosL first(tList L);
tPosL last(tList L);
tPosL next(tPosL posicion);
bool insertItem(tItemL comando, tList *L);
void deleteList(tList *L);
*/


void HList_show_all();
char*  HList_show_n(int n);
void HList_show_last_n(int n);
int HList_total();
void HList_add();
void HList_delete();    
void HList_init();



#endif 