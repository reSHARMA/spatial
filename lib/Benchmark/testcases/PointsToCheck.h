#ifndef PointsToCheck_H
#define PointsToCheck_H
#include <stdio.h>

template <class T,class U>
void MustPointsTo(T,U);
template <class T,class U>
void DoesNotPointsTo(T,U);
template <class T,class U>
void MayPointsTo(T,U);

#endif


