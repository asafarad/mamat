#ifndef _CLUSTER_H_
#define _CLUSTER_H_
#include "defs.h"
#include "point.h"

typedef struct Cluster_* PCluster;


/*Interface functions*/
PCluster ClusterCreate(int n);
void ClusterDestroy(PCluster pCluster);
Result ClusterAddPoint(PCluster pCluster, PPoint pPoint);
int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint);
void ClusterPrint(PCluster pCluster);
#endif
