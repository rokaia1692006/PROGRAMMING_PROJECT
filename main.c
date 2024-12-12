#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct{
    int real;
    int img;
} Complex;
Complex add_Complex (Complex a ,Complex b){
    Complex total;
    total.real = a.real + b.real;
    total.img = a.img + b.img;
    return total;
}
void print_Complex (Complex a){
    printf("%d + %di\n",a.real,a.img);
}
Complex read_Complex(){
    Complex a;
    printf("enter real part of number: ");
    scanf("%d",&a.real);
    printf("enter imaginary part of number: ");
    scanf("%d",&a.img);
    printf("\t*******************************************\n");
    return a;
}
int Compare_Complex(Complex a, Complex b){
    float mag_a = pow((pow(a.img,2)+pow(a.real,2)),0.5), mag_b = pow((pow(b.img,2)+pow(b.real,2)),0.5) ;
    if(mag_a == mag_b){
        return 0;

    }
    else if (mag_a>mag_b){
        return 1;
    }
    else if (mag_a<mag_b){
        return -1;
    }
}

int main(){
    Complex a,b,c,d;
    a = read_Complex();
    b = read_Complex();
    c = read_Complex();
    printf("FIRST NUMBER = ");
    print_Complex(a);
    printf("\n");
    printf("SECOND NUMBER = ");
    print_Complex(b);
    printf("\n");
    printf("THIRD NUMBER = ");
    print_Complex(c);
    printf("\n");
    d = add_Complex(a,b);
    d = add_Complex(d,c);
    printf("ADDITION OF COMPLEX = ");
    print_Complex(d);
    printf("\n");
    int i ,x,y;
    i = Compare_Complex(a,b);
    x = Compare_Complex(b,c);
    y = Compare_Complex(a,c);
    if (i == 1 && y == 1){
        printf("HIGHEST MAGNITITUDE = ");
        print_Complex(a);
        printf("\n");
    }
    else if(x == 1 && i == -1){
        printf("HIGHEST MAGNITITUDE = ");
        print_Complex(b);
    printf("\n");
    }
    else if(y == -1 && x == -1){
        printf("HIGHEST MAGNITITUDE = ");
        print_Complex(c);
    printf("\n");
    }
    else if(x == 0 && y == 0 && i ==0){
        printf("All complex numbers are equal\n");
    }


    
}