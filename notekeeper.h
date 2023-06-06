#include <bits/types/time_t.h>
#define MAX_TITLE_LENGTH 2000
#define MAX_CONTENT_LENGTH 10000

typedef struct Note{
    char  title[MAX_TITLE_LENGTH];
    char content[MAX_CONTENT_LENGTH];
    time_t lastModifiedDate;
}Note;

void noteKeeper();
int addNote();
int writeNoteToFile(Note note);

