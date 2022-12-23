#include<time.h>
struct Todos{
    char title[100];
    char description[1000];
    int priority;
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