#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Name: Shaunak Sachdev
// Student ID: 301558905
// Computing ID: SSA516@SFU.CA

typedef struct {
    short hours;
    short minutes;
    short seconds;
    char* title;
    char* overview;
} Talk;

Talk* createTalk(short hours, short minutes, short seconds, const char* title, const char* overview) {
    // Allocate memory for the Talk struct
    Talk* talk = (Talk*)malloc(sizeof(Talk));
    
    if (talk == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    
    // Calculating the total minutes and seconds
    int totalMinutes = hours * 60 + minutes;
    int totalSeconds = totalMinutes * 60 + seconds;
    
    // Calculating the correct hours, minutes, and seconds from the total seconds
    talk->hours = totalSeconds / 3600;
    talk->minutes = (totalSeconds % 3600) / 60;
    talk->seconds = totalSeconds % 60;
    
    // Duplicating and storing the title and overview strings
    talk->title = strdup(title);
    talk->overview = strdup(overview);
    
    if (talk->title == NULL || talk->overview == NULL) {
        // Handling memory allocation failure
        free(talk->title);
        free(talk->overview);
        free(talk);
        return NULL;
    }
    
    return talk;
}

void clearTalk(Talk* talk) {
    if (talk == NULL) {
        return;
    }
    
    // Freeing the memory for title, overview, and the Talk struct itself
    free(talk->title);
    free(talk->overview);
    free(talk);
}

int main() {
    short hours, minutes, seconds;
    char title[100]; 
    char overview[500];  
    
    printf("Enter hours, minutes, and seconds: ");
    scanf("%hd, %hd, %hd", &hours, &minutes, &seconds);
    
    // Clear the newline character from the previous input
    while (getchar() != '\n');
    
    printf("Enter title: ");
    fgets(title, sizeof(title), stdin);
    title[strlen(title) - 1] = '\0';  // Remove the newline character
    
    printf("Enter overview: ");
    fgets(overview, sizeof(overview), stdin);
    overview[strlen(overview) - 1] = '\0';  // Remove the newline character
    
    Talk* talk = createTalk(hours, minutes, seconds, title, overview);
    
    if (talk != NULL) {
        printf("%dh%dm%ds\n%s\n%s\n", talk->hours, talk->minutes, talk->seconds, talk->title, talk->overview);
        
        // Releasing memory for title, overview, and the Talk struct itself
        clearTalk(talk);
    } else {
        printf("Failed to create Talk.\n");
    }
    
    return 0;
}