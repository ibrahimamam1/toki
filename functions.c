//functions.c
//file contains usefull functions needed in program  
#include"functions.h"
#include<string.h>
#include <stdio.h>
#include<ctype.h>
#include<time.h>
#include<stdlib.h>
#include <unistd.h>
#include"todo_manager.h"

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

int checkReminders()
{
    int n = 0;
    Todos* todo = NULL;
    int i = 0;
    int nlines = 1;
    int n_todos = 0;
    FILE* fp = fopen("todo.txt", "r");

    // Get number of exams
    while (!feof(fp)) {
        if (fgetc(fp) == '\n')
            nlines++;
    }
    n_todos = nlines / 5;
    todo = (Todos*)malloc(n_todos * sizeof(Todos));

    // Read exams from file
    fseek(fp, 0, SEEK_SET);
    while (i < n_todos) {
        fgets((todo)[i].title, 100, fp);
        strtok((todo)[i].title, "\n");
        fgets((todo)[i].description, 1000, fp);
        strtok((todo)[i].description, "\n");
        fscanf(fp, "%d", &(todo)[i].priority);
        fscanf(fp, "%d", &(todo)[i].reminder);
        fscanf(fp,"%lu",&todo[i].modifiedTime);
        fseek(fp,1,SEEK_CUR);
        i++;
    }

    fclose(fp);

    for (int i = 0; i < n_todos; i++)
    {
        if (todo[i].reminder == 1) n++;
    }
    return n;
}

int compareDates(time_t date1, time_t date2)
{
    double diff = difftime(date1, date2);
    
    if (diff < 0) {
        // Date 2 is closer than Date 1
        return 0;
    } else {
        // Date 1 is closer than or equal to Date 2
        return 1;
    }
}