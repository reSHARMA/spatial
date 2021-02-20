#include "PointsToCheck.h"
int *p, *q, x, y;
void g()
{

    if (y)
    {
        p = &x;
        *q = 20;
    }
}
void f()
{
    g();
    *p = 40;
}

int main()
{
    q = &y;
    f();
    *p = 20;
}
