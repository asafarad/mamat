#include "cluster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cluster_ {
	int dim;
	int minSqDist;
	PList pList;
} Cluster;

/*User functions*/


/*Interface functions*/
PCluster ClusterCreate(int n) {
	PCluster newCluster;
	newCluster = (PCluster)malloc(sizeof(Cluster));
	if (newCluster == NULL)
		return NULL;

	//Constructor:
	newCluster->dim = n;
	PList pListCluster;
	pListCluster = ListCreate(clonePoint, PointDestroy, ListCompare, PointPrint);
	if (pListCluster == NULL)
		return NULL;
	newCluster->pList = pListCluster;
	newCluster->minSqDist = 10000;
	return newCluster;

}
void ClusterDestroy(PCluster pCluster) {
	ListDestroy(pCluster->pList);
	free(pCluster);
}
Result ClusterAddPoint(PCluster pCluster, PPoint pPoint) {
	if (pPoint == NULL || pCluster == NULL || (PointGetDim(pPoint) != pCluster->dim))
		return FAIL;
	PPoint iterPoint = ListGetFirst(pCluster->pList);
	while (iterPoint != NULL) {
		if (ListCompare(pPoint, iterPoint) == TRUE) {
			return FAIL;
		}
		iterPoint = ListGetNext(pCluster->pList);
	}
	int newMinDistance = ClusterGetMinDistance(pCluster, pPoint);
	if (newMinDistance < pCluster->minSqDist)
		pCluster->minSqDist = newMinDistance;
	return ListAdd(pCluster->pList, pPoint);
}
int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint) {
	PPoint iterPoint = ListGetFirst(pCluster->pList);
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
		iterPoint = ListGetNext(pCluster->pList);		
	}
	return minSqDist;
}
void ClusterPrint(PCluster pCluster) {
	printf("Cluster's dimension: %d\n", pCluster->dim);
	ListPrint(pCluster->pList);
	printf("Minimum Square Distance: %d\n", pCluster->minSqDist);
}