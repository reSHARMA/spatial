#include <stdio.h>
#include "PointsToCheck.h"

int **p, **q, **r, *x, *y, *z ,a ,b, c;
int main(){
    p = &x;
    MustPointsTo(p,x);
    DoesNotPointsTo(p,y);
    DoesNotPointsTo(p,z);
    


    while(a > 0){
        MayPointsTo(p,x);
        MayPointsTo(p,y);
        DoesNotPointsTo(p,z);
        MayPointsTo(q,x);

        *p = &b;
        MayPointsTo(x,b);
        MayPointsTo(y,b);
     
        while(b > 0){
            MayPointsTo(q,x);
            MayPointsTo(q,y);
            MustPointsTo(x,b);
            MayPointsTo(y,a);
            MayPointsTo(y,b);

            x = &b;
            y = &a;
            q = &y;

            MustPointsTo(x,b);
            MustPointsTo(y,a);
            MustPointsTo(q,y);

            b--;
        }
        MayPointsTo(x,b);
        MayPointsTo(y,a);
        MayPointsTo(y,b);
        MayPointsTo(q,x);
        MayPointsTo(q,y);

        p = &y;
        q = &x;
        p = r;
	
        MustPointsTo(q,x);
        a--;
    }

    if(a > -1){
        MayPointsTo(p,x);
        MayPointsTo(q,x);
        *p = *q;

    }   
    else{
        MayPointsTo(p,x);
        MayPointsTo(q,x);
        *q = &a;
        MayPointsTo(x,a);
    }

    MayPointsTo(p,x);
    MayPointsTo(q,x);
    MayPointsTo(x,a);

    x = &a;
    y = &b;
    MustPointsTo(x,a);
    MustPointsTo(y,b);

    return 0;
}
