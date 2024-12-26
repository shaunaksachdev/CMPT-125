#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "a2_question2.h"

// Name: Shaunak Sachdev
// Student ID: 301558905
// Computing ID: SSA516@SFU.CA

// Function to read talk information from the file and store it in a dynamic array
Talk** readTalksFromFile(const char* filename, int* numTalks) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    int capacity = 16;  // Initial capacity
    int used = 0;       // Number of talks read
    Talk** talks = (Talk**)malloc(capacity * sizeof(Talk*));

    if (talks == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    char line[301];  // Assuming a maximum of 300 characters per line

    while (fgets(line, sizeof(line), file) != NULL) {
        if (used == capacity) {
            capacity *= 2;
            talks = (Talk**)realloc(talks, capacity * sizeof(Talk*));

            if (talks == NULL) {
                perror("Memory reallocation failed");
                exit(1);
            }
        }

        // Parse talk information and create a Talk struct
        short hours, minutes, seconds;
        char title[301], overview[301];
        sscanf(line, "Duration: %hd:%hd:%hd", &hours, &minutes, &seconds);
        fgets(title, sizeof(title), file);
        fgets(overview, sizeof(overview), file);

        // Allocate memory for the Talk struct and deep-copy the strings
        Talk* talk = createTalk(hours, minutes, seconds, title, overview);

        if (talk == NULL) {
            perror("Memory allocation for Talk failed");
            exit(1);
        }

        talks[used++] = talk;
    }

    fclose(file);
    *numTalks = used;
    return talks;
}

// Function to print talk information
void printTalks(Talk** talks, int numTalks) {
    for (int i = 0; i < numTalks; i++) {
        printf("Talk #%d\n", i + 1);
        printf("%dh%dm%ds\n%s\n%s\n\n", talks[i]->hours, talks[i]->minutes, talks[i]->seconds,
               talks[i]->title, talks[i]->overview);
    }
}

// Function to free allocated memory
void freeTalks(Talk** talks, int numTalks) {
    for (int i = 0; i < numTalks; i++) {
        clearTalk(talks[i]);
    }
    free(talks);
}

int main() {
    printf("*******************************************************\n");
    printf("           CSTalks Viewer by Your Name\n");
    printf("    SFU ID: YourID | SFU Email: youremail@sfu.ca\n");
    printf("*******************************************************\n\n");

    int numTalks;
    Talk** talks = readTalksFromFile("CSTalksList.txt", &numTalks);

    printTalks(talks, numTalks);

    freeTalks(talks, numTalks);

    return 0;
}