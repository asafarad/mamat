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
BOOL compareCoordinate(int* pCoordinate1, int* pCoordinate2);
PElem cloneCoordinate(int* pCoordinate);
void removeCoordinate(int* pCoordinate);
void printCoordinate(int* pCoordinate);

/*Interface functions*/
PPoint PointCreate(int n);
void PointDestroy(PPoint pPoint);
Result PointAddCoordinate(PPoint pPoint, int k);
int PointGetFirstCoordinate(PPoint pPoint);
int PointGetNextCoordinate(PPoint pPoint);
void PointPrint(PPoint pPoint);

/*Getters*/
int PointGetDim(PPoint pPoint);
PList PointGetList(PPoint pPoint);
#endif  /* _POINT_H_ */
