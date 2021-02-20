#include <stdio.h>
#include "PointsToCheck.h"
int *x, *y, *w, **p, **q, a, b, c;
int main(){
    p = &x;
	x = &a;

	MustPointsTo(p,x);
	MustPointsTo(x,a);

	switch(a){
		case 1:
			x = &b;
			MustPointsTo(x,b);
			break;
		case 2:
			x = &c;
			MustPointsTo(x,c);
			break;
		case 3:
			y = &a;
			MustPointsTo(y,a);
			break;
		case 5:
			break;
		default :
			y = &b;
			MustPointsTo(y,b);
			break;
	}
	MustPointsTo(p,x);
	MayPointsTo(x,a);
	MayPointsTo(x,b);
	MayPointsTo(x,c);
	MayPointsTo(y,a);
	MayPointsTo(y,b);
	*p = w;
	//cannot say anything about points to info of x MustAlias(x,w) exists though.
	MayPointsTo(y,a);
	MayPointsTo(y,b);
    // **p = 10;	
}