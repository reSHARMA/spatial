   #include "PointsToCheck.h" 	
   int ***p, **q, **a, **b, *c, *m, *n, d;
   int main() {
       m = &d; 
       a = b = &c; 
// p -> {}
       if (a) {
           p = &a; 
// p -> {a}
           MustPointsTo(p, a); 
           DoesNotPointsTo(p, b); 
       } else {
           p = &b; 
// p -> {b}
           MustPointsTo(p, b); 
       }  
// p -> {a, b} 
       return 0;
   }
