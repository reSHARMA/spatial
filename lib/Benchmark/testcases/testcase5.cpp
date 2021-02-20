#include <stdio.h>
#include "PointsToCheck.h"
int **p, **q;
int *x, *y;
int a, b, c, d;
int main()
{

    int e;
    p = &x;
    q = &y;
    MustPointsTo(p,x);
    MustPointsTo(q,y);
    d = 40;

    if (b)
    {
        *q = &a;
        x = &b;
        MustPointsTo(y,a);
        MustPointsTo(x,b);
    }
    else
    {
        *p = &a;
        y = &b;
        MustPointsTo(x,a);
        MustPointsTo(y,b);
    }

    MayPointsTo(x,a);
    MayPointsTo(x,b);
    MayPointsTo(y,a);
    MayPointsTo(y,b);
    
    x = y;
    MayPointsTo(x,a);
    MayPointsTo(x,b);
    MayPointsTo(y,a);
    MayPointsTo(y,b);
    
    a = b;
    **p = 30;
    *x = 40;
    printf("%d", e);
}