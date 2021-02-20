#include "PointsToCheck.h"
int ***p, **q, **a, **b, *c, *m,*n,d;
int main(){

    m = &d;
    a = b = &c;
    if(a)
    {
        p = &a;
        MustPointsTo(p,a);
        DoesNotPointsTo(p,b);

        q = &c;
        MustPointsTo(q,c);
        DoesNotPointsTo(q,m);
        DoesNotPointsTo(q,n);
    }
    else
    {
        p = &b;
        MustPointsTo(p,b);
        DoesNotPointsTo(p,a);

        q = &c;
        MustPointsTo(q,c);
        DoesNotPointsTo(q,m);
        DoesNotPointsTo(q,n);

    }

    MayPointsTo(p,a);
    MayPointsTo(p,b);
    MustPointsTo(q,c);
    DoesNotPointsTo(q,m);
    DoesNotPointsTo(q,n);


	*a = m;
    MustPointsTo(c,d);

	n = *b;
	MustPointsTo(n,d);
	
	*p=&n;
	MayPointsTo(a,n);
	MayPointsTo(b,n);
    MayPointsTo(a,c);
	MayPointsTo(b,c);
    DoesNotPointsTo(a,m);
    DoesNotPointsTo(b,m);
}

