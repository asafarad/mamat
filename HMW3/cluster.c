/*

  File: cluster.c

  Abstract:

	Cluster handling implementation

*/

#include "cluster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Types*/
typedef struct Cluster_ {
	int dim; // dimension of cluster
	int minSqDist; // minimum square distance of cluster
	PList pList; // list of points in cluster
} Cluster;

/*User functions*/
/*
  Function Name	:	clonePoint
  Description	:	Create a copy of pointer to Point ADT and allocate the new pointer element.
  Parameters	:	pElem	- Pointer to Point ADT.
  Return Value	:	Pointer to a new element, the new Point ADT. return NULL if allocate failed.
  */
PElem clonePoint(PPoint pPoint) {
	if (pPoint == NULL)
		return NULL;
	int dim = PointGetDim(pPoint); // get dimension
	PPoint pPointClone = PointCreate(dim); // create a new point
	if (pPointClone == NULL)
		return NULL;
	int iterCoordinate = PointGetFirstCoordinate(pPoint);
	int i;
	// copy all coordinates from pPoint to the new point
	for (i = 0; i < dim; i++) {
		PointAddCoordinate(pPointClone, iterCoordinate);
		iterCoordinate = PointGetNextCoordinate(pPointClone);
	}
	return (PElem)pPointClone;
}

/*
  Function Name	:	comparePoint
  Description	:	Compare the two point ADT by using the ListCompare.
  Parameters	:	pPoint1	- Pointer to Point 1.
					pPoint2	- Pointer to Point 2.
  Return Value	:	BOOL- TRUE if equal, FALSE if not equal.
  */
BOOL comparePoint(PPoint pPoint1, PPoint pPoint2) {
	if (PointGetDim(pPoint1) != PointGetDim(pPoint2)) // if not the same dimension- not equal
		return FALSE;
	// compare using the ListCompare
	return (ListCompare(PointGetList(pPoint1), PointGetList(pPoint2)));
}
/*Interface functions*/

/*
  Function Name	:	ClusterCreate
  Description	:	Create a copy of pointer to coordinate and allocate the new pointer element.
  Parameters	:	n    - Dimension of cluster, e.g the points in cluster have n coordinates.
  Return Value	:	Pointer to a new ADT of Cluster. NULL if allocate failed.
  */
PCluster ClusterCreate(int n) {
	PCluster newCluster;
	newCluster = (PCluster)malloc(sizeof(Cluster));
	if (newCluster == NULL)
		return NULL;

	//Constructor:
	newCluster->dim = n;
	PList pListCluster;
	pListCluster = ListCreate(clonePoint, PointDestroy, comparePoint, PointPrint);
	if (pListCluster == NULL)
		return NULL;
	newCluster->pList = pListCluster;
	newCluster->minSqDist = 10000; //initialize min square distance to the maximum value- 10000
	return newCluster;

}

/*
  Function Name	:	ClusterDestroy
  Description	:	
  Parameters	:	
  Return Value	:	
  */
void ClusterDestroy(PCluster pCluster) {
	ListDestroy(pCluster->pList);
	free(pCluster);
}

/*
  Function Name	:	ClusterAddPoint
  Description	:	
  Parameters	:	
  Return Value	:	
  */
Result ClusterAddPoint(PCluster pCluster, PPoint pPoint) {
	if (pPoint == NULL || pCluster == NULL || (PointGetDim(pPoint) != pCluster->dim))
		return FAIL;
	PPoint iterPoint;
	iterPoint = (PPoint)ListGetFirst(pCluster->pList);
	while (iterPoint != NULL) {
		if (comparePoint(pPoint, iterPoint) == TRUE) {
			return FAIL;
		}
		iterPoint = (PPoint)ListGetNext(pCluster->pList);
	}
	int newMinDistance = ClusterGetMinDistance(pCluster, pPoint);
	if (newMinDistance < pCluster->minSqDist)
		pCluster->minSqDist = newMinDistance;
	return ListAdd(pCluster->pList, pPoint);
}

/*
  Function Name	:	ClusterGetMinDistance
  Description	:	
  Parameters	:	
  Return Value	:	
  */
int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint) {
	PPoint iterPoint = (PPoint)ListGetFirst(pCluster->pList);
	int minSqDist = 10000, currSqDist = 0;
	int k1, k2, i;
	while (iterPoint != NULL) {
		k1 = PointGetFirstCoordinate(iterPoint);
		k2 = PointGetFirstCoordinate(pPoint);
		for (i = 0; i < pCluster->dim; i++) {
			currSqDist = currSqDist + (k1 - k2) * (k1 - k2);
			k1 = PointGetNextCoordinate(iterPoint);
			k2 = PointGetNextCoordinate(pPoint);
		}
		if (currSqDist < minSqDist)
			minSqDist = currSqDist;
		currSqDist = 0;
		iterPoint = (PPoint)ListGetNext(pCluster->pList);		
	}
	return minSqDist;
}

/*
  Function Name	:	ClusterPrint
  Description	:	
  Parameters	:	
  Return Value	:	
  */
void ClusterPrint(PCluster pCluster) {
	printf("Cluster's dimension: %d\n", pCluster->dim);
	ListPrint(pCluster->pList);
	printf("Minimum Square Distance: %d\n", pCluster->minSqDist);
}