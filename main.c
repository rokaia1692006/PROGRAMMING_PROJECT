#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include<stdlib.h>
#include "reservation.h"
#include"ReservationFunctions.c"
int main(){
    char choose;
    printf("Welcome to the reservation system!\n");
    printf("Please choose an option:\n");
    while(1){
    printf("enter r for reservation and c for changing reservaton and e to exit program: ");
    scanf(" %c",&choose);
    if(choose == 'r'){
        getchar();
    reservationInfo* customer = malloc(sizeof(reservationInfo));
    reserve(customer);
    free(customer); }
    if(choose == 'c'){
    changeReservation();}
    if(choose == 'e'){
    return 0;}}
}
