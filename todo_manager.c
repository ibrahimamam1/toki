#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"functions.h"
#include"todo_manager.h"

int nTodos;

void todoManager(){
    
    Todos *todo;
    readTodo(todo);
}

void readTodo(Todos* todo){

    int i=0;
    int nlines=1;
    nTodos=0;
    FILE* fp=fopen("todo.txt","r");

    //get number of todos;
    while(!feof(fp)){
        if(fgetc(fp)=='\n')
            nlines++;
    }
    nTodos = nlines/4;
    todo = (Todos*)malloc(nTodos*sizeof(Todos));
    
    //read Todos
    fseek(fp,0,SEEK_SET);
    while(i<nTodos){
        fgets(todo[i].title ,100 , fp);
        strtok(todo[i].title ,"\n");
        fgets(todo[i].description , 1000, fp);
        strtok(todo[i].description , "\n");
        fscanf(fp,"%d",&todo[i].priority);
        fscanf(fp,"%lu",&todo[i].modifiedTime);
        fseek(fp,1,SEEK_CUR);
        i++;
    }
        
    fclose(fp);
    displayTodo(todo);
}
void displayTodo(Todos *todo){

    char action;
    system("clear");
    listTodos(todo);
    printf("Press A to add a Todo\n");
    if(nTodos>0){
        printf("Press R to set a reminder\n");
        printf("Press V to delete a Todo\n");
    }
        
    scanf(" %c",&action);
    getchar();
    switch(action){
        case 'A':
        case 'a': addTodo(todo , ++nTodos);
                  break;
        case 'V':          
        case 'v': deleteTodo(todo);
                  break;
        case 'R':          
        case 'r': setReminder(todo);
                  break;                        
        default : printf("Invalid Command");          
    }
}

void listTodos(Todos *todo){
    for(int i=0; i<nTodos; i++){
        printf("%d- %s: %s\n\n\tpriority:%d\n\tLast modified time: %s\n" , i+1, todo[i].title , todo[i].description, todo[i].priority,ctime(&todo[i].modifiedTime));
    }
}

void addTodo(Todos *todo , int n){
    FILE* fp = fopen("todo.txt","a");
    char *p;

    system("clear");
    todo = (Todos*)realloc(todo , (n*sizeof(Todos)));

    printf("Title: ");
    fgets(todo[n-1].title , 100 , stdin);
    strtok(todo[n-1].title , "\n");
    printf("Description: ");
    fgets(todo[n-1].description , 1000 , stdin);
    strtok(todo[n-1].description , "\n");
    printf("priority(1-5): ");
    scanf("%d" ,&todo[n-1].priority);
    setModifiedTime(&todo[n-1].modifiedTime);
    fprintf(fp,"%s\n%s\n%d\n%lu\n",todo[n-1].title,todo[n-1].description,todo[n-1].priority,todo[n-1].modifiedTime);
    fclose(fp);
    system("clear");
    displayTodo(todo);
}

void deleteTodo(Todos *todo){
    
    int n;
    FILE* fp = fopen("todo.txt","w");
    system("clear");
    listTodos(todo);
    printf("Select todo to delete(press 0 to delete all)\n");
    scanf("%d", &n);
    //delete todo
    if(n==0){
        fclose(fp);
        nTodos=0;
        free(todo);
    }
    else{   
        for(int i=n-1; i<nTodos-1; i++){
            todo[i]=todo[i+1];
        }
        nTodos--;
        todo = (Todos*)realloc(todo , (nTodos*sizeof(Todos))); //reallocate memory

        //write modification in file
        for(int i=0;i<nTodos;i++){
            fprintf(fp,"%s\n%s\n%d\n%lu\n",todo[i].title,todo[i].description,todo[i].priority,todo[i].modifiedTime);
        }
        fclose(fp);
    }
    
    displayTodo(todo);
}

void setReminder(Todos *todo){
    printf("Sorry not available yet\n");
    // int n;
    // system("clear");
    // listTodos(todo);
    // printf("Select todo to create reminder\n");
    // scanf("%d", &n);
    // printf("")
    displayTodo(todo);
}    
