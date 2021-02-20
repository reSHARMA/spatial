#include <stdio.h>
#include "PointsToCheck.h"

int main(){
    int **p, **q, **r, *x, *y, *z , *w, a ,b, c;
    p = &x;
    w = x;
    while(a > 0){
        *p = &b;        
        while(b > 0){
            p = &x;
            x = &a;
            switch(a){
                case 1:
                    x = &b;
                    break;
                case 2:
                    x = &c;
                    break;
                case 3:
                    y = &a;
                    break;
                case 5:
                    break;
                default :
                    y = &b;
                    break;
            }
            *p = w;    
            b--;        
        }
        p = &y;
        q = &x;
        p = r;
        a--;
    }
    if(a > -1){
        *p = *q;
    }   
    else{
        *q = &a;
    }
    x = &a;
    y = &b;
    return 0;
}
