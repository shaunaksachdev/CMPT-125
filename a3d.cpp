////Shaunak Sachdev
//SFU Computing ID: ssa516@sfu.ca
//Student ID: 301558905

#include "a4_talkList.hpp"


TalkList::TalkList(){
    //no variables to iniitalize
}

TalkList::~TalkList() {
    for (Talk* talk : talkEntries) {
        deleteTalk(talk);
    }
    talkEntries.clear();
}

int TalkList::getSize(){
    return talkEntries.size();
}

void TalkList::listTalksByDuration(){
    std::sort(talkEntries.begin(), talkEntries.end(), compareTalksByDuration);
    for (const Talk* talk : talkEntries) {
        printTalk(talk);
        std::cout << "---" << std::endl;
    }
}

void TalkList::listTalksByTitle(){

    std::sort(talkEntries.begin(), talkEntries.end(), compareTalksByTitle);
    for (const Talk* talk : talkEntries) {
        printTalk(talk);
        std::cout << "---" << std::endl;
    }
}

void TalkList::insertTalk(short hours, short minutes, short seconds,const string title, const string overview){
    talkEntries.push_back(createTalk(hours, minutes, seconds, title, overview));
}

void TalkList::listTalksContainingTitle(const string keyTitle){
    bool found = false;

    for (const Talk* talk : talkEntries) {
        if (talk->title.find(keyTitle) != std::string::npos) {
            printTalk(talk);
            found = true;
        }
    }

    if (!found) {
        std::cout << "No such talk on record.\n";
    }
}

void TalkList::saveTalksToFile(const string filename){
     std::ofstream outputFile(filename, std::ios::trunc);

    if (!outputFile.is_open()) {
        std::cout << "Error: Unable to open the file for writing." << std::endl;
        return;
    }

    for (const Talk* talk : talkEntries) {
        outputFile << "**Duration:** " << talk->hours << " hour, " << talk->minutes << " minutes, " << talk->seconds << " seconds\n";
        outputFile << "**Talk Title:** \"" << talk->title << "\"\n";
        outputFile << "**Overview:** " << talk->overview << "\n---\n";
    }

    outputFile.close();
}