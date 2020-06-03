/*

  File: point.c

  Abstract:

	Point handling implementation

*/


#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Types*/
typedef struct Point_ {
	int dim; // dimension of point
	PList pList; // list of coordinates
} Point;

/*User functions*/

/*
  Function Name	:	compareCoordinate
  Description	:	Cast two element pointers into integers and compare the two coordinates.
  Parameters	:	pElem1	- Pointer to coordinate 1.
					pElem2	- Pointer to coordinate 2.
  Return Value	:	BOOL- TRUE if equal, FALSE if not equal.
  */
BOOL compareCoordinate(PElem pElem1, PElem pElem2) {
	// cast pElem into pointer to integer
    if (pElem1 == NULL || pElem2 == NULL) // input legal check- pointers to NULL
        return FALSE;
    //casting
    int* pCoordinate1 = (int*)pElem1;
    int* pCoordinate2 = (int*)pElem2;
	if (*pCoordinate1 == *pCoordinate2) // check if numbers are equal
		return TRUE;
	else
		return FALSE;
}

/*
  Function Name	:	cloneCoordinate
  Description	:	Create a copy of pointer to coordinate and allocate the new pointer element.
  Parameters	:	pElem	- Pointer to coordinate.
  Return Value	:	Pointer to a new element, the new coordinate.
  */
PElem cloneCoordinate(PElem pElem) {
	if (pElem == NULL) // input legal check
		return NULL;
	int* pCoordinateClone;
	if ((pCoordinateClone = (int*)malloc(sizeof(int))) == NULL) // allocate memory for integer
		return NULL;
	*pCoordinateClone = *(int*)pElem; // copy the integer from the parameter by casting
	return pCoordinateClone;
}



/*
  Function Name	:	removeCoordinate
  Description	:	Free memory of pointer to coordinate.
  Parameters	:	pElem	- Pointer to coordinate.
  Return Value	:	None.
  */
void removeCoordinate(PElem pElem) {
    int* pCoordinate = (int*)pElem; //casting
	free(pCoordinate); // free ineteger pointer
}
/*
  Function Name	:	printCoordinate
  Description	:	Print the coordinate itself, the integer.
  Parameters	:	pElem	- Pointer to coordinate.
  Return Value	:	None.
  */
void printCoordinate(PElem pElem) {
    int* pCoordinate = (int*)pElem; //casting
	printf("%d ", *pCoordinate);
}


/*Interface functions*/

/*
  Function Name	:	PointCreate
  Description	:	Creates a new Point ADT and allocate the point to the ADT.
  Parameters	:	n    - Dimension of point, e.g the point have n coordinates.
  Return Value	:	Pointer to a new ADT of Point. NULL if allocate failed.
*/
PPoint PointCreate(int n) {
	PPoint newPoint;
	newPoint = (PPoint)malloc(sizeof(Point));//allocate pointer to new Point ADT
	if (newPoint == NULL)
		return NULL;

	//Constructor:
	newPoint->dim = n;
	PList pListPoint;
	//create the coordinates list in ADT- every elem in node of list is coordinate
	pListPoint = ListCreate(cloneCoordinate, removeCoordinate, compareCoordinate, printCoordinate);
	if (pListPoint == NULL)
		return NULL;
	newPoint->pList = pListPoint;
	return newPoint;
}

/*
  Function Name	:	PointDestroy
  Description	:	Delete the memory of the point ADT without leak.
  Parameters	:	pPoint    - Pointer to Point ADT to be destroyed.
  Return Value	:	None.
  */
void PointDestroy(PElem pElem) {
    PPoint pPoint = (PPoint)pElem; //casting
	ListDestroy(pPoint->pList); // destroy the coordinates list
	free(pPoint); // free the ADT itself
}

/*
  Function Name	:	PointAddCoordinate
  Description	:	Add a new coordinate to the point in case the point isn't full.
  Parameters	:	pPoint	- Pointer to Point ADT.
					k		- integer coordiante to be added.
  Return Value	:	Result- SUUCCES if coordinate added to the point. FAIL if coordinate not added.
  */
Result PointAddCoordinate(PPoint pPoint, int k) {
	if (pPoint == NULL) // input legal check
		return FAIL;
	if (ListGetSize(pPoint->pList) >= pPoint->dim)
		return FAIL;
	int* pCoordinate = &k;
	return ListAdd(pPoint->pList, pCoordinate);
}

/*
  Function Name	:	PointGetFirstCoordinate
  Description	:	Get the first coordinate of the point, and get the iterator to the head of the list.
  Parameters	:	pPoint	- Pointer to Point ADT.
  Return Value	:	First coordinate of point if exist(point isn't empty). if point is empty return 0.
  */
int PointGetFirstCoordinate(PPoint pPoint) {
	if (pPoint == NULL) // input legal check
		return 0;
	int* pCoordinate =(int*)ListGetFirst(pPoint->pList); //get the iterator to the first element
	if (pCoordinate == NULL) // if list is empty, first element is NULL, return 0
		return 0;
	return *pCoordinate;
}

/*
  Function Name	:	PointGetNextCoordinate
  Description	:	Get the iterator to the next node in coordinates list- get the next coordinate of the point.
  Parameters	:	pPoint	- Pointer to Point ADT.
  Return Value	:	Next coordinate of point if exist. if not exist return 0.
  */
int PointGetNextCoordinate(PPoint pPoint) {
	if (pPoint == NULL) // input legal check
		return 0;
	int* pCoordinate = (int*)ListGetNext(pPoint->pList); // get the iterator to the next element
	if (pCoordinate == NULL) // if returned the end of the list return 0
		return 0;
	return *pCoordinate;
}
/*
  Function Name	:	PointPrint
  Description	:	Print the point and its coordinates by the template.
  Parameters	:	pElem	- Pointer to Point ADT.
  Return Value	:	None.
  */
void PointPrint(PElem pElem) {
	if (pElem == NULL) // input legal check
		return;
    PPoint pPoint = (PPoint)pElem; //casting
	printf("Point Dimension: %d, Size: %d, Coordinates: ", pPoint->dim, ListGetSize(pPoint->pList));
	ListPrint(pPoint->pList);
}

/*Getters*/
/*
  Function Name	:	PointGetDim
  Description	:	Getter for the dimension of point.
  Parameters	:	pPoint	- Pointer to Point ADT.
  Return Value	:	Dimension of the point.
  */
int PointGetDim(PPoint pPoint) {
	return pPoint->dim;
}

/*
  Function Name	:	PointGetList
  Description	:	Getter for the coordinates list of point.
  Parameters	:	pPoint	- Pointer to Point ADT.
  Return Value	:	List ADT with the coordinates in the nodes.
  */
PList PointGetList(PPoint pPoint) {
	return pPoint->pList;
}

