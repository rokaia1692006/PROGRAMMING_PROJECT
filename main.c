#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
int Num;
int Denom;
} FRAC;
FRAC Divide_fractions(FRAC n , FRAC m){
    FRAC result;
    result.Num = n.Num * m.Denom;
    result.Denom = n.Denom * m.Num;
    return result;
}
FRAC Multiply_fractions (FRAC n , FRAC m)
{
FRAC ans;
ans.Num= n.Num * m.Num;
ans.Denom = n.Denom * m.Denom;
return ans;
}
void main()
{
FRAC N1, N2,N , D;
N1.Num=3;
N1.Denom=4;
N2.Num=1;
N2.Denom=2;
N=Multiply_fractions(N1,N2);
D = Divide_fractions(N1,N2);
printf("result of division N1 by N2= %d / %d \n", D.Num,
D.Denom);
printf("result of subtract N1 to N2= %d / %d", N.Num,
N.Denom);
}