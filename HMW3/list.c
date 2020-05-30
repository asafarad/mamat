#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_ {
    struct node_* next;
    PElem pElem;
} Node;

/*
typedef struct iter_ {
    Node* 
    
} iter;
*/

typedef struct List_
{
    int size;
    Node *head;
    Node *tail;
    Node *iter;

    /*User functions*/
    CloneElem elem_cln;
    ElemCompare elem_cmp;
    ElemPrint elem_prt;
    ElemRemove elem_rmv;
} List;



/*Interface functions*/
PList ListCreate(CloneElem elem_cln, ElemRemove elem_rmv, ElemCompare elem_cmp, ElemPrint elem_prt) {
    PList newList;
    if ((elem_cln == NULL) || (elem_rmv == NULL) || (elem_cmp == NULL) || (elem_prt == NULL))
        return NULL;
    newList = (PList)malloc(sizeof(List));
    if (newList == NULL)
        return NULL;

    
    //Constructor:
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    newList->elem_cln = elem_cln;
    newList->elem_rmv = elem_rmv;
    newList->elem_cmp = elem_cmp;
    newList->elem_prt = elem_prt;
    newList->iter = newList->head;
    return newList;
}

void ListDestroy(PList pList) {

    Node* currNode = NULL;
    Node* node = pList->head;
    while (node != NULL){
        currNode = node;
        node = node->next;
        pList->elem_rmv(currNode->pElem);
        free(currNode);
    }
    free(pList);

}
Result ListAdd(PList pList, PElem pElem) {
    Node* newNode;
    newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL)
        return FAIL;
    PElem newElem = pList->elem_cln(pElem);
    newNode->pElem = newElem;
    newNode->next = NULL;
    //Advance the last "next" in the list to point at the newNode
    pList->tail = newNode;
    pList->size++;
    return SUCCESS;
}
Result ListRemove(PList pList, PElem pElem) {

    Node* node = pList->head;
    Node* prevNode = NULL;
    while (node != NULL) {
        if (pList->elem_cmp(pElem, node->pElem)) {

            if (node == pList->head) {
                pList->head = node->next;
                pList->elem_rmv(node->pElem);
                free(node);
                return SUCCESS;
            }
            else {
                prevNode->next = node->next;
                pList->elem_rmv(node->pElem);
                free(node);
                return SUCCESS;
            }
        }
        prevNode = node;
        node = node->next;
        pList->size--;
    }
    return FAIL;
}
PElem ListGetFirst(PList pList) {
    pList->iter = pList->head;
    return pList->iter->pElem;
}
PElem ListGetNext(PList pList) {
    if ((pList->iter == NULL) || (pList->iter->next == NULL ))
        return NULL;
    pList->iter = pList->iter->next;
    return pList->iter->pElem;
}

BOOL ListCompare(PList pList1, PList pList2) {
    PElem currElem1 = ListGetFirst(pList1);
    PElem currElem2 = ListGetFirst(pList2);
    while (currElem1 != NULL && currElem2 != NULL) {
        if (pList1->elem_cmp(currElem1, currElem2) == FALSE)
            return FALSE;
        currElem1 = ListGetNext(pList1);
        currElem2 = ListGetNext(pList2);
    }
    if ((currElem1 == NULL && currElem2 != NULL) || (currElem2 == NULL && currElem1 != NULL))
        return FALSE;

    return TRUE;
}

void ListPrint(PList pList) {

    PElem currElem = ListGetFirst(pList);
    printf("[");
    while (currElem != NULL) {
        pList->elem_prt(currElem);
        currElem = ListGetNext(pList);
    }

    printf("]\n");

}
int ListGetSize(PList pList) {
    return pList->size;
}