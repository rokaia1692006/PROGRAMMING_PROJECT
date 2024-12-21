#ifndef RESERVATION_H 
#define RESERVATION_H
typedef struct{
    int day;
    int month;
    int year;
}date;
typedef struct{
    char ID[8];
    int roomNum;
    char customerName [100];
    char phoneNum[12];
    int numberNights;
    char email[100];
    date checkIn;
    char RoomCategory [10];
    char status[13];
    char nationalID[15];
    
}reservationInfo;
typedef struct 
{
    int number;
    char status[100];
    char roomCategory[100];
    int price;


}Room;
const char* domains []= {
    "alexu.edu.eg",
    "gmail.com",
    "yahoo.com",
    "hotmail.com",
    "outlook.com",
    "aol.com",
    "icloud.com",
    "protonmail.com",
    "protonmail.ch",
    "yandex.com",
    "mail.ru",
    "yahoo.co.uk",
    "yahoo.com.au",
    "yahoo.com.br",
    "yahoo.com.cn",
    "yahoo.com.hk",
    "yahoo.com.in",
    "yahoo.com.mx",
    "yahoo.com.sg",
    "yahoo.com.tr",
    "yahoo.com.tw",
    "yahoo.com.ua",
    "yahoo.com.vn",
    "yahoo.co.jp",
    "yahoo.co.kr",
    "yahoo.co.nz",
    "yahoo.co.th",
    "yahoo.co.uk",
    "yahoo.com.ar"
};
const char* phoneCompany[]={
    "011",
    "012",
    "015"
};
const char* categories[]={
    "SeaView",
    "LakeView",
    "GardenView"
};

const char randomcharacter[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 
    'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x',
    'y', 'z',
    'A','B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z',
    '1','2','3','4','5','6','7',
    '8','9'


};
#endif