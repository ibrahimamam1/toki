#include <bits/types/time_t.h>
#include<stdio.h>
#define MAX_TITLE_LENGTH 2000
#define MAX_CONTENT_LENGTH 10000
#define STOP_SIGNAL "STOP"

typedef struct Note{
    char  title[MAX_TITLE_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    time_t lastModifiedDate;
}Note;

void noteKeeper();
int addNote();
int writeNoteToFile(Note note);
int readNoteFromFile();
void ListNotes(Note* , int);
void sortNotes(Note* , int len);
void displayNote(Note);
int deleteNote(Note* , int index, int len);
void searchNotes(Note* , int len);
void ListFoundNotes(Note* , int);