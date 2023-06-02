#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include"functions.h"
#include"todo_manager.h"


int displayUi(){
    int page;
    int reminders = checkReminders();

	if (reminders) printf("--You have %d todos(check TodoList)\n\n\n" , reminders );

    printf("\t\tWelcome\n\n");
    printf("1) TodoList\n");
    printf("2) NoteKeeper\n");
    printf("3) Clock\n\n");
    scanf("%d",&page);
    return page;
}

int main(int argc , char* argv[]){
    if(argc < 2){
        switch(displayUi()){
            case 1:
                todoManager();
                break;
            case 2:
                // noteKeeper();
                printf("NoteKeeper");
                break;
            case 3:
                // clock();  
                printf("Clock");
                break;
            default:
                printf("Option invalid");          
        }
    }
    else{
        
        if(!strcmp(toLowerCase(argv[1]),"todolist")){
            //todoList();
            printf("TodoList");
        }
        else if(!strcmp(toLowerCase(argv[1]),"notekeeper")){
            //notekeeper();
            printf("NoteKeeper");
        }
        else if(!strcmp(toLowerCase(argv[1]),"clock" )){
            //clock();
            printf("clock");
        }
    }

}


//TODO: Display reminder on main menu , Fix  last modification time , sort todos , add main menu to todoList