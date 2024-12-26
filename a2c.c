// Name: Shaunak Sachdev
// SFU ID:301558905
// Computing ID: ssa516@sfu.ca
#include "a3_talklib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Forward Declarations
void loadTalksFromFile(Talk ***array, int *size, const char* filename);
void listTalksSortedByDuration(Talk **array, int size);
void listTalksSortedByTitle(Talk **array, int size);
void lookupTalk(Talk **array, int size);
void freeTalkArray(Talk ***array, int size);
void printBanner();
int main() {
    Talk **talkArray = NULL;
    int talkArraySize = 0;
    int userOption;

    printBanner();

    do {
        printf("1. Load talks from CSTalksList.txt\n");
        printf("2. List talks sorted by duration\n");
        printf("3. List talks sorted by title\n");
        printf("4. Lookup a talk\n");
        printf("5. Terminate program\n");
        printf("Enter option: ");
        scanf("%d", &userOption);
        getchar(); // Catch newline character

        if ((userOption == 2 || userOption == 3 || userOption == 4) && 
            talkArraySize == 0) {
            printf("No talks file loaded. Please load the CSTalksList.txt file first.\n");
            continue;
        }

        switch (userOption) {
            case 1: {
                const char* filename = "CSTalksList.txt";
                loadTalksFromFile(&talkArray, &talkArraySize, filename);
                break;
            }
            case 2:
                listTalksSortedByDuration(talkArray, talkArraySize);
                break;
            case 3:
                listTalksSortedByTitle(talkArray, talkArraySize);
                break;
            case 4:
                lookupTalk(talkArray, talkArraySize);
                break;
            case 5:
                printf("Thank you for using the program. Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (userOption != 5);

    freeTalkArray(&talkArray, talkArraySize);
    return 0;
}

void printBanner() {
    printf("=======================================\n");
    printf("Talk Lookup System\n");
    printf("Developed by: Shaunak Sachdev\n");
    printf("SFU ID: 301558905\n");
    printf("Email: ssa516@sfu.ca\n");
    printf("=======================================\n");
}

void loadTalksFromFile(Talk ***talksArray, int *arraySize, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file '%s'.\n", filename);
        return;
    }

    freeTalkArray(talksArray, *arraySize); // Free existing talks if any
    *arraySize = 0;

    char line[1024], title[301], overview[1024];
    short hours, minutes, seconds;
    while (fgets(line, sizeof(line), file)) {
        // Parse duration, title, and overview from the file
        if (sscanf(line, "**Duration:** %hd hour, %hd minutes, %hd seconds", 
                   &hours, &minutes, &seconds) == 3) {
            fgets(line, sizeof(line), file); // Read title
            sscanf(line, "**Talk Title:** \"%[^\"]\"", title);
            fgets(line, sizeof(line), file); // Read overview
            sscanf(line, "**Overview:** %[^\n]", overview);
            fgets(line, sizeof(line), file); // Skip delimiter line

            *talksArray = realloc(*talksArray, (*arraySize + 1) * sizeof(Talk*));
            if (!(*talksArray)) {
                printf("Memory allocation failed.\n");
                fclose(file);
                return;
            }

            (*talksArray)[*arraySize] = createTalk(hours, minutes, seconds, title, overview);
            if (!(*talksArray)[*arraySize]) {
                printf("Memory allocation for talk failed.\n");
                fclose(file);
                return;
            }
            (*arraySize)++;
        }
    }

    fclose(file);
    printf("Loaded %d talks from '%s'.\n", *arraySize, filename);
}

void listTalksSortedByDuration(Talk **talksArray, int arraySize) {
    if (arraySize == 0) {
        printf("No talks to display.\n");
        return;
    }

    qsort(talksArray, arraySize, sizeof(Talk*), compareTalksByDuration);

    for (int i = 0; i < arraySize; i++) {
        printf("%d. %s (%dh%dm%ds)\n", i + 1, talksArray[i]->title, 
               talksArray[i]->hours, talksArray[i]->minutes, talksArray[i]->seconds);
    }
}

void listTalksSortedByTitle(Talk **talksArray, int arraySize) {
    if (arraySize == 0) {
        printf("No talks to display.\n");
        return;
    }

    qsort(talksArray, arraySize, sizeof(Talk*), compareTalksByTitle);

    for (int i = 0; i < arraySize; i++) {
        printf("%d. %s\n", i + 1, talksArray[i]->title);
    }
}

void lookupTalk(Talk **talksArray, int arraySize) {
    char titleToLookup[51];
    printf("Enter title to lookup (case-sensitive): ");
    fgets(titleToLookup, sizeof(titleToLookup), stdin);
    titleToLookup[strcspn(titleToLookup, "\n")] = 0; // Remove newline character

    int *foundIndexes = lookupTalkByTitle(talksArray, arraySize, titleToLookup);

    if (foundIndexes[0] == -1) {
        printf("No such talk on record.\n");
    } else {
        for (int i = 0; foundIndexes[i] != -1; i++) {
            int idx = foundIndexes[i];
            printf("%s (%dh%dm%ds)\n%s\n", talksArray[idx]->title, 
                   talksArray[idx]->hours, talksArray[idx]->minutes, 
                   talksArray[idx]->seconds, talksArray[idx]->overview);
        }
    }

    free(foundIndexes);
}

void freeTalkArray(Talk ***talksArray, int arraySize) {
    if (*talksArray) {
        for (int i = 0; i < arraySize; i++) {
            clearTalk((*talksArray)[i]);
            free((*talksArray)[i]);
        }
        free(*talksArray);
        *talksArray = NULL;
    }
}