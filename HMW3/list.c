/*

  File: list.c

  Abstract:

    List handling implementation

*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Types*/
typedef struct node_* PNode;
typedef struct node_ {
    PElem pElem; //pointer to abstract element
    PNode next; //next node
} Node;


typedef struct List_
{
    int size; //size of list
    PNode head;
    PNode tail;
    PNode iter; //inner iterator to get the elements

    /*User functions*/
    CloneElem elem_cln; //function for clone element
    ElemCompare elem_cmp; //function for compare element
    ElemPrint elem_prt; //function for print element
    ElemRemove elem_rmv; //function for remove element
} List;



/*Interface functions*/

/*
  Function Name	:	ListCreate
  Description	:	Allocate a new empty list with pointers to the user functions.
  Parameters	:	elem_cln	- Pointer to user function clone element.
                    elem_rmv    - Pointer to user function remove element.
                    elem_cmp    - Pointer to user function compare element.
                    elem_prt    - Pointer to user function print element.
  Return Value	:	Pointer to a new empty list ADT. return NULL if allocate failed.
  */
PList ListCreate(CloneElem elem_cln, ElemRemove elem_rmv, ElemCompare elem_cmp, ElemPrint elem_prt) {
    // input legal check
    if ((elem_cln == NULL) || (elem_rmv == NULL) || (elem_cmp == NULL) || (elem_prt == NULL))
        return NULL;
    PList newList;
    newList = (PList)malloc(sizeof(List));
    if (newList == NULL)
        return NULL;

    
    //Constructor: initlize empty list
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    newList->iter = newList->head;
    //take the pointers to the compatible functions
    newList->elem_cln = elem_cln;
    newList->elem_rmv = elem_rmv;
    newList->elem_cmp = elem_cmp;
    newList->elem_prt = elem_prt;
    return newList;
}

void ListDestroy(PList pList) {
    if (pList == NULL)
        return;
    PNode currNode = NULL;
    PNode node = pList->head;
    while (node != NULL){
        currNode = node;
        node = node->next;
        pList->elem_rmv(currNode->pElem);
        free(currNode);
    }
    free(pList);

}
Result ListAdd(PList pList, PElem pElem) {
    if (pList == NULL || pElem == NULL)
        return FAIL;

    PElem newElem = pList->elem_cln(pElem);
    if (newElem == NULL)
        return FAIL;
    PNode newNode;
    newNode = (PNode)malloc(sizeof(Node));
    if (newNode == NULL)
        return FAIL;
    
    newNode->pElem = newElem;
    newNode->next = NULL;
    //Advance the last "next" in the list to point at the newNode
    if (pList->size == 0) {
        pList->head = newNode;
        pList->tail = pList->head;
    }
    else {
        pList->tail->next = newNode;
        pList->tail = newNode;
    }
    pList->size++;
    return SUCCESS;
}
Result ListRemove(PList pList, PElem pElem) {

    if (pList == NULL || pElem == NULL)
        return FAIL;
    PNode node = pList->head;
    PNode prevNode = NULL;
    while (node != NULL) {
        if (pList->elem_cmp(pElem, node->pElem) == TRUE) {

            if (node == pList->head) {
                pList->head = node->next;
                pList->elem_rmv(node->pElem);
                free(node);
                pList->size--;
                return SUCCESS;
            }
            else {
                prevNode->next = node->next;
                if (node == pList->tail)
                    pList->tail = prevNode;
                pList->elem_rmv(node->pElem);
                free(node);
                pList->size--;
                return SUCCESS;
            }
        }
        prevNode = node;
        node = node->next;
    }
    return FAIL;
}
PElem ListGetFirst(PList pList) {
    if (pList == NULL)
        return NULL;
    pList->iter = pList->head;
    if (pList->iter == NULL)
        return NULL;
    return pList->iter->pElem;
}
PElem ListGetNext(PList pList) {
    if (pList == NULL || pList->iter == NULL || pList->iter->next == NULL )
        return NULL;
    pList->iter = pList->iter->next;
    return pList->iter->pElem;
}

BOOL ListCompare(PList pList1, PList pList2) {
    if (pList1 == NULL || pList2 == NULL)
        return FALSE;
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
    if (pList == NULL)
        return;
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