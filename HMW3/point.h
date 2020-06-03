/*

  File: point.h

  Abstract:

    Point handling interface

*/

#ifndef _POINT_H_
#define _POINT_H_

#include "defs.h"
#include "list.h"
/*Types*/
typedef struct Point_* PPoint;

/*User functions*/
BOOL compareCoordinate(PElem pCoordinate1, PElem pCoordinate2);
PElem cloneCoordinate(PElem pCoordinate);
void removeCoordinate(PElem pCoordinate);
void printCoordinate(PElem pCoordinate);

/*Interface functions*/
PPoint PointCreate(int n);
void PointDestroy(PElem pPoint);
Result PointAddCoordinate(PPoint pPoint, int k);
int PointGetFirstCoordinate(PPoint pPoint);
int PointGetNextCoordinate(PPoint pPoint);
void PointPrint(PElem pPoint);

/*Getters*/
int PointGetDim(PPoint pPoint);
PList PointGetList(PPoint pPoint);
#endif  /* _POINT_H_ */
