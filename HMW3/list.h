#ifndef _LIST_H_
#define _LIST_H_
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List_* PList;
typedef void* PElem;

/*User functions*/
typedef BOOL (*ListCompare)(PList pList1, PList pList2);
typedef void (*ListPrint)(PList pList);
typedef Result (*ListRmv)(PList pList, PElem pElem);
typedef PElem(*CloneElem) (PElem pElem);

/*Interface functions*/
PList ListCreate(CloneElem elem_cln, ListRmv list_rmv, ListCompare list_cmp, ListPrint list_prt);
void ListDestroy(PList pList);
Result ListAdd(PList pList, PElem pElem);
PElem ListGetFirst(PList pList);
PElem ListGetNext(PList pList);
 

#endif
