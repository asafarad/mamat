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

/*
  Function Name	:	ListDestroy
  Description	:	Delete the memory of the list ADT without leak.
  Parameters	:	pList    - Pointer to list ADT to be destroyed.
  Return Value	:	None.
  */
void ListDestroy(PList pList) {
    if (pList == NULL) // input legal check
        return;
    PNode currNode = NULL;
    PNode node = pList->head;
    // iterate all the list nodes
    while (node != NULL){
        currNode = node; // save the current node for no leaks
        node = node->next;
        pList->elem_rmv(currNode->pElem); // remove with user function the element in node
        free(currNode); // remove the whole node struct
    }
    free(pList); // remove the whole list

}

/*
  Function Name	:	ListAdd
  Description	:	Add a new element to the list.
  Parameters	:	pList	- Pointer to list ADT.
                    pElem	- Pointer to new element to be added in the same struct as the list elments.
  Return Value	:	Result- SUUCCES if element added to the list. FAIL if element not added.
  */
Result ListAdd(PList pList, PElem pElem) {
    //input legal check
    if (pList == NULL || pElem == NULL)
        return FAIL;

    PElem newElem = pList->elem_cln(pElem); //clone the new element by user function
    if (newElem == NULL)
        return FAIL;
    PNode newNode;
    newNode = (PNode)malloc(sizeof(Node)); //allocate a node to the element
    if (newNode == NULL)
        return FAIL;
    //update the new node
    newNode->pElem = newElem;
    newNode->next = NULL;
    //update the tail in the list to point at the newNode
    if (pList->size == 0) { // if the list is empty, update both head tand tail
        pList->head = newNode;
        pList->tail = pList->head;
    }
    else { // list isn't empty, update the tail
        pList->tail->next = newNode;
        pList->tail = newNode;
    }
    pList->size++; //increase size of list
    return SUCCESS;
}

/*
  Function Name	:	ListRemove
  Description	:	Remove an element from the list.
  Parameters	:	pList	- Pointer to list ADT.
                    pElem	- Pointer to element to be deleted from list.
  Return Value	:	Result- SUUCCES if element deleted from the list. FAIL if not deleted.
  */
Result ListRemove(PList pList, PElem pElem) {
    //input legal check
    if (pList == NULL || pElem == NULL)
        return FAIL;
    PNode node = pList->head;
    PNode prevNode = NULL;
    //iterate all list nodes and find the node to delete
    while (node != NULL) {
        //find the node by compare element user function
        if (pList->elem_cmp(pElem, node->pElem) == TRUE) {
            if (node == pList->head) { //if the node to delete is the head of list
                pList->head = node->next; //update head
                pList->elem_rmv(node->pElem); //remove element by user function
                free(node); // free the node itself
                pList->size--; //decrease size of list
                return SUCCESS;
            }
            else { //if the node isnt the first node
                prevNode->next = node->next; //update its previous node
                if (node == pList->tail) // if the node to delete is the tail of list
                    pList->tail = prevNode;
                pList->elem_rmv(node->pElem); // remove element by user function
                free(node); // free node itself
                pList->size--; //decrease size of list
                return SUCCESS;
            }
        }
        prevNode = node; //update the iterators to the next node in the loops
        node = node->next;
    }
    //if get here, the node to remove not found and return FAIL because nothing to remove
    return FAIL;
}

/*
  Function Name	:	ListGetFirst
  Description	:	Get the iterator to the head of list, the first element.
  Parameters	:	pList	- Pointer to list ADT.
  Return Value	:	Pointer to the element in the head of list. NULL if list is empty.
  */
PElem ListGetFirst(PList pList) {
    if (pList == NULL) //input legal check
        return NULL;
    pList->iter = pList->head; // get the iterator to the head
    if (pList->iter == NULL) // if head is empty, list is empty, return NULL
        return NULL;
    return pList->iter->pElem;
}

/*
  Function Name	:	ListGetNext
  Description	:	Get the iterator to the next node in list, the next element.
  Parameters	:	pList	- Pointer to list ADT.
  Return Value	:	Pointer to the element in the next node of list. NULL if got to the end of list.
  */
PElem ListGetNext(PList pList) {
    //input legal check and check if the iter not got to the end of list
    if (pList == NULL || pList->iter == NULL || pList->iter->next == NULL )
        return NULL;
    pList->iter = pList->iter->next; //update iterator to the next node
    return pList->iter->pElem;
}

/*
  Function Name	:	ListCompare
  Description	:	Compare between two nodes in list.
  Parameters	:	pList1	- Pointer to list ADT.
                    pList2  - Pointet to list ADT.
  Return Value	:	BOOL- TRUE if the nodes are same, FALSE if not same or.
  */
BOOL ListCompare(PList pList1, PList pList2) {
    if (pList1 == NULL || pList2 == NULL) // input legal check, if one of the lists is NULL its FALSE
        return FALSE;
    PElem currElem1 = ListGetFirst(pList1);
    PElem currElem2 = ListGetFirst(pList2);
    // iterate the nodes in each list
    while (currElem1 != NULL && currElem2 != NULL) {
        if (pList1->elem_cmp(currElem1, currElem2) == FALSE) //compare elements of the nodes by user function
            return FALSE;
        //update iterators
        currElem1 = ListGetNext(pList1);
        currElem2 = ListGetNext(pList2);
    }
    //if one of lists is empty, or got to the end, not found the same node and return FALSE
    if ((currElem1 == NULL && currElem2 != NULL) || (currElem2 == NULL && currElem1 != NULL))
        return FALSE;
    //if two lists are empty or got to the end here, the lists are the same
    return TRUE;
}

/*
  Function Name	:	ListPrint
  Description	:	Print all the elements in the list.
  Parameters	:	pList	- Pointer to list ADT.
  Return Value	:   None.
  */
void ListPrint(PList pList) {
    if (pList == NULL) //input legal check.
        return;
    PElem currElem = ListGetFirst(pList);
    printf("[");
    //iterate all nodes and print each element in the node
    while (currElem != NULL) {
        pList->elem_prt(currElem); //print element by user function
        currElem = ListGetNext(pList);
    }

    printf("]\n");

}

/*
  Function Name	:	ListGetSize
  Description	:	Get the size of list, how many nodes exist in the list.
  Parameters	:	pList	- Pointer to list ADT.
  Return Value	:	inetegr, number of nodes that exist in the list.
  */
int ListGetSize(PList pList) {
    return pList->size;
}