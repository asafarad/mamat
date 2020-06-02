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
BOOL comparePoint(PPoint pPoint1, PPoint pPoint2);
PElem clonePoint(PPoint pPoint);

/*Interface functions*/
PCluster ClusterCreate(int n);
void ClusterDestroy(PCluster pCluster);
Result ClusterAddPoint(PCluster pCluster, PPoint pPoint);
int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint);
void ClusterPrint(PCluster pCluster);
#endif /* _CLUSTER_H_ */
