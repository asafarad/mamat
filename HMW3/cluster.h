/*

  File: point.h

  Abstract:

    Cluster handling interface

*/

#ifndef _CLUSTER_H_
#define _CLUSTER_H_
#include "defs.h"
#include "point.h"
/*Types*/
typedef struct Cluster_* PCluster;

/*User functions*/
BOOL comparePoint(PElem pPoint1, PElem pPoint2);
PElem clonePoint(PElem pPoint);

/*Interface functions*/
PCluster ClusterCreate(int n);
void ClusterDestroy(PCluster pCluster);
Result ClusterAddPoint(PCluster pCluster, PPoint pPoint);
int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint);
void ClusterPrint(PCluster pCluster);
#endif /* _CLUSTER_H_ */
