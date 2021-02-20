#include <stdio.h>
#include "PointsToCheck.h"
int main()
{
    int **p, **q, **r;
    int *a, *b, *c, *d, *e;
    int m;
    do
    {     
        *q = &m;
        MayPointsTo(b,m);
        if (m)
        {
            q = &b;
        }
        MayPointsTo(q,b);
    } while (1);
    q = &e;
}
