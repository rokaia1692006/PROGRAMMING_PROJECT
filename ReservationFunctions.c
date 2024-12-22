#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include "reservation.h"
#include <time.h>
#include <stdlib.h>
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
    else if( day>31 || day<1 ||(day>28 && month == 2 && leap == 1)||(day == 29 && month == 2 && leap == 0)){
        printf("wrong day %d\n",day);
        return 0;
     }
    
    else if(month>12 || month<1){
         printf("wrong month %d\n",month);
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
void LoadresRooms(FILE *file,reservationInfo *Reserve,int lines){
        int i = 0 ;
        char line[200];
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
            strncpy(Reserve[i].ID,ptr,sizeof(Reserve[i].ID)-1) ;
            Reserve[i].ID[sizeof( Reserve[i].ID) - 1] = '\0';
            //room number
            ptr = strtok(NULL, ",");
            if(ptr == NULL){
                printf("error in pointer-7");
                
                }
                Reserve[i].roomNum=atoi(ptr) ;            
            //status
            ptr = strtok(NULL, ",");
            if(ptr == NULL){
                printf("error in pointer-6");
                
                }
                strncpy(Reserve[i].status,ptr,sizeof(Reserve[i].status)-1) ;
                Reserve[i].status[sizeof( Reserve[i].status) - 1] = '\0';            
            //name
            ptr = strtok(NULL, ",");
            if(ptr == NULL){
                printf("error in pointer-5");
                
                }
                strncpy(Reserve[i].customerName,ptr,sizeof(Reserve[i].customerName)-1) ;
                 Reserve[i].customerName[sizeof( Reserve[i].customerName) - 1] = '\0';
            //national id
            ptr = strtok(NULL, ",");
            if(ptr == NULL){
                printf("error in pointer-4");
                
                }
                strncpy(Reserve[i].nationalID,ptr,sizeof(Reserve[i].nationalID)-1) ;
                Reserve[i].nationalID[sizeof( Reserve[i].nationalID) - 1] = '\0';
                //number of nights
                ptr = strtok(NULL, ",");
                if(ptr == NULL){
                    printf("error in pointer-3");
                   
                    }
                    Reserve[i].numberNights = atoi(ptr) ;
               
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
                  strncpy(Reserve[i].email,ptr,sizeof(Reserve[i].email)-1) ;
                  Reserve[i].email[sizeof( Reserve[i].email) - 1] = '\0';
                    
                      
                    //phone number
                    ptr = strtok(NULL, "");
                    if(ptr == NULL){
                        printf("error in pointer0");
                        }
                    strncpy(Reserve[i].phoneNum, ptr,sizeof(Reserve[i].phoneNum)-1) ;
                    Reserve[i].phoneNum[sizeof(Reserve[i].phoneNum) - 1] ='\0';
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
                Reserve[i].checkIn.day = day;
                Reserve[i].checkIn.month = month;
                Reserve[i].checkIn.year = year;
            
            i++; 
            
            }
            
} 
// enter data and validate into struct
void enterData(reservationInfo* i){
     

   printf("To reserve a room please enter your first and last name:(maximum 100 characters) ");
    fgets(i->customerName,sizeof(i->customerName),stdin);
    i->customerName[strcspn(i->customerName, "\n")] = '\0';
    while(!validateName(i->customerName)){
        printf("Wrong input please enter your first and last name:(maximum 100 characters) ");
        fgets(i->customerName,99,stdin);
        i->customerName[strcspn(i->customerName, "\n")] = '\0';
} 

    printf("please Enter ur national ID: 14 digits");
    fgets(i->nationalID,15,stdin);
    i->nationalID[strcspn(i->nationalID, "\n")] = '\0';
    //wrong id
    while(!validateID(i->nationalID)){
       
        printf("Wrong ID Please try again: 14 digits");
        fgets(i->nationalID,15,stdin);
        i->nationalID[strcspn(i->nationalID, "\n")] = '\0';
        
    }
    i->nationalID[14]='\0';
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
    fgets(i->phoneNum,12,stdin);
     i->phoneNum[strcspn(i->phoneNum, "\n")] = '\0';
    while(!validateMobile(i->phoneNum)){
        //getchar();
        printf("Wrong mobile number Please try again:");
        fgets(i->phoneNum,12,stdin);
         i->phoneNum[strcspn(i->phoneNum, "\n")] = '\0';
    }
    printf("Enter Date of Reservation: (dd/mm/yyyy) ");
    
    char reserveDate[11];
    getchar(); 
    fgets(reserveDate,sizeof(reserveDate),stdin);
    while(!validateDate(reserveDate,&i->checkIn)){
        printf("Wrong date Please try again:");
        fgets(reserveDate,sizeof(reserveDate),stdin);
    } 
    printf("Enter Number of Nights: ");
    scanf("%d",&i->numberNights);
    while(i->numberNights <= 0){
        printf("Wrong number of nights Please try again:");
        getchar();
        scanf("%d",&i->numberNights);
        

    }
    getchar(); 
    printf("CASE SENSITIVE\n");
    printf("choose a Room category:(SeaView,LakeView,GardenView) ");
    fgets(i->RoomCategory,11,stdin);
    while (!validateRoomCategory(i->RoomCategory)){
        printf("Wrong room category Please try again: (SeaView,LakeView,GardenView) ");
       
        fgets(i->RoomCategory,11,stdin);
}
getchar();
 
}
//  print data to confirm
void printReservation(reservationInfo* customer){
    printf("\n");
    clearScreen();
    printf("Customer Name: %s\n",customer->customerName);
    printf("National ID: %s\n",customer->nationalID);
    printf("Customer Email: %s\n",customer->email);
    printf("Customer Phone Number: %s\n",customer->phoneNum);
    printf("Number of Nights: %d\n",customer->numberNights);
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
int chooseRoom (int roomNum,Room* rooms,int count,reservationInfo* customer){

    int flag = 0;
    for (int i = 0;i<count;i++){
        if(rooms[i].number == roomNum){
            strcpy(rooms[i].status,"Reserved");
            customer->roomNum = rooms[i].number ;
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
int validaterandomID(char * str,int line,reservationInfo *all ){
    
    int flag = 0;
    for (int i = 0;i<line;i++){
        if (strcmp(str,all[i].ID)==0){
            flag = 1;
            break;
        }
    }
    return flag;

}
//load customer in file 
void writeCustomer(FILE* file,reservationInfo*all){
 
    fprintf(file,"%s,",all->ID);
    fprintf(file,"%d,",all->roomNum);
    fprintf(file,"%s,",all->status);
    fprintf(file,"%s,",all->customerName);
    fprintf(file,"%s,",all->nationalID);
    fprintf(file,"%d,",all->numberNights);
    fprintf(file,"%d-%d-%d,",all->checkIn.day,all->checkIn.month,all->checkIn.year);
    fprintf(file,"%s,",all->email);
    fprintf(file,"%s",all->phoneNum);
    

   
}
// main reservation function
void reserve(reservationInfo* customer){
//enter custumer data
while(1){
enterData(customer);
//print the reservation data
printReservation(customer);
//check if data is correct
printf("is the data correct if no u will be prompted to enter the data again \n");
printf("y/n: ");
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
else{
    printf("please choose y/n");
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

int choice;
printf("Enter number of the room of your choice: ");
scanf(" %d",&choice);
//check if choice is valid
while(!chooseRoom(choice,rooms,count,customer)){

    printf("Invalid choice, please choose a valid room number \n");
    printf("Enter number of the room of your choice: ");
    scanf(" %d",&choice);
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
//allocate memory
reservationInfo *all = malloc(line*sizeof(reservationInfo));
LoadresRooms(file,all,line);
fclose(file);
//generate random id
randomID(randomcharacter,customer->ID,7);
//validate random id
while(validaterandomID(customer->ID,line,all)){
    printf("ID already exist\n");
    randomID(randomcharacter,customer->ID,7);

}
free(all);
printf("Your Reservation ID is %s please remeber it for later use\n",customer->ID);
//status is unconfirmed
strncpy(customer->status,"unconfirmed",sizeof(customer->status));
//end the string
customer->status[sizeof(customer->status)-1] = '\0';
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
//search for room
int findRoom(Room* rooms,int NUM,int count){
    int i;
    
    for(i=0;i<count;i++){
        if(rooms[i].number == NUM){
            //return index
            return i;
        }
        }
        return -1;

}
// change data in reservation
void changeReservation(){

    char idNum[8];
    printf("Enter your reservation ID or Room number: ");
    scanf("%s",idNum);
    FILE *res = fopen("Reservation.txt","r"); //reservation
    int lines = countlines(res); //lines in reservation
    reservationInfo *all = malloc(lines*sizeof(reservationInfo)); //all people
    LoadresRooms(res,all,lines);
    fclose(res);

    int i;
    int flag = 0;
    // find the line where reservation exits
    for(i=0;i<lines;i++){
        // compare id
        if(strcmp(all[i].ID,idNum)==0){
            flag = 1;
            break;}
            //compare room number
        else if(all[i].roomNum==atoi(idNum)){
            flag = 1;
            break;}
    }
    //doesn't exist
    if(flag == 0){
        printf("No reservation found\n");
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
            printf("Current Name: %s\n",all[i].customerName);
            printf("Do you want to change Reservation name: (y/n)");  
            scanf(" %c",&confirm);
        if(confirm == 'y'){
            printf("Enter new name: ");
            getchar();
            fgets(all[i].customerName,99,stdin);
            all[i].customerName[strcspn(all[i].customerName, "\n")] = '\0';
            while (!validateName(all[i].customerName))
            {
                printf("Invalid name. Please enter a valid name.\n");
                printf("Enter new name: ");
                getchar();
                fgets(all[i].customerName,99,stdin);
                all[i].customerName[strcspn(all[i].customerName, "\n")] = '\0';


                        }
            
            x =1;
        }
        else if (confirm !='y' && confirm!='n'){
            printf("Invalid choice\n");
             x = 0;
                continue;
        }    
        else if(confirm == 'n'){
            x = 1;

        }}
        //change phone
        
        x = 0;
        printf("2. Change Phone Number\n");

        
        //phone number
        while ((!x))
        {
       
        printf("Current phone number: %s \n",all[i].phoneNum);
        printf("Do you want to change Reservation phone number: (y/n)");
        scanf(" %c",&confirm);
        getchar();
        if(confirm == 'y'){
            printf("Enter new phone number: ");
            fgets(all[i].phoneNum,12,stdin);
            all[i].phoneNum[strcspn(all[i].phoneNum, "\n")] ='\0';
            while (!validateMobile(all[i].phoneNum)){
                printf("Invalid phone number. Please enter a valid phone number.\n");
                printf("Enter new phone number: ");
                fgets(all[i].phoneNum,12,stdin);
                all[i].phoneNum[strcspn(all[i].phoneNum, "\n")] ='\0';
                

            }
            x =1;
            }
            else if (confirm !='y' && confirm!='n'){
                printf("Invalid choice\n");
                x = 0;
                continue;
                }
                else if(confirm == 'n'){
            x = 1;

        }
        }
        x = 0;

        //change email
        printf("3. Change Email\n");
        while(!x){
            printf("Current email: %s \n",all[i].email);
            printf("Do you want to change Reservation email: (y/n) ");
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
             else if (confirm !='y' && confirm!='n'){
                printf("Invalid choice\n");
                x = 0;
                continue;
                } 
                else if(confirm == 'n'){
            x = 1;

        }
                }
            //room category
            x = 0;
        printf("4. Change Room Category\n");
        int roomnumber = all[i].roomNum;
        //using room number find category
        int roomlocation = findRoom(rooms,roomnumber,count);
        if(roomlocation == -1){
            printf("room not found");
            exit(1);
            }

        
        
        while(!x){
            printf("Current room category: %s \n",rooms[roomlocation].roomCategory);
        printf("Do you want to change Reservation room category: (y/n)");
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
            int choice;
            printf("Enter number of the room of your choice: ");
            scanf(" %d",&choice);
            while(!chooseRoom(choice,rooms,count,&all[i])){
                
                printf("Invalid choice, please choose a valid room number\n");
                printf("Enter number of the room of your choice: ");
                scanf("%d",&choice);

            }
            
            x = 1;
            }
             else if (confirm !='y' && confirm!='n'){
                printf("Invalid choice\n");
                x = 0;
                continue;
                }
                else if (confirm == 'n'){
                    x = 1;
                }}
                x = 0;
                // number of lines
        printf("5. Change Number of Nights\n");
        while (!x){
            printf("Current number of nights :%d\n",all[i].numberNights);
             printf("Do you want to change Reservation number of nights: (y/n)");
        scanf(" %c",&confirm);
        if(confirm == 'y'){
            
            printf("Enter new number of nights: ");
           
            scanf("%d",&all[i].numberNights);
            x = 1;}
            else if (confirm !='y' && confirm!='n'){
                printf("Invalid choice\n");
                x = 0;
                continue;
                }
                else if(confirm == 'n'){
            x = 1;

        }}
        x = 0;
        //date
        printf("6. Change Date\n");
        
        while (!x)
        {
            printf("Current Date = %d/%d/%d\n",all[i].checkIn.day,all[i].checkIn.month,all[i].checkIn.year);
        printf("Do you want to change Reservation date: (y/n)");
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
                else if (confirm !='y' && confirm!='n'){
                    printf("Invalid choice\n");
                    x = 0;
                continue;
                    }
                    else if(confirm == 'n'){
            x = 1;

        }
        
}
//print reservation
        printf("New Details");
        printReservation(&all[i]);
printf("is the data correct if no u will be prompted to enter the data again \n");
printf("y/n: ");
char finalconfirm;
scanf(" %c",&finalconfirm);
while(finalconfirm !='n'&&finalconfirm !='y'){
    printf("Invalid choice\n");
    printf("y/n: ");
    scanf(" %c",&finalconfirm);
}
if(finalconfirm == 'n'){
    printf("Enter the data again:\n");
    getchar();
    continue;
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
}