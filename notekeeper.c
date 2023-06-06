#include <stdio.h>
#include <string.h>
#include "notekeeper.h"
#include "functions.h"

void noteKeeper(){
    char operation;
    //List Notes
    printf("Press A to add Note\n");
    scanf(" %c" , &operation);

    switch (operation) {
        case 'A':
        case 'a':
            addNote();
            break;
    }
}

int addNote(){
    Note note;
    char buffer[MAX_CONTENT_LENGTH];

    printf("Title: ");
    scanf("%s" ,  note.title);
    printf("Content(Press CTRL + D to stop and save): \n\n");
    while (fgets(buffer, MAX_CONTENT_LENGTH, stdin) != NULL) {
        strcat(note.content, buffer);
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
    char fileName[MAX_TITLE_LENGTH];

    strcpy(fileName, "notes/");
    strcat(fileName, note.title);
    strcat(fileName, ".txt");
    fp = fopen(fileName, "w");

    if(fp == NULL){
        printf("Failed to open the file for writing.\n");
        return 1;
    }

    fprintf(fp, "Title: %s\n" , note.title);
    fprintf(fp, "Last Modified Date : %ld\n\n" ,note.lastModifiedDate );
    fprintf(fp, "%s" , note.content);
    fclose(fp);

    return 0;
     
}