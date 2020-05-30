#ifndef _LIST_H_
#define _LIST_H_
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List_* PList;
typedef void* PElem;

/*User functions*/
typedef BOOL (*ElemCompare)(PElem pElem1, PElem pElem2);
typedef void (*ElemPrint)(PElem pElem);
typedef void (*ElemRemove)(PElem pElem);
typedef PElem(*CloneElem) (PElem pElem);

/*Interface functions*/
PList ListCreate(CloneElem elem_cln, ElemRemove pElem, ElemCompare elem_cmp, ElemPrint elem_prt);
void ListDestroy(PList pList);
Result ListAdd(PList pList, PElem pElem);
PElem ListGetFirst(PList pList);
PElem ListGetNext(PList pList);
BOOL ListCompare(PList pList1, PList pList2);
Result ListRemove(PList pList, PElem pElem);
void ListPrint(PList pList);

int ListGetSize(PList pList);
 

#endif
