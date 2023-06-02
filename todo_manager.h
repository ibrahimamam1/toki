#include<time.h>
struct Todos{
    char title[100];
    char description[1000];
    int priority;
    int reminder;
    time_t modifiedTime;
};
typedef struct Todos Todos;
void todoManager();
void readTodo(Todos*);
void displayTodo(Todos*);
void listTodos(Todos*);
void addTodo(Todos* , int);
void deleteTodo(Todos*);
void setReminder(Todos *todo);
void sortTodos(Todos* todo, int length, int mode);
int compareDates(time_t date1, time_t date2);