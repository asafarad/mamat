#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Point_ {
	int dim;
	PList pList;
} Point;


/*User functions*/
ElemCompare compareCoordinate(PElem pElem1, PElem pElem2) {
	int* pCoordinate1 = (int*)pElem1;
	int* pCoordinate2 = (int*)pElem2;
	if (*pCoordinate1 == *pCoordinate2)
		return TRUE;
	else
		return FALSE;
}
CloneElem cloneCoordinate(PElem pElem) {
	if (pElem == NULL)
		return NULL;
	int* pCoordinate;
	if ((pCoordinate = (int*)malloc(sizeof(int))) == NULL)
		return NULL;
	*pCoordinate = *(int*)pElem;
	return pCoordinate;
}
CloneElem clonePoint(PElem pElem) {
	if (pElem == NULL)
		return NULL;
	PPoint pPoint = PointCreate(((PPoint)pElem)->dim);
	if (pPoint == NULL)
		return NULL;
	pPoint->pList = ((PPoint)pElem)->pList;
	/*if ((pPoint = (PPoint)malloc(sizeof(Point))) == NULL);
		return NULL;
	pPoint = (PPoint)pElem;*/
	return pPoint;
}
ElemRemove removeCoordinate(PElem pElem) {
	free((int*)pElem);
}
ElemPrint printCoordinate(PElem pElem) {
	int* pCoordiante = (int*)pElem;
	printf("%d ", *pCoordiante);
}


/*Interface functions*/
PPoint PointCreate(int n) {
	PPoint newPoint;
	newPoint = (PPoint)malloc(sizeof(Point));
	if (newPoint == NULL)
		return NULL;

	//Constructor:
	newPoint->dim = n;
	PList pListPoint;
	pListPoint = ListCreate(cloneCoordinate, removeCoordinate, compareCoordinate, printCoordinate);
	if (pListPoint == NULL)
		return NULL;
	newPoint->pList = pListPoint;
	return newPoint;
}
void PointDestroy(PPoint pPoint) {
	ListDestroy(pPoint->pList);
	free(pPoint);
}
Result PointAddCoordinate(PPoint pPoint, int k) {
	if (ListGetSize(pPoint->pList) >= pPoint->dim)
		return FAIL;
	int* pCoordinate = &k;
	return ListAdd(pPoint->pList, pCoordinate);
}
int PointGetFirstCoordinate(PPoint pPoint) {
	int* pCoordinate =(int*)ListGetFirst(pPoint->pList);
	if (pCoordinate == NULL)
		return 0;
	return *pCoordinate;
}
int PointGetNextCoordinate(PPoint pPoint) {
	int* pCoordinate = (int*)ListGetNext(pPoint->pList);
	if (pCoordinate == NULL)
		return 0;
	return *pCoordinate;
}
void PointPrint(PPoint pPoint) {
	printf("Point Dimension: %d, Size: %d, Coordinates: ", pPoint->dim, ListGetSize(pPoint->pList));
	ListPrint(pPoint->pList);
}

int PointGetDim(PPoint pPoint) {
	return pPoint->dim;
}

