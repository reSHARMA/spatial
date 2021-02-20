#include "PointsToCheck.h"
#include <stdio.h>
int *a, *b, **c, x, y, *w, **s, u;
int main(){

    a=&x;
    MustPointsTo(a,x);
    DoesNotPointsTo(a,y);
    DoesNotPointsTo(a,u);
    
    b=&y;
    MustPointsTo(b,y);
    DoesNotPointsTo(b,x);
    DoesNotPointsTo(b,u);
    
    c=&a;
    MustPointsTo(c,a);
    DoesNotPointsTo(c,b);
    DoesNotPointsTo(c,w);


    s = c;
    MustPointsTo(s,a);
    DoesNotPointsTo(s,b);
    DoesNotPointsTo(s,w);
    
    s=&w;
    MustPointsTo(s,w);
    DoesNotPointsTo(s,a);
    DoesNotPointsTo(s,b);
    
    w=&u;
    MustPointsTo(w,u);
    DoesNotPointsTo(w,x);
    DoesNotPointsTo(w,y);


    u = 9;

    if(x==5)
    {
    	*c = &y;
        MustPointsTo(a,y);
        DoesNotPointsTo(a,x);
        DoesNotPointsTo(a,u);

        s=&a;
        MustPointsTo(s,a);
        DoesNotPointsTo(s,b);
        DoesNotPointsTo(s,w);
    }
    else
    {
		b =&x;
        MustPointsTo(b,x);
        DoesNotPointsTo(b,y);
        DoesNotPointsTo(b,u);

        s=&b;
        MustPointsTo(s,b);
        DoesNotPointsTo(s,a);
        DoesNotPointsTo(s,w);
    }
    //------------------------------------------------------------------------------------------
    MayPointsTo(a,x);
    MayPointsTo(a,y);
    

	MayPointsTo(b,x);
    MayPointsTo(b,y);
    
    MayPointsTo(s,a);
    MayPointsTo(s,b);
    DoesNotPointsTo(s,w);
    //MayPointsTo(s,w) no longer exists as atleast one of if/else block is traversed.
    
    
    
    //--------------------------------------------------------------------------------------------
    while(u>10)
    {
        // Through the backedge arising due to the while loop, we get the following points to information at the entry of the loop.
        MayPointsTo(a,u);
        MayPointsTo(b,u);
		*s = &u;
		MayPointsTo(a,u);
		MayPointsTo(b,u);
		
		u--;
    }
    
    return 0;

}
