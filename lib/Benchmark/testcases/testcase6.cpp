#include <stdio.h>
#include "PointsToCheck.h"
int **p, **q, **r;
int *a, *b, *c, *d, *e;
int m;
int main()
{
    do
    {
        MayPointsTo(q,b);
        r = &a;
        MustPointsTo(r,a);

        *q = &m;
        MayPointsTo(b,m);
        if (m)
        {
            q = &b;
            MustPointsTo(q,b);
        }
        else
        {
            break;
        }
        MayPointsTo(q,b);
    } while (1);
    MayPointsTo(q,b);
    MayPointsTo(b,m);
    MayPointsTo(r,a);
    e = *p;
    q = &e;
    MustPointsTo(q,e);
}