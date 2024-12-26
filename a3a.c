//Shaunak Sachdev
//SFU Computing ID: ssa516@sfu.ca
//Student ID: 301558905

#ifndef _A4_TALKLIB_HPP_
#define _A4_TALKLIB_HPP_

#include <string> //needed for some string functions
#include <iostream> //to be able to print things
using namespace std; //so you don't have to use std:: all the time

//the structure used for holding one talk entry
typedef struct {
	short hours;
	short minutes;
	short seconds;
	string title;
	string overview;
} Talk;

//Creates a Talk struct variable storing three shorts representing 
// hours, minutes, and seconds respectively, a char* array representing a title,
// and a char* array representing an overview
//Returns the address of the dynamically (i.e., uses malloc) created variable
//For example:
//Given the code (title and overview are Cstrings sotring the proper information):
//Talk* talk = createTalk(1, 27, 10, title, overview);
//printf("%dh%dm%ds\n%s\n%s\n", talk->hours, talk->minutes, talk->seconds, 
//      talk->title, talk->overview);
//will result in an output like this:
//1h27m10s
//AI in Retail: Personalizing the Shopping Experience
//Explore how AI is reshaping the retail industry, focusing on personalized
// recommendations, inventory management, and customer engagement. Discuss the
// potential to enhance customer satisfaction and optimize operations using
// AI-powered solutions.
Talk* createTalk(short hours, short minutes, short seconds,
                            const string title, const string overview);


//Releases the memory created to store the 2 members title and overview using
// the address of a Talk struct variable
//Note that the talk parameter can be NULL
// and if this is the case the function should do nothing.
//This function now also releases the memory used for the Talk struct variable,
// and since string is used there really is no need to handle title and overview.
//To make sure there is no dangling pointers, you should set the pointer to NULL
// right after the function returns.
void deleteTalk(Talk* talk);

//In contrast to Assignment 3, the helper function to look up a talk entry by title (Cstring)
// is moved to a4_talkList, refer to a4_talkList.hpp for details

//helper function printing a talk entry nicely
void printTalk(const Talk* talk);

//In contrast to Assignment 3, we will be using sort from <algorithm> to do the sorting.
// This function takes in a helper function returning a bool value indicating whether 
// the element passed as first argument is considered to go before the second.
//This is the helper function for sort to compare talks by duration
bool compareTalksByDuration(const Talk *p1, const Talk *p2);

//In contrast to Assignment 3, we will be using sort from <algorithm> to do the sorting.
// This function takes in a helper function returning a bool value indicating whether 
// the element passed as first argument is considered to go before the second.
//helper function for sort to compare talks by title (string)
bool compareTalksByTitle(const Talk *p1, const Talk *p2);

#endif