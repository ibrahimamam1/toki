//functions.c
//file contains usefull functions needed in program  
#include"functions.h"
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
#include <unistd.h>

void sleepOneSecond(){
#ifdef _WIN32
    Sleep(1000); // For Windows
#else
    sleep(1); // For Linux and macOS
#endif
}

char* toLowerCase(char *str){
    for(int i=0; str[i] ; i++){
        str[i]=tolower(str[i]);
    }
    return str;
}

void setModifiedTime(time_t *lt){

*lt = time(NULL);
}

void clearConsole(){
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and macOS
#endif
}