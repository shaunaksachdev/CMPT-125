// Name: Shaunak Sachdev
// SFU ID:301558905
// Computing ID: ssa516@sfu.ca

#include "a3_talklib.h"
#include <stdlib.h>
#include <string.h>

Talk* createTalk(short hours, short minutes, short seconds, const char* title, const char* overview) {
    Talk* talk = (Talk*) malloc(sizeof(Talk));
    if (!talk) return NULL;

    talk->hours = hours;
    talk->minutes = minutes;
    talk->seconds = seconds;

    talk->title = strdup(title);
    talk->overview = strdup(overview);

    return talk;
}

void clearTalk(Talk* talk) {
    if (talk) {
        free(talk->title);
        free(talk->overview);
    }
}

int compareTalksByDuration(const void *p1, const void *p2) {
    const Talk *talk1 = *(const Talk**)p1;
    const Talk *talk2 = *(const Talk**)p2;

    int duration1 = talk1->hours * 3600 + talk1->minutes * 60 + talk1->seconds;
    int duration2 = talk2->hours * 3600 + talk2->minutes * 60 + talk2->seconds;

    return duration1 - duration2;
}

int compareTalksByTitle(const void *p1, const void *p2) {
    const Talk *talk1 = *(const Talk**)p1;
    const Talk *talk2 = *(const Talk**)p2;

    return strcmp(talk1->title, talk2->title);
}

int* lookupTalkByTitle(Talk **array, int size, const char* title) {
    int *indexes = (int*) malloc((size + 1) * sizeof(int));
    if (!indexes) return NULL;

    int index_count = 0;
    for (int i = 0; i < size; ++i) {
        if (strstr(array[i]->title, title) != NULL) {
            indexes[index_count++] = i;
        }
    }

    indexes[index_count] = -1;
    return indexes;
}