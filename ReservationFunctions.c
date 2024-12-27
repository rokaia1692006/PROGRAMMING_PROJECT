#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include "reservation.h"
#include <time.h>
#include <stdlib.h>
#include "loadfunc.c"
//search for room
int findRoom(Room* rooms,char NUM[],int count){
    int i;
    int roomnumber = atoi(NUM);
    for(i=0;i<count;i++){
        if(rooms[i].number ==roomnumber){
            //return index
            return i;
        }
        }
        return -1;

}

// 1 = yes 0 = no 2 = main
int choosemenu(){
    char choice;
    scanf(" %c",choice);
    if(isupper(choice)){
        choice = tolower(choice);
    }
    if(choice == 'y'){
        printf("GREAT!");
        return 1;
    }
    if(choice == 'n'){
        
        return 0;
    }
    if (choice == 'm'){
        printf(" back to menu.\n");
        return 2;
    }
    if(choice == 'e'){
        printf("Exiting...\n");
        exit(1);
    }
}
//clear screen
void clearScreen() {
    
    //check if windows
#ifdef _WIN32
//clear in windows
    system("cls"); 
#else 
//clear in other
    system("clear"); 
#endif
}
//validate id
int validateID(const char *id) {
    //check if id is 14 digita
    if (strlen(id) != 14) {
        return 0; 
    }
    for (int i = 0; i < 14; i++) {
        if (!isdigit(id[i])) {
            return 0; 
        }
    }

    return 1; 
}
//count number of words
int countwords(char *c){
    int  i = 0, w = 0; 
    
    while(*c){
        if(isspace(*c)){
            w = 0;
        }
        else{
            if(w == 0){
                i++;
                w = 1;
            }
            }
         c++;
    }
    return i;
}
//check if name is valide
int validateName (char *name){
    //only 2 words
    if (countwords(name) !=2){
        return 0;
    }
    int i = 0 ;
    while(name[i]!='\0'){
        // no numbers or characters
        if(!isalpha(name[i]) && name[i]!=' '){
            return 0;
        }
        i++;
    }
    return 1;
}
//chack if email is correct
int validateEmail(char *email){
    //if email exists
    if(email == NULL){
        return 0;
    }
   
    //pointer to @
    char* at = strchr(email,'@');
    //pointer to . 
    char* dot = strchr(email,'.');
    
    // if an @ exists not in the start and end of email
    //and dot exists not directly before or after and not at the end of email or 
    // at the start of the email
    if(at == NULL || at == email || at == (email + strlen(email)-1)||dot == at-1 ||dot == at+1 || dot == (email +strlen(email)-1)||dot == email){
        return 0;
    }
    //no multiple @
    if(strchr(at+1,'@') != NULL){
        return 0;
    }
    //atleast 3 characters before @
    if (at - email < 3){
        return 0;
    }
    dot = strchr(at+1,'.');
    //dot exists after the @
    if(dot == NULL){
        return 0;
    }
    //stleast 3 characters after the @
    
    if (email +strlen(email) - dot-1 < 3){
    
        return 0 ;
    }
    char *space = strchr(email,' ');
    //no space in email
    if(space != NULL){
        return 0;
        }

    //copy all characters after the @
    //copy after pointer and allocate memory and give pointer to memory
    char* domain = strdup(at + 1);
    //printf("%s",domain);
    if (domain == NULL){
        printf("pointer failed");
    }
     for (int i = 0 ; i < strlen(domain)-1;i++){
        if(isupper(domain[i])){
            domain[i] = tolower(domain[i]);
            
        }
    }
    
    if(domain[strlen(domain)-1]=='\n'||domain[strlen(domain)-1]==' '){
        domain[strlen(domain) - 1] = '\0';
    }
    
   
    for(int i = 0 ; i < sizeof(domains) / sizeof(domains[0]) ; i++){
        
        if(strcmp(domain,domains[i]) == 0){
            free(domain);
            return 1;

        }
     
    }
    printf("%s is not a supported Domain \n",domain);
    free (domain);
    return 0;

    
}
//validate phone number
int validateMobile(char* mobileNumber){
    // remove last whitespace character 
    if(mobileNumber[12]==' '||mobileNumber[12]=='\n'){
        mobileNumber[12] = '\0';
    }
    //chack length of phone number
    if(strlen(mobileNumber)!=11){
        return 0;
    }
    //check if first digit is 0
    else if(mobileNumber[0] != '0'){
        return 0;
    }
    //no spaces in phone number
    char *space = strchr(mobileNumber,' ');
    if(space != NULL){
        return 0;
    }
    //only digits
    for (int i = 0 ; i < 11 ; i ++ ){
        if(!isdigit(mobileNumber[i])){
            return 0;
        }
    }
    char firstdigits [4];
    //copy first 3 digits of phone number into an array
    strncpy(firstdigits,mobileNumber,3);
    
    //end array 
    firstdigits[3] = '\0';
    for(int i = 0 ;i<3;i++){
       if(strcmp(firstdigits,phoneCompany[i]) == 0){
        return 1;
       }
    }
    return 0;
}
//validate date 
int validateDate (char reserveDate[], date* destination){
    //remove whitespace character
    //search for location of white space character and remove it
    reserveDate[strcspn(reserveDate, "\n")] = '\0';
    //check format
    if(strlen(reserveDate)!=10 || reserveDate[2]!='/'||reserveDate[5]!='/'){
        printf("DATE WRONG FORMAT (dd/mm/yyyy)\n");
        return 0;
    }
   
    //devide date into partition (day,month,year)
    
    char *ptr = strtok(reserveDate,"/");
     if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int day = atoi(ptr);
    ptr = strtok(NULL,"/");
    if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int month = atoi(ptr);
    ptr = strtok(NULL,"/");
    if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int year = atoi(ptr);

    //check if date is valid
    int leap = 0;
    
    
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
        leap = 1;
    }
    else if(month>12 || month<1){
         printf("wrong month %d\n",month);
        return 0;
        }
    else if( day>31 || day<1 ||(day>28 && month == 2 && leap == 1)||(day == 29 && month == 2 && leap == 0)){
        printf("wrong day %d\n",day);
        return 0;
     }
    
    
    //get time now
    time_t t = time(NULL);

    struct tm *now = localtime(&t);
    int currentDay = now->tm_mday;
    int currentMonth = now->tm_mon + 1;
    int currentYear = now->tm_year + 1900; // counts years after 1900
    

    
    //check if date is in the future
    if(currentYear>year || (currentYear == year && currentMonth>month) || (currentYear == year && currentMonth == month && currentDay>day)){
        printf("date must be in the future \n");
        return 0 ;

    }
    if(year-currentYear>5){
        printf("date is too far in the future \n");
        return 0 ;
    }
    destination->day = day;
    destination->month = month;
    destination->year = year;

    
    
    
return 1;
    

}
//check if room category is correct
int validateRoomCategory(char category[]){
    category[strcspn(category, "\n")] = '\0';

    if(strchr(category,' ')!= NULL){
        printf("invalid category\n");
        return 0 ;
    }


for(int i = 0 ; i < 3;i++){
    if(strcmp(category,categories[i])==0){
        return 1;
    }
}
printf("choose a correct category CASE SENSITIVE\n");
return 0 ;
}
//check if number of nights is correct
int validateNightNum(char num[]){
    num[strcspn(num, "\n")] = '\0';
    if(strchr(num,' ')!= NULL){
        printf("invalid number\n");
        return 0 ;
        }
        int i = 0;
        while(num[i]!='\0'){
            if(!isdigit(num[i])){
                printf("invalid number\n");
                return 0 ;
            }
            i++;
        }
        return 1 ;

}
//number of lines in file
int countlines(FILE* file){
    if (file == NULL) {
        printf("Could not open file\n");
        return 0;
        }
        char line[100];
        //get number of lines in file
        int count = 0;
        while (!feof(file)){
            char c = fgetc(file);
            if (c == '\n'){
            count++;}
        }
        rewind(file); //reset pointer to start of file
        return count+1;
        

}
//load room file
void LoadRooms(FILE *file,Room *rooms){
        int i = 0 ;
        char line[100];
        
        while (fgets(line, sizeof(line), file) != NULL) {
            //room number
            line[strcspn(line, "\n")] = '\0';
              if(line == NULL){
                continue;
            }
            char *ptr = strtok(line, " ");
            if(ptr == NULL){
                printf("error in pointer-12");
                return ;
            } 
            rooms[i].number = atoi(ptr);
            //room status
            ptr = strtok(NULL, " ");
            if(ptr == NULL){
                printf("error in pointer-11");
                return ;
                }
                strncpy(rooms[i].status,ptr,sizeof(rooms[i].status)-1) ;
                rooms[i].status[sizeof( rooms[i].status) - 1] = '\0';
            
            //categery
            ptr = strtok(NULL, " ");
            if(ptr == NULL){
                printf("error in pointer-10");
                return ;
                }
                strncpy(rooms[i].roomCategory,ptr,sizeof(rooms[i].roomCategory)-1) ;
                rooms[i].roomCategory[sizeof( rooms[i].roomCategory) - 1] = '\0';
           
            //room price
            ptr = strtok(NULL, " ");
            if(ptr == NULL){
                printf("error in pointer-9");
                return ;
                }
                rooms[i].price = atoi(ptr);
            i++;
            }
            
}
//load reservation file into struct
void LoadresRooms(FILE *file,reservation *r,int lines){
        int i = 0 ;
        char *line = malloc(lines*(sizeof(reservation)-1));
        while (fgets(line, sizeof(line), file) != NULL && i<lines) {
            //ID
            line[strcspn(line, "\n")] = '\0';
            if(line == NULL){
                continue;
            }
            char *ptr = strtok(line, ",");
            if(ptr == NULL){
                printf("error in pointer-8");
                
            } 
            strncpy(r[i].reservationID,ptr,sizeof(r[i].reservationID)-1) ;
            r[i].reservationID[sizeof( r[i].reservationID) - 1] = '\0';
            //room number
            ptr = strtok(NULL, ",");
            if(ptr == NULL){
                printf("error in pointer-7");
                
                }
                strncpy(r[i].roomNum,ptr,sizeof(r[i].roomNum)-1) ;
                r[i].roomNum[sizeof( r[i].roomNum) - 1] = '\0';            
            //status
            ptr = strtok(NULL, ",");
            if(ptr == NULL){
                printf("error in pointer-6");
                
                }
                strncpy(r[i].reserveStatus,ptr,sizeof(r[i].reserveStatus)-1) ;
                r[i].reserveStatus[sizeof( r[i].reserveStatus) - 1] = '\0';            
            //name
            ptr = strtok(NULL, ",");
            if(ptr == NULL){
                printf("error in pointer-5");
                
                }
                strncpy(r[i].custName,ptr,sizeof(r[i].custName)-1) ;
                 r[i].custName[sizeof( r[i].custName) - 1] = '\0';
            //national id
            ptr = strtok(NULL, ",");
            if(ptr == NULL){
                printf("error in pointer-4");
                
                }
                strncpy(r[i].nationalId,ptr,sizeof(r[i].nationalId)-1) ;
                r[i].nationalId[sizeof( r[i].nationalId) - 1] = '\0';
                //number of nights
                ptr = strtok(NULL, ",");
                if(ptr == NULL){
                    printf("error in pointer-3");
                   
                    }
                    strncpy(r[i].nightNum ,ptr,sizeof(r[i].nightNum)-1) ;
                    r[i].nightNum[sizeof( r[i].nightNum) - 1] = '\0';
               
                //check in date
                ptr = strtok(NULL, ",");
                if(ptr == NULL){
                    printf("error in pointer-2");
                    
                    }
                char date[30];
                strcpy(date,ptr);
                ptr = strtok(NULL, ",");
                if (ptr == NULL) {
                    printf("Error in pointer-1\n");
                }
                  strncpy(r[i].email,ptr,sizeof(r[i].email)-1) ;
                  r[i].email[sizeof( r[i].email) - 1] = '\0';
                    
                      
                    //phone number
                    ptr = strtok(NULL, "");
                    if(ptr == NULL){
                        printf("error in pointer0");
                        }
                    strncpy(r[i].mobileNum, ptr,sizeof(r[i].mobileNum)-1) ;
                    r[i].mobileNum[sizeof(r[i].mobileNum) - 1] ='\0';
                char *tok = strtok(date,"-");
                
                if(tok == NULL){
                    printf("Error in pointer1");
                   
                } 
                int day = atoi(tok);
            
                tok = strtok(NULL,"-");
                if(tok == NULL){
                    printf("Error in pointer2");
                   
                }
                int month = atoi(tok);
                tok = strtok(NULL,"-");
                if(tok == NULL){
                    printf("Error in pointer3");
                    
                }
                int year = atoi(tok); 
                r[i].checkIn.day = day;
                r[i].checkIn.month = month;
                r[i].checkIn.year = year;
            
            i++; 
            
            }
            
} 
//check if room number exists
int validateRoomnum(char NUM[]){
    //int roomnum = atoi(NUM);
    FILE* fptr = fopen("Room.txt","r");
    int lines = countlines(fptr);
    Room* rooms = malloc(lines*sizeof(Room));
    LoadRooms(fptr,rooms);
    fclose(fptr);
    if(findRoom(rooms,NUM,lines)==-1){
        printf("Room number is not available or incorrect\n");
        return 0;
    }
    else{
        return 1;
    }
} 
// enter data and validate into struct
void enterData(reservation* i){
     

   printf("To reserve a room please enter your first and last name:(maximum 100 characters) ");
    fgets(i->custName,sizeof(i->custName),stdin);
    i->custName[strcspn(i->custName, "\n")] = '\0';
    while(!validateName(i->custName)){
        printf("Wrong input please enter your first and last name:(maximum 100 characters) ");
        fgets(i->custName,99,stdin);
        i->custName[strcspn(i->custName, "\n")] = '\0';
} 

    printf("please Enter ur national ID: 14 digits");
    fgets(i->nationalId,15,stdin);
    i->nationalId[strcspn(i->nationalId, "\n")] = '\0';
    //wrong id
    while(!validateID(i->nationalId)){
       
        printf("Wrong ID Please try again: 14 digits");
        getchar();
        fgets(i->nationalId,15,stdin);
        i->nationalId[strcspn(i->nationalId, "\n")] = '\0';
        
    }
    i->nationalId[14]='\0';
    printf("please Enter your email: ");
    getchar();
    fgets(i->email,99,stdin);
    i->email[strcspn(i->email, "\n")] = '\0';
    while(!validateEmail(i->email)){
        printf("Wrong email Please try again:");
        fgets(i->email,99,stdin);
        i->email[strcspn(i->email, "\n")] = '\0';
    }
    //

   
    
     printf("please Enter your mobile number: ");
    fgets(i->mobileNum,12,stdin);
     i->mobileNum[strcspn(i->mobileNum, "\n")] = '\0';
    while(!validateMobile(i->mobileNum)){
        //getchar();
        printf("Wrong mobile number Please try again:");
        fgets(i->mobileNum,12,stdin);
         i->mobileNum[strcspn(i->mobileNum, "\n")] = '\0';
    }
    printf("Enter Date of Reservation: (dd/mm/yyyy) ");
    
    char reserveDate[11];
    getchar(); 
    fgets(reserveDate,sizeof(reserveDate),stdin);
    while(!validateDate(reserveDate,&i->checkIn)){
        getchar();
        printf("Wrong date Please try again:");
        
        fgets(reserveDate,sizeof(reserveDate),stdin);
    } 
    printf("Enter Number of Nights: ");
    scanf(" %s",&i->nightNum);
    while(!validateNightNum(i->nightNum)){
        printf("Wrong number of nights Please try again:");
        //getchar();
        scanf(" %s",&i->nightNum);
        

    }
    getchar(); 
    printf("CASE SENSITIVE\n");
    printf("choose a Room category:(SeaView,LakeView,GardenView) ");
    fgets(i->RoomCategory,11,stdin);
    while (!validateRoomCategory(i->RoomCategory)){
        printf("Wrong room category Please try again: (SeaView,LakeView,GardenView) ");
       
        fgets(i->RoomCategory,11,stdin);
}
//getchar();
 
}

//  print data to confirm
void printReservation(reservation* customer){
    printf("\n");
    //clearScreen();
    printf("Customer Name: %s\n",customer->custName);
    printf("National ID: %s\n",customer->nationalId);
    printf("Customer Email: %s\n",customer->email);
    printf("Customer Phone Number: %s\n",customer->mobileNum);
    printf("Number of Nights: %s\n",customer->nightNum);
    //printf("Room Category: %s\n",customer->roomNum);
    printf("Room Category: %s\n",customer->RoomCategory);
    printf("Reservation Date = %d/%d/%d\n",customer->checkIn.day,customer->checkIn.month,customer->checkIn.year);

}
//display rooms available in category
int showroom(Room* rooms , char* category,int count){
    printf("\n");
    clearScreen(); 
    int f = 0;
    printf("\t Available Rooms\n");
    for (int i = 0;i<count;i++){
    if(strcmp(rooms[i].roomCategory,category)==0){
        if(strcmp(rooms[i].status,"Available")==0){
            printf("Room number = %d\tPrice =  %d\n",rooms[i].number,rooms[i].price);
            f = 1;}
}  }
int flag = 0;
while (f == 0){
    printf("No rooms available in that category please choose another\n");
    printf("CASE SENSITIVE\n");
    printf("choose a Room category:(SeaView,LakeView,GardenView) ");
    getchar();
    fgets(category,11,stdin);
    while (!validateRoomCategory(category)){
        printf("Wrong room category Please try again: (SeaView,LakeView,GardenView) ");
        fgets(category,11,stdin);
}
   printf("\t    Available Rooms\n");
    for (int i = 0;i<count;i++){
    if(strcmp(rooms[i].roomCategory,category)==0){
         
        if(strcmp(rooms[i].status,"Available")==0){
            printf("Room number = %d\tPrice =  %d\n",rooms[i].number,rooms[i].price);
            f = 1;}
            else{
            flag+=1;}
            //if all choices go back to main
            if(flag == 3){
                printf("NO ROOMS AVAILABLE \n");
               return 0;
            }
}  }
}

}
// choose Room From the Available rooms
int chooseRoom (char roomNum[],Room* rooms,int count,reservation* customer){

    int flag = 0;
    char number[5];
    //sprintf(number,"%d",rooms[i].number);
    for (int i = 0;i<count;i++){
        sprintf(number,"%d",rooms[i].number);
        if(!strcmp(number,roomNum)){
            strcpy(rooms[i].status,"Reserved");
            strcpy(customer->roomNum , number );
            flag = 1;
            }
            }

            return flag;
            


}
//save room in file
void saveRooms(FILE* file,Room * rooms,int count){
    for (int i = 0;i<count;i++){
        fprintf(file,"%d %s %s %d",rooms[i].number,
        rooms[i].status,rooms[i].roomCategory,rooms[i].price);
        
        if(i!=count-1){
            fprintf(file,"\n");
        }}
}
//generate random id
void randomID(const char randomcharacter[],char*str , int num){
    int lengthRC = 10; //size of array of random array
    //intial value to start with in the pseudorandom generator
    //seed so that rand() doesn't give the same value each time
    //seed is the current time bcs time changes every second
    srand(time(NULL));
    for (int i = 0;i<num;i++){
        //rand gets a random number them by using mod the number produced is less than length of rc
        str[i] = randomcharacter[(rand()%lengthRC)];//gets a random character from the array
    }
}
//check if random id already exists
int validaterandomID(char * str,int line,reservation *all ){
    
    int flag = 0;
    for (int i = 0;i<line;i++){
        if (strcmp(str,all[i].reservationID)==0){
            flag = 1;
            break;
        }
    }
    return flag;

}
//load customer in file 
void writeCustomer(FILE* file,reservation*all){
 
    fprintf(file,"%s,",all->reservationID);
    fprintf(file,"%s,",all->roomNum);
    fprintf(file,"%s,",all->reserveStatus);
    fprintf(file,"%s,",all->custName);
    //printf("%s",all->nationalId);
    fprintf(file,"%s,",all->nationalId);
    fprintf(file,"%s,",all->nightNum);
    fprintf(file,"%d-%d-%d,",all->checkIn.day,all->checkIn.month,all->checkIn.year);
    fprintf(file,"%s,",all->email);
    fprintf(file,"%s",all->mobileNum);
    

   
}
// main reservation function
void reserve(reservation* customer){
//enter custumer data
while(1){
enterData(customer);
//print the reservation data
printReservation(customer);
//check if data is correct
printf("is the data correct if no u will be prompted to enter the data again \n");
printf("yes/no/return to menu/exit program(y/n/m/e)");
char choice;
scanf(" %c",&choice);
// try again
if(choice == 'n'){
    printf("Enter the data again:\n");
    continue;
}
//exit while
else if (choice == 'y'){
    printf("GREAT!\n");
    break;
}
if (choice == 'm'){
    return;
}
if(choice == 'e'){
    exit(1);
}
else{
    printf("please choose y/n/m/e");
}
}
//open room
FILE *file = fopen("Room.txt", "r");

if(file == NULL){
    printf("file not found");
    exit(1);
    }
//count the lines in room
int count  = countlines(file);
//allocate memory
Room* rooms = malloc(count*sizeof(Room));
//memory allocation failed
if(rooms == NULL){
    printf("Memory not allocated\n");
    fclose(file);
   return;
    }
    //load into struct
LoadRooms(file,rooms);
fclose(file); 
//open reservation
file = fopen("Reservation.txt", "r"); 
if(file == NULL){
    printf("file not found");
    exit(1);
    }


//show rooms

showroom(rooms,customer->RoomCategory,count);

char choice[5];
printf("Enter number of the room of your choice: ");
scanf(" %s",&choice);
//check if choice is valid
while(!chooseRoom(choice,rooms,count,customer)){

    printf("Invalid choice, please choose a valid room number \n");
    printf("Enter number of the room of your choice: ");
    scanf(" %s",&choice);
}
//write in file
file = fopen("Room.txt", "w");
//check if file is open
if(file == NULL){
    printf("file not found");
    exit(1);
    }
    // save rooms
    saveRooms(file,rooms,count);
    fclose(file); 
    //open reservation
file = fopen("Reservation.txt","r");
if(file == NULL){
    printf("file not found");
    return;
}
//count lines
int line = countlines(file);
fclose(file);
//allocate memory
reservation *all = malloc(line*sizeof(reservation));
load(all);

//generate random id
randomID(randomcharacter,customer->reservationID,7);
//validate random id
while(validaterandomID(customer->reservationID,line,all)){
    printf("ID already exist\n");
    randomID(randomcharacter,customer->reservationID,7);

}
free(all);
printf("Your Reservation ID is %s please remeber it for later use\n",customer->reservationID);
//status is unconfirmed
strncpy(customer->reserveStatus,"unconfirmed",sizeof(customer->reserveStatus));
//end the string
customer->reserveStatus[sizeof(customer->reserveStatus)-1] = '\0';
//append data
    file = fopen("Reservation.txt","a+");
    fseek(file,0,SEEK_END); // making sure
    if(file == NULL){
        printf("Could not open file\n");
        return;
        }
        if (ftell(file) != 0) { // Check if the file is not empty
        fprintf(file, "\n");
    } 
    //write new costumer in file
writeCustomer(file,customer);

free(rooms);
}
// change data in reservation
void changeReservation(){

    char idNum[8];
    printf("Enter your reservation ID or Room number: ");
    scanf("%s",idNum);
    FILE *res = fopen("Reservation.txt","r"); //reservation
    int lines = countlines(res); //lines in reservation
    fclose(res);
    reservation *all = malloc(lines*sizeof(reservation)); //all people
    load(all);
    
while(1){
    int i;
    int flag = 0;
    // find the line where reservation exits
    for(i=0;i<lines;i++){
        // compare id
        if(strcmp(all[i].reservationID,idNum)==0){
            flag = 1;
            break;}
            //compare room number
        else if(!strcmp(all[i].roomNum,idNum)){
            flag = 1;
            break;}
 
    }

    //doesn't exist
    if(flag == 0){
        printf("No reservation found\nwould u like to try again(y/n/m/e)");
        char choice;
        scanf(" %c",&choice);
        if(choice == 'y'){
            continue;
        }
        else if(choice == 'n'){
            break;
        }
        else if (choice == 'm'){
            return;
        }
        else if(choice == 'e'){
            exit(1);
        }

        
    }
    //found
    else{
        FILE* Rooms = fopen("Room.txt","r");
        
        int count = countlines(Rooms);//lines in Rooms
        Room* rooms = malloc(count*sizeof(Room)); // all rooms
        LoadRooms(Rooms,rooms);
        fclose(Rooms);

    
    
        
        
        // change name
        while(1){
            int x =0;
            char confirm;
            fflush(stdin);
        printf("1. Change Name\n");
        
        while(!x){     
            printf("Current Name: %s\n",all[i].custName);
            printf("Do you want to change Reservation name: \nyes/no/return to menu/exit program(y/n/m/e)");  
            scanf(" %c",&confirm);
        if(confirm == 'y'){
            printf("Enter new name: ");
            getchar();
            fgets(all[i].custName,99,stdin);
            all[i].custName[strcspn(all[i].custName, "\n")] = '\0';
            while (!validateName(all[i].custName))
            {
                printf("Invalid name. Please enter a valid name.\n");
                printf("Enter new name: ");
                getchar();
                fgets(all[i].custName,99,stdin);
                all[i].custName[strcspn(all[i].custName, "\n")] = '\0';


                        }
            
            x =1;
        }
        else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
            printf("Invalid choice\n");
             x = 0;
                continue;
        }    
        else if(confirm == 'n'){
            x = 1;

        }
        else if(confirm == 'm'){
            
            return;
        }
        else if(confirm == 'e'){
            exit(1);
        }}
        //change phone
        
        x = 0;
        printf("2. Change Phone Number\n");

        
        //phone number
        while ((!x))
        {
       
        printf("Current phone number: %s \n",all[i].mobileNum);
        printf("Do you want to change Reservation phone number: \nyes/no/return to menu/exit program(y/n/m/e)");
        scanf(" %c",&confirm);
        getchar();
        if(confirm == 'y'){
            printf("Enter new phone number: ");
            fgets(all[i].mobileNum,12,stdin);
            all[i].mobileNum[strcspn(all[i].mobileNum, "\n")] ='\0';
            while (!validateMobile(all[i].mobileNum)){
                printf("Invalid phone number. Please enter a valid phone number.\n");
                printf("Enter new phone number: ");
                fgets(all[i].mobileNum,12,stdin);
                all[i].mobileNum[strcspn(all[i].mobileNum, "\n")] ='\0';
                

            }
            x =1;
            }
            else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
                printf("Invalid choice\n");
                x = 0;
                continue;
                }
                else if(confirm == 'n'){
            x = 1;

        }
        else if(confirm == 'm'){
            
            return;
        }
        else if(confirm == 'e'){
            exit(1);
        }
        }
        x = 0;

        //change email
        printf("3. Change Email\n");
        while(!x){
            printf("Current email: %s \n",all[i].email);
            printf("Do you want to change Reservation email: \nyes/no/return to menu/exit program(y/n/m/e) ");
            scanf(" %c",&confirm);
        if(confirm == 'y'){
            getchar();
            printf("Enter new email: ");
            fgets(all[i].email,99,stdin);
            all[i].email[strcspn(all[i].email, "\n")] ='\0';
            while (!validateEmail(all[i].email)){

                printf("Invalid email. Please enter a valid email.\n");
                printf("Enter new email: ");
                fgets(all[i].email,99,stdin);
                all[i].email[strcspn(all[i].email, "\n")] ='\0';
                
                }

            x =1;
            }
             else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
                printf("Invalid choice\n");
                x = 0;
                continue;
                } 
                else if(confirm == 'n'){
            x = 1;

        }
        else if(confirm == 'm'){
            
            return;
        }
        else if(confirm == 'e'){
            exit(1);
        }
                }
            //room category
            x = 0;
        printf("4. Change Room Category\n");
        //int roomnumber = atoi(all[i].roomNum);
        //using room number find category
        int roomlocation = findRoom(rooms,all[i].roomNum,count);
        if(roomlocation == -1){
            printf("room not found");
            exit(1);
            }

        
        
        while(!x){
            printf("Current room category: %s \n",rooms[roomlocation].roomCategory);
        printf("Do you want to change Reservation room category: \nyes/no/return to menu/exit program(y/n/m/e)");
        scanf(" %c",&confirm);
        if(confirm == 'y'){
            printf("CASE SENSITIVE\n");
            printf("Enter new room category Please enter one of the following: SeaView,LakeView,GardenView ");
            //char room[20];
            getchar();
            fgets(all[i].RoomCategory,19,stdin);
            all[i].RoomCategory[strcspn(all[i].RoomCategory, "\n")] ='\0';
            while(!validateRoomCategory(all[i].RoomCategory)){
                printf("CASE SENSITIVE\n");
                printf("Invalid room category. Please enter one of the following: SeaView,LakeView,GardenView");
                fgets(all[i].RoomCategory,19,stdin);
                all[i].RoomCategory[strcspn(all[i].RoomCategory, "\n")] ='\0';

            }
            //change room status to available
            strcpy(rooms[roomlocation].status , "Available");
            //show available rooms
            showroom(rooms,all[i].RoomCategory,count);
            char choice[5];
            printf("Enter number of the room of your choice: ");
            scanf(" %s",&choice);
            while(!chooseRoom(choice,rooms,count,&all[i])){
                
                printf("Invalid choice, please choose a valid room number\n");
                printf("Enter number of the room of your choice: ");
                scanf(" %s",&choice);

            }
            
            x = 1;
            }
             else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
                printf("Invalid choice\n");
                x = 0;
                continue;
                }
                else if (confirm == 'n'){
                    x = 1;
                }
                else if(confirm == 'm'){
            
            return;
        }
        else if(confirm == 'e'){
            exit(1);
        }}
                x = 0;
                // number of lines
        printf("5. Change Number of Nights\n");
        while (!x){
            printf("Current number of nights :%s\n",all[i].nightNum);
             printf("Do you want to change Reservation number of nights: \nyes/no/return to menu/exit program(y/n/m/e)");
        scanf(" %c",&confirm);
        if(confirm == 'y'){
            
            printf("Enter new number of nights: ");
           
            scanf(" %s",&all[i].nightNum);
            while(!validateNightNum(all[i].nightNum)){
                printf("Invalid number of nights\n");
                printf("Enter new number of nights: ");
                scanf(" %s",&all[i].nightNum);
            }
            x = 1;}
            else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
                printf("Invalid choice\n");
                x = 0;
                continue;
                }
                else if(confirm == 'n'){
            x = 1;

        }
        else if(confirm == 'm'){
            
            return;
        }
        else if(confirm == 'e'){
            exit(1);
        }
        }
        x = 0;
        //date
        printf("6. Change Date\n");
        
        while (!x)
        {
            printf("Current Date = %d/%d/%d\n",all[i].checkIn.day,all[i].checkIn.month,all[i].checkIn.year);
        printf("Do you want to change Reservation date: \nyes/no/return to menu/exit program(y/n/m/e)");
            scanf(" %c",&confirm);
            if(confirm == 'y'){
                printf("Enter new date: (dd/mm/yyyy)");
                char resdate [11];
                getchar();
                fgets(resdate,11,stdin);
                resdate[strcspn(resdate, "\n")] ='\0';
                printf("%s ",resdate);
                while(!validateDate(resdate,&all[i].checkIn)){
                    printf("Invalid date. Please enter a valid date (dd/mm/yyyy): ");
                    getchar();
                    fgets(resdate,11,stdin);
                    resdate[strcspn(resdate, "\n")] ='\0';

                }
                x =1;
                }
                else if (confirm !='y' && confirm!='n'&&confirm!='m'&&confirm!='e'){
                    printf("Invalid choice\n");
                    x = 0;
                continue;
                    }
                    else if(confirm == 'n'){
            x = 1;

        }
        else if(confirm == 'm'){
            
            return;
        }
        else if(confirm == 'e'){
            exit(1);
        }
        break;
}
//print reservation
        printf("New Details");
        printReservation(&all[i]);
printf("is the data correct if no u will be prompted to enter the data again \n");
printf("y/n/m/e: ");
char finalconfirm;
scanf(" %c",&finalconfirm);
while(finalconfirm !='n'&&finalconfirm !='y'&&finalconfirm !='m'&&finalconfirm !='e'){
    printf("Invalid choice\n");
    printf("y/n/m/e: ");
    scanf(" %c",&finalconfirm);
}
if(finalconfirm == 'n'){
    printf("Enter the data again:\n");
    getchar();
    continue;
}
if(finalconfirm == 'm'){
   return;
}
if(finalconfirm == 'e'){
    exit(1);
}
else if (finalconfirm == 'y'){
    printf("GREAT!\n");
    break;
    }
     
        }
      
        //save rooms 
        Rooms = fopen("Room.txt","w");
         saveRooms(Rooms,rooms,count);
         fclose(Rooms);
         res = fopen("Reservation.txt","w");
         for(int z = 0;z<lines;z++){
            //save customers
         writeCustomer(res,&all[z]);
         if(z!=(lines-1)){
            fprintf(res,"\n");
         }}

         fclose(res);
    }
}}
//validate search by date
int validateSearchDate (char reserveDate[], date* destination){
    //remove whitespace character
    //search for location of white space character and remove it
    reserveDate[strcspn(reserveDate, "\n")] = '\0';
    //check format
    if(strlen(reserveDate)!=10 || reserveDate[2]!='/'||reserveDate[5]!='/'){
        printf("DATE WRONG FORMAT (dd/mm/yyyy)\n");
        return 0;
    }
   
    //devide date into partition (day,month,year)
    
    char *ptr = strtok(reserveDate,"/");
     if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int day = atoi(ptr);
    ptr = strtok(NULL,"/");
    if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int month = atoi(ptr);
     if(month>12 || month<1){
         printf("wrong month %d\n",month);
        return 0;
        }
    ptr = strtok(NULL,"/");
    if(ptr == NULL){
        printf("Error in pointer");
        return 0;
    }
    int year = atoi(ptr);

    //check if date is valid
    int leap = 0;
    
    
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
        leap = 1;
    }
   
    else if( day>31 || day<1 ||(day>28 && month == 2 && leap == 1)||(day == 29 && month == 2 && leap == 0)){
        printf("wrong day %d\n",day);
        return 0;
     }
    
    
        destination->day = day;
        destination->month = month;
        destination->year = year;


    
    
    
return 1;
    

}
//print all customers that have the date
void printbydate(){
    int x = 1;
    char searchDate[11];
    date search;
    while(x){
    printf("\n");
    clearScreen();
    getchar();
    printf("Please enter the date:(dd/mm/yyyy) ");
    fgets(searchDate,sizeof(searchDate),stdin);
    while(!validateSearchDate(searchDate,&search)){
        
        printf("Wrong date Please try again:");
        fgets(searchDate,sizeof(searchDate),stdin);
        
        //printf("%s\n",searchDate);
        
    }
    clearScreen();
    printf("\n");
    while (1)
        {
            char confirm;
            printf("Date you entered= %d/%d/%d\n",search.day,search.month,search.year);
        printf("is it correct (yes =y,n = no enter date agin , m = return to main , e = close code): (y/n/m/e)");
            scanf(" %c",&confirm);
            //getchar();
            if(confirm == 'y'){
             printf("GREAT!");
             x= 0;
             break;}
                //x =1;
                
                else if (confirm !='y' && confirm!='n'&& confirm!='m'&& confirm!='e'){
                    printf("Invalid choice\n");
                    x =1;
                continue;
                    }
                    else if(confirm == 'n'){
            x = 1;
            break;

        }
        else if(confirm == 'm'){
            
            return;
        }
        else if(confirm == 'e'){
            exit(1);
        }
        
} }
    //printf("\n");
    //clearScreen();
    int flag  = 0;
    FILE *fptr = fopen("Reservation.txt","r");
    if(fptr == NULL){
        printf("Could not open file\n");
        return ;
    }
    int lines = countlines(fptr);
    //printf("lines = %d",lines);
    fclose(fptr);
    reservation* reservations = malloc(lines * sizeof(reservation));
    load(reservations);
    fptr = fopen("Room.txt","r");
    if(fptr == NULL){
        printf("Could not open file\n");
        getchar();
        return ;
        }
    int roomlines = countlines(fptr);
    Room *rooms = malloc(roomlines*(sizeof(Room)));
    LoadRooms(fptr,rooms);
    fclose(fptr);
   
    clearScreen();
    printf("\n");
    for(int i = 0; i < lines; i++){
        if((search.day == reservations[i].checkIn.day)&&(search.month == reservations[i].checkIn.month)&&(search.year == reservations[i].checkIn.year)){
        int room = findRoom(rooms,reservations[i].roomNum,roomlines);
        strcpy(reservations[i].RoomCategory,rooms[room].roomCategory);
        printReservation(&reservations[i]);
        printf("\n\t***************************************************\t\n");
        flag = 1;
       
        }
   
}
      if(flag == 0){
            printf("No reservations found for the given date\n");
         }
   //getchar(); 
return;
}
//not good
void start(){
    //getchar();
     
    while(1){
    char choose;
    
    printf("Please choose an option:\n");
    printf("enter r for reservation and c for changing reservaton and d for searching by date and e to exit program: ");
    scanf(" %c",&choose);
    if(choose == 'r'){
        getchar();
        reservation* customer = malloc(sizeof(reservation));
        reserve(customer);
        free(customer); 
    }
    if(choose == 'c'){
        changeReservation();
    }
     if(choose == 'd'){
        printbydate();
    }
    if(choose == 'e'){
    return ;}
    if(choose != 'e' && choose != 'c'&&choose != 'r'){
        printf("Invalid choice try again\n");
    }
}
}
