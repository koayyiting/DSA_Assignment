// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include "Topic.h"
#include "Dictionary.h"

string displayMainMenu()
{
    cout << "\n----------------- Main Menu -----------------" << endl;
    cout << "Welcome to C++ forum" << endl;
    cout << "[1] Log in" << endl;
    cout << "[2] Sign up" << endl;
    cout << "[0] Exit program" << endl;
    cout << "---------------------------------------------\n" << endl;

    string option;
    cout << "Enter an option: ";
    cin >> option;
    return option;
}

string displayForumMenu() 
{
    cout << "\n------------------- Forum -------------------" << endl;
    //list all the topics and posts
    cout << "---------------------------------------------" << endl;
    cout << "[1] Create new topic" << endl;
    cout << "[2] Choose a topic" << endl;
    cout << "[3] Your post(s)" << endl;
    cout << "[0] Exit" << endl;
    cout << "---------------------------------------------\n" << endl;

    string option;
    cout << "Enter an option: ";
    cin >> option;
    return option;
}

void createNewTopic() 
{
    //create new topic
}


int main()
{
    string mainMenuOption = displayMainMenu();
    if (mainMenuOption == "1") {
        cout << "Log in" << endl;
        string forumMenuOption = displayForumMenu();
        if (forumMenuOption == "1") {
            //create new topic
        }
        else if(forumMenuOption == "2")
        {
            //choose a topic to see
        }
        else if (forumMenuOption == "3") 
        {
            //see user's posts
        }
        else if (forumMenuOption == "0") {
            //Exit
        }
        else {
            //ask for valid option
        }
    }
    else if (mainMenuOption == "2") {
        cout << "Sign up" << endl;
    }
    else if (mainMenuOption == "0") {
        cout << "Exit program" << endl;
    }
    else {
        cout << "Please enter a valid option" << endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
