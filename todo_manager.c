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
    nTodos = nlines/5;
    todo = (Todos*)malloc(nTodos*sizeof(Todos));
    
    //read Todos
    fseek(fp,0,SEEK_SET);
    while(i<nTodos){
        fgets(todo[i].title ,100 , fp);
        strtok(todo[i].title ,"\n");
        fgets(todo[i].description , 1000, fp);
        strtok(todo[i].description , "\n");
        fscanf(fp,"%d",&todo[i].priority);
        fscanf(fp,"%d",&todo[i].reminder);
        fscanf(fp,"%lu",&todo[i].modifiedTime);
        fseek(fp,1,SEEK_CUR);
        i++;
    }
        
    fclose(fp);
    displayTodo(todo);
}
void displayTodo(Todos *todo){
    int sortMode;
    char action;
    system("clear");
    listTodos(todo);
    printf("Press A to add a Todo\n");
    if(nTodos>0){
        printf("Press R to set/remove a reminder\n");
        printf("Press V to delete a Todo\n");
        printf("Press S to sort  Todos\n");
    }
    printf("Press M to go to main menu\n");    

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
        case 'S':          
        case 's': 
                    printf("1) Sort by Priority\n");
                    printf("2) Sort by Date\n");
                    scanf("%d", &sortMode);
                    if(sortMode == 1 ) sortTodos(todo , nTodos , 0 );
                    else if (sortMode == 2) sortTodos(todo, nTodos, 1);
                    break;            
        case 'M':          
        case 'm': main_menu();
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
    fprintf(fp,"%s\n%s\n%d\n%d\n%lu\n",todo[n-1].title,todo[n-1].description,todo[n-1].priority,todo[n-1].reminder,todo[n-1].modifiedTime);
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
    int n;
    FILE* fp = fopen("todo.txt","w");
    clearConsole();
    listTodos(todo);
    printf("Select todo to create/remove reminder\n");
    scanf("%d", &n);

    if(todo[n-1].reminder == 1){
        todo[n-1].reminder = 0;
        printf("Reminder removed succesfully\n\n");
    } 
    else{
        todo[n-1].reminder = 1;
        printf("Reminder set succesfully\n\n");
    } 
    sleepOneSecond();

    
     //write modification in file
        for(int i=0;i<nTodos;i++){
            fprintf(fp,"%s\n%s\n%d\n%d\n%lu\n",todo[i].title,todo[i].description,todo[i].priority,todo[i].reminder,todo[i].modifiedTime);
        }
        fclose(fp);
      
    
    clearConsole();  
    displayTodo(todo);
}   

void sortTodos(Todos* todo, int length, int mode)
{
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - i - 1; j++)
        {
            if ( (mode == 0 && todo[j].priority < todo[j + 1].priority) ||
                (mode == 1 && compareDates(todo[j].modifiedTime, todo[j + 1].modifiedTime)) )
            {
                // Swap todo[j] and todo[j+1]
                Todos temp = todo[j];
                todo[j] = todo[j + 1];
                todo[j + 1] = temp;
            }
        }
    }
    displayTodo(todo);
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
