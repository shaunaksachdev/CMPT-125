//Shaunak Sachdev
//SFU Computing ID: ssa516@sfu.ca
//Student ID: 301558905

#ifndef _A4_TALKLIST_HPP_
#define _A4_TALKLIST_HPP_

#include "a4_talklib.hpp" //to recognize and use all the talk code

#include <vector> //to store Talk* as items and provide array-like functions
#include <string> //to handle string variables like title and overview
#include <algorithm> //to be able to sort things
#include <iostream> //to be able to print things
#include <fstream> //to be able to do file I/O
using namespace std; //so you don't have to use std:: all the time

//The definition of the TalkList class
class TalkList {
    private:
        vector<Talk*> talkEntries; //storing the Talk*

    public:
        //constructor
        TalkList();
        //destructor
        // use this to free up all the Talk* items
        ~TalkList();
        //return the size of the list (i.e., number of talks)
        int getSize();
        //list talks sorted by duration
        // call the sort function here and use the helper functions
        // from a4_talklib
        void listTalksByDuration();
        //list talks sorted by title
        // call the sort function here and use the helper functions
        // from a4_talklib
        void listTalksByTitle();
        //create and insert a Talk entry to the list
        // first use createTalk to create a Talk entry,
        // then use the push_back method of vector to insert
        void insertTalk(short hours, short minutes, short seconds,
                            const string title, const string overview);
        //list talks that have title containing the keyTitle as substring
        // use the find method of string for matching, look up string::npos
        // reference: https://cplusplus.com/reference/string/string/find/
        void listTalksContainingTitle(const string keyTitle);
        //save all the talks into a file using the sample format
        void saveTalksToFile(const string filename);
};

#endif