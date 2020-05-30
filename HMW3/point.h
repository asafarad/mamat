#ifndef _POINT_H_
#define _POINT_H_

#include "defs.h"
#include "list.h"
typedef struct Point_* PPoint;

/*User functions*/
ElemCompare compareCoordinate(PElem pElem1, PElem pElem2);
CloneElem cloneCoordinate(PElem pElem);
CloneElem clonePoint(PElem pElem);
ElemRemove removeCoordinate(PElem pElem);
ElemPrint printCoordinate(PElem pElem);

/*Interface functions*/
PPoint PointCreate(int n);
void PointDestroy(PPoint pPoint);
Result PointAddCoordinate(PPoint pPoint, int k);
int PointGetFirstCoordinate(PPoint pPoint);
int PointGetNextCoordinate(PPoint pPoint);
void PointPrint(PPoint pPoint);

int PointGetDim(PPoint pPoint);
#endif
