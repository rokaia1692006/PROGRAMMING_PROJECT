#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lcm(int n , int m ){
    int i = 1;
    while (i <= n && i <= m) {
        if (i % n == 0 && i % m == 0) {
            return i;
        }
        i++;
}}
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
FRAC Add_fractions(FRAC n , FRAC m){
    FRAC result;
    int commonDenom = lcm(n.Denom,m.Denom);
    result.Num = ((commonDenom/n.Denom)*n.Num)+((commonDenom/m.Denom)*m.Num);
    result.Denom = commonDenom;
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
FRAC N1, N2,N , D , S;
N1.Num=3;
N1.Denom=4;
N2.Num=1;
N2.Denom=2;
N=Multiply_fractions(N1,N2);
D = Divide_fractions(N1,N2);
S = Add_fractions(N1,N2);
printf("result of addition N1 and N2= %d / %d \n", S.Num,
S.Denom);
printf("result of division N1 by N2= %d / %d \n", D.Num,
D.Denom);
printf("result of subtract N1 to N2= %d / %d", N.Num,
N.Denom);
}