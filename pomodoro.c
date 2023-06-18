#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "pomodoro.h"
#include "functions.h"


void pomodoro(){
    int sessionDuration;
    int shortBreakDuration;
    int longBreakDuration;
    int elapsedTime = 0;
    int numSessions;
    int pomodoroCount = 0;

    clearConsole();
    printf("Session Duration(in minutes): ");
    scanf("%d" , &sessionDuration);
    sessionDuration *= 60; 

    printf("Short Break Duration(in minutes): ");
    scanf("%d" , &shortBreakDuration);
    shortBreakDuration *= 60;

    printf("Long Break Duration(in minutes): ");
    scanf("%d" , &longBreakDuration);
    longBreakDuration *= 60;

    printf("Number of Bouts: ");
    scanf("%d" , &numSessions);
    
    while (pomodoroCount < numSessions) {
        
        while(sessionDuration >= elapsedTime){
            clearConsole();
            printf("Time Left: ");
            printTime(sessionDuration - elapsedTime);
            sleepOneSecond();
            elapsedTime++;
        }
        pomodoroCount++;
        elapsedTime = 0;

        if (pomodoroCount % 4 == 0){
            while (longBreakDuration >= elapsedTime) {
                clearConsole();
                printf("Long Break: ");
                printTime(longBreakDuration - elapsedTime);
                sleepOneSecond();
                elapsedTime++;
            }   
            elapsedTime = 0;
        }
        
        else{
            while (shortBreakDuration >= elapsedTime) {
                clearConsole();
                printf("Short: ");
                printTime(shortBreakDuration - elapsedTime);
                sleepOneSecond();
                elapsedTime++;
            }   
        }
        
    }
}


void printTime(int t) {
    int hours = t / 3600;
    int minutes = (t % 3600) / 60;
    int seconds = t % 60;

    printf("%02d:%02d:%02d\n", hours, minutes, seconds);
}
