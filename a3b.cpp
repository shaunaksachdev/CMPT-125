//Shaunak Sachdev
//SFU Computing ID: ssa516@sfu.ca
//Student ID: 301558905

#include "a4_talklib.hpp"

Talk* createTalk(short hours, short minutes, short seconds, const string title, const string overview) {
    Talk* talk = new Talk;  
    talk->seconds = seconds;
    talk->minutes = minutes;
    talk->hours = hours;
    talk->title = title;
    talk->overview = overview;
    return talk; // returning the talk 
}

void deleteTalk(Talk* talk){
    if (talk != nullptr) 
        delete talk; // deallocate the memory
}

void printTalk(const Talk* talk){
        cout << "Duration: " << talk->hours << " hours, " << talk->minutes << " minutes, " << talk->seconds << " seconds" << std::endl;
        cout << "Talk Title: " << talk->title << endl;
        cout << "Overview: " << talk->overview << endl;
}


bool compareTalksByDuration(const Talk *p1, const Talk *p2) {
    // calculating total seconds then compairing
    int totalSeconds1 = p1->hours * 3600 + p1->minutes * 60 + p1->seconds;
    int totalSeconds2 = p2->hours * 3600 + p2->minutes * 60 + p2->seconds;

    return totalSeconds1 < totalSeconds2;
}



bool compareTalksByTitle(const Talk *p1, const Talk *p2){
    return p1->title < p2->title; // compairing two strings
}