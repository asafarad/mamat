#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_ {
    struct elem* next;
    PElem pElem;
} Node;

typedef struct List_
{
    int size;
    Node *head;

    /*User functions*/
    CloneElem elem_cln;
    ListCompare list_cmp;
    ListPrint list_prt;
    ListRmv list_rmv;
} List;

/*Interface functions*/
PList ListCreate(CloneElem elem_cln, ListRmv list_rmv, ListCompare list_cmp, ListPrint list_prt) {
    PList newList;
    newList = (PList)malloc(sizeof(List));
    if (newList == NULL)
        return NULL;
    
    //Constructor:
    newList->head = NULL;
    newList->size = 0;
    newList->elem_cln = elem_cln;
    newList->list_rmv = list_rmv;
    newList->list_cmp = list_cmp;
    newList->list_prt = list_prt;
    return newList;
}

void ListDestory(PList pList) {
    

    while (PartyList != NULL) {
        CurrParty = PartyList;
        PartyList = PartyList->pNext;
        free(CurrParty);
    }

    Node* currNode = NULL;
    Node* node = pList->head;
    while (node != NULL){
        currNode = node;
        node = node->next;
        list_rmv(pList, currNode->pElem)
        
    }

}
Result ListAdd(PList pList, PElem pElem);
Result ListRemove(PList pList, PElem pElem);
PElem ListGetFirst(PList pList);
PElem ListGetNext(PList pList);