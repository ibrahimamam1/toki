#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include"functions.h"
#include"todo_manager.h"


int displayUi(){
    int page;
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


