//Shaunak Sachdev
//SFU Computing ID: ssa516@sfu.ca
//Student ID: 301558905

#include <iostream>
#include "a4_talkList.hpp"
using namespace std;

void readTalksFile(string file, TalkList *newList)
{

    ifstream newFile(file);
    short hours = 0, minutes = 0, seconds = 0;
    string Title = "", Overview = "";

    if (!newFile.is_open())
    {
        cout << "Error: Unable to open the file." << endl;
        return;
    }
    string line;
    while (getline(newFile, line))
    {
        if (line == "---")
        {
            Overview = Overview.substr(14);
            Title = Title.substr(17, Title.length() - 18);
            newList->insertTalk(hours, minutes, seconds, Title, Overview);
        }
        else
        {
            sscanf(line.c_str(), "**Duration:** %hd hour, %hd minutes, %hd seconds\n", &hours, &minutes, &seconds);
            getline(newFile, Title);
            getline(newFile, Overview);
        }
    }
    newFile.close();
}

int main()
{
    int Option = 0;
    string fileName = "", titleInput = "";
    string Title = "", Overview = "";
    TalkList *Talk = new TalkList();
    short hours = 0, minutes = 0, seconds = 0;

    cout<<"==============================================\n";
    cout<<"================== CMPT 125 ==================\n";
    cout<<"================== [Name] ==================\n";
    cout<<"================== [Student ID] =================\n";
    cout<<"================= [Email]@sfu.ca ===============\n";
    cout<<"==============================================\n";

    do
    {
        cout << "Press numbers 1-7 for the following options and then enter: " << endl;
        cout << "1) to load a talks file." << endl;
        cout << "2) to list talks sorted by duration." << endl;
        cout << "3) to list talks sorted by title." << endl;
        cout << "4) to look up a talk." << endl;
        cout << "5) to add a talk." << endl;
        cout << "6) to save a talks file." << endl;
        cout << "7) to terminate the program." << endl;
        cout << "Choose Option : ";
        cin >> Option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (Option)
        {
        case 1:
            cout << "Enter the full name of the talks file (with Extension) : ";
            getline(cin, fileName);
            readTalksFile(fileName, Talk);
            cout << "Total Entries read : " << Talk->getSize();
            break;

        case 2:
            if (Talk->getSize() > 0)
            {
                Talk->listTalksByDuration();
            }
            else
            {
                cout << "No Talks File Loaded. Load one first\n";
            }
            break;

        case 3:
            if (Talk->getSize() > 0)
            {

                Talk->listTalksByTitle();
            }
            else
            {
                cout << "No Talks File Loaded. Load one first\n";
            }

            break;

        case 4:
            if (Talk->getSize() > 0)
            {
                cout << "What is the title of the talk, enter in part or as a whole (50 character max.)? ";
                getline(cin, titleInput);
                Talk->listTalksContainingTitle(titleInput);
            }
            else
            {
                cout << "No Talks File Loaded. Load one first\n";
            }
            break;

        case 5:
            if (Talk->getSize() > 0)
            {
                cout << "What is the number of hours (input 0 or more and press enter)? ";
                cin >> hours;
                while (hours < 0)
                {
                    cout << "Enter a number greater than 0 : ";
                    cin >> hours;
                }

                cout << "What is the number of minutes (input 0-59 and press enter)? ";
                cin >> minutes;
                while (minutes < 0 || minutes > 59)
                {
                    cout << "Enter a number between 0 and 59 : ";
                    cin >> minutes;
                }

                cout << "What is the number of seconds (input 0-59 and press enter)? ";
                cin >> seconds;
                while (seconds < 0 || seconds > 59)
                {
                    cout << "Enter a number between 0 and 59 : ";
                    cin >> seconds;
                }

                cout << "What is the title of the talk? ";
                getline(cin, Title);
                cout << "what is the overview of the talk? ";
                getline(cin, Overview);

                cout<<"you have Entered : "<<hours<<"h"<<minutes<<"m"<<seconds<<"s\n";
                cout<<"Title : "<<Title<<endl;
                cout<<"Overview : "<<Overview<<endl;
                Talk->insertTalk(hours, minutes, seconds, Title, Overview);
            }
            else
            {
                cout << "No Talks File Loaded. Load one first\n";
            }

            break;

        case 6:
            if (Talk->getSize() > 0)
            {
                cout << "Enter the full name of the save file (with extension): ";
                getline(cin, fileName);
                Talk->saveTalksToFile(fileName);
                cout << Talk->getSize() << " entries saved.\n";
            }
            else
            {
                cout << "No Talks File Loaded. Load one first\n";
            }
            break;
        }
    } while (Option != 7);

    delete Talk;
}