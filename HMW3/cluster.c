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
	if (pPoint == NULL) // input legal check
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
		iterCoordinate = PointGetNextCoordinate(pPoint);
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
	newCluster = (PCluster)malloc(sizeof(Cluster));//allocate pointer to new Cluster ADT
	if (newCluster == NULL)
		return NULL;

	//Constructor:
	newCluster->dim = n;
	PList pListCluster;
	//create the points list in ADT- every elem in node of list is Point ADT
	pListCluster = ListCreate(clonePoint, PointDestroy, comparePoint, PointPrint);
	if (pListCluster == NULL)
		return NULL;
	newCluster->pList = pListCluster;
	newCluster->minSqDist = 10000; //initialize min square distance to the maximum value- 10000
	return newCluster;

}

/*
  Function Name	:	ClusterDestroy
  Description	:	Delete the memory of the cluster ADT without leak.
  Parameters	:	pCluster    - Pointer to Cluster ADT to be destroyed.
  Return Value	:	None.
  */
void ClusterDestroy(PCluster pCluster) {
	ListDestroy(pCluster->pList); // destroy the points list
	free(pCluster); // free the ADT itself
}

/*
  Function Name	:	ClusterAddPoint
  Description	:	Add a new point to the cluster.
  Parameters	:	pCluster	- Pointer to Cluster ADT.
					pPoint		- Pointer to Point ADT to be added.
  Return Value	:	Result- SUUCCES if point added to the cluster. FAIL if point not added.
  */
Result ClusterAddPoint(PCluster pCluster, PPoint pPoint) {
	if (pPoint == NULL || pCluster == NULL || (PointGetDim(pPoint) != pCluster->dim)) // input legal check
		return FAIL;
	PPoint iterPoint;
	iterPoint = (PPoint)ListGetFirst(pCluster->pList); // initialize point iterator for the cluster
	//check if the point already exist in cluster
	while (iterPoint != NULL) { // while the iterator points to a point
		if (comparePoint(pPoint, iterPoint) == TRUE) { // compare the current point with the new point
			return FAIL; //if the point exist it is FAIL, don't add it
		}
		iterPoint = (PPoint)ListGetNext(pCluster->pList); // get the next point
	}
	int newMinDistance = ClusterGetMinDistance(pCluster, pPoint); //calculate the minSqrDist of new point with cluster before it is added
	if (newMinDistance < pCluster->minSqDist)
		pCluster->minSqDist = newMinDistance; // update the minSqDist with the new point distance
	return ListAdd(pCluster->pList, pPoint);//finally, add the point to the list
}

/*
  Function Name	:	ClusterGetMinDistance
  Description	:	Calculate the L2 minimum distance between a point and a whole cluster. distance=||x-y||^2
  Parameters	:	pCluster	- Pointer to Cluster ADT.
					pPoint		- Pointer to Point ADT.
  Return Value	:	Minimum Square Distance between point and cluster.
  */
int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint) {
	if (pCluster == NULL || pPoint == NULL) //input legal check
		return 10000; // default value
	PPoint iterPoint = (PPoint)ListGetFirst(pCluster->pList); // get point iterator
	int minSqDist = 10000, currSqDist = 0; //define default minSqDist value 10000 according to the demands
	int k1, k2, i;
	while (iterPoint != NULL) {
		k1 = PointGetFirstCoordinate(iterPoint); // coordinate of current point
		k2 = PointGetFirstCoordinate(pPoint); // coordinate of input point
		 // run over all coordinates in dimension of point
		for (i = 0; i < pCluster->dim; i++) {
			currSqDist = currSqDist + (k1 - k2) * (k1 - k2); // sum the current distance between coordinates
			k1 = PointGetNextCoordinate(iterPoint);
			k2 = PointGetNextCoordinate(pPoint);
		}
		if (currSqDist < minSqDist) //update the minimum square distance if needed
			minSqDist = currSqDist;
		currSqDist = 0; // initialize the tmp dist back to 0 for the next point
		iterPoint = (PPoint)ListGetNext(pCluster->pList); // get the next point in cluster
	}
	return minSqDist;
}

/*
  Function Name	:	ClusterPrint
  Description	:	Print the cluster and its points by the template.
  Parameters	:	pCluster	- Pointer to Cluster ADT.
  Return Value	:	None.
  */
void ClusterPrint(PCluster pCluster) {
	printf("Cluster's dimension: %d\n", pCluster->dim);
	ListPrint(pCluster->pList);
	printf("Minimum Square Distance: %d\n", pCluster->minSqDist);
}