#include<time.h>

void main_menu();
extern char* toLowerCase(char *str);
extern void setModifiedTime(time_t *str);
void clearConsole();
void sleepOneSecond();
int checkReminders();
int compareDates(time_t date1, time_t date2);