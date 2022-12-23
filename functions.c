//functions.c
//file contains usefull functions needed in program  
#include"functions.h"
#include<string.h>
#include<ctype.h>
#include<time.h>

char* toLowerCase(char *str){
    for(int i=0; str[i] ; i++){
        str[i]=tolower(str[i]);
    }
    return str;
}

void setModifiedTime(time_t *lt){

*lt = time(NULL);
}