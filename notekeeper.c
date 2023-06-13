#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notekeeper.h"
#include "functions.h"


void noteKeeper(){
    readNoteFromFile();
    
}

int addNote(){
    Note note;
    char buffer[MAX_CONTENT_LENGTH];

    clearConsole();
    printf("Title: ");
    scanf("%s" ,  note.title);
    printf("Content (Type STOP to stop and save):\n\n");
     while (1) {
        fgets(buffer, MAX_CONTENT_LENGTH, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline character

        if (strcmp(buffer, STOP_SIGNAL) == 0) {
            break; // Stop reading input and exit the loop
        }

        strcat(note.content, buffer);
        strcat(note.content, "\n"); // Add a newline to separate lines
    }

    // Remove the trailing newline character, if present
    if (note.content[strlen(note.content) - 1] == '\n')
    {
        note.content[strlen(note.content) - 1] = '\0';
    }

    setModifiedTime(&note.lastModifiedDate);

    writeNoteToFile(note);
    return 0;
}

int writeNoteToFile(Note note){
    FILE* fp;
    FILE* sp;
    char fileName[MAX_TITLE_LENGTH];

    strcpy(fileName, "notes/");
    strcat(fileName, note.title);
    strcat(fileName, ".txt");
    fp = fopen(fileName, "w");
    sp = fopen("notes.txt", "a");

    if(fp == NULL){
        printf("Failed to open the file for writing.\n");
        return 1;
    }

    fprintf(fp, "Title: %s\n" , note.title);
    fprintf(fp, "Last Modified Date : %ld\n\n" ,note.lastModifiedDate );
    fprintf(fp, "%s" , note.content);
    fclose(fp);

     if(sp == NULL){
        printf("Failed to open the file for writing.\n");
        return 1;
    }
    
    fprintf(sp, "%s\n" , fileName);//writing path to note in seperate file
    fclose(sp);
    return 0;
     
}

int readNoteFromFile(){
    FILE* fp ;
    FILE* sp ;
    char fileName[MAX_TITLE_LENGTH];
    char buffer[MAX_TITLE_LENGTH];
    Note notes[100];
    int n_Notes = 0;

    sp = fopen("notes.txt", "r"); 

     if (sp == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    for(int i=0; i < 100 && fgets(fileName, MAX_TITLE_LENGTH, sp); i++) {
        fgets(fileName, MAX_TITLE_LENGTH, sp);
        strtok(fileName, "\n");
        if(strlen(fileName) >= 6){
            fp = fopen(fileName, "r");
            fscanf(fp, " Title: %s" , notes[i].title);
            fscanf(fp, " Last Modified Date : %lu" , &notes[i].lastModifiedDate);
            while(!feof(fp)){
            fgets(buffer, MAX_TITLE_LENGTH, fp);
            strcat(notes[i].content, buffer);
            }
            fclose(fp);
            n_Notes++;
        }    
    }
    fclose(sp);
    ListNotes(notes , n_Notes);
    return 0;
}

void ListNotes(Note *notes , int n){
    char operation;
    int i;
    int noteIndex;

    clearConsole();
    for(i=0; i<n; i++){
        printf("%d -\tTITLE: %s\n",i+1,notes[i].title);
        printf("     \tLast modified Time: %s\n\n" ,ctime(&notes[i].lastModifiedDate) );
    }

    printf("Press A to add Note\n");
    if(n>=1){
        printf("Press S to Reverse Order\n");
        printf("Press D to Delete Note\n");
    }
    scanf(" %c" , &operation);

    switch (operation) {
        case 'A':
        case 'a':
            addNote();
            readNoteFromFile();
            break;
        case 'D':
        case 'd':
             printf("\nWhich note do you want to delete?\n");
             scanf("%d" ,&noteIndex);
             deleteNote(notes, noteIndex-1, n);
             break;       
        case 'S':
        case 's':
            sortNotes(notes , n);
            ListNotes(notes , n);
            break; 
         default:
                noteIndex = operation - '0'; // Convert character to integer
                if (noteIndex >= 1 && noteIndex <= n) displayNote(notes[noteIndex - 1]);
                else {
                    printf("Invalid input. Please try again.\n");
                }
                break;       
    }
}

void sortNotes(Note* notes, int len){
    
    int start = 0;
    int end = len - 1;

    while (start < end) {
        // Swap elements at start and end indices
        Note temp = notes[start];
        notes[start] = notes[end];
        notes[end] = temp;

        // Move the start and end indices towards the center
        start++;
        end--;
    }
    
}

void displayNote(Note note ){
    int operation;
    clearConsole();
    printf("\t\t\tPress 1 to edit\n");
    printf("\t\t\tPress 2 to Go back\n\n");
    printf("%s" , note.content);
    printf("\n\n");

    scanf("%d" , &operation);
    if (operation == 1) {
        clearConsole();
        printf("Sorry not available yet!!!\n");
        //TODO: Implement feature
    }
    else if (operation == 2) {
        clearConsole();
        readNoteFromFile();
    }
}

int deleteNote(Note* notes , int index , int len){
    //1) Delete note file
    char fileName[MAX_TITLE_LENGTH];
    char buffer[MAX_TITLE_LENGTH];

    strcpy(fileName, "notes/");
    strcat(fileName, notes[index].title);
    strcat(fileName, ".txt");

     if (remove(fileName) != 0) {
        printf("Error deleting the note file.\n");
        return -1;
    }

    //2) Remove note from notes array
    for(int i = index; i < len-1 ; i++){
        notes[i] = notes[i+1];
    }
    len--;
    
    //3)Remove notes paths from notes.txt
    FILE* fp = fopen("notes.txt", "w");
    for(int i = 0; i<len; i++){
        strcpy(fileName, "notes/");
        strcat(fileName, notes[i].title);
        strcat(fileName, ".txt");
        fprintf(fp, "%s\n" , fileName);//writing path to note in seperate file
    }
    fclose(fp);
    readNoteFromFile();
    return 0;
}