//functions.c
//file contains usefull functions needed in program  

char* toLowerCase(char *str){
    for(int i=0; str[i] ; i++){
        str[i]=tolower(str[i]);
    }
    return str;
}