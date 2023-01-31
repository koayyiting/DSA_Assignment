// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include "Topic.h"
#include "Dictionary.h"
#include "Account.h"
#include "List.h"

using namespace std;

TItemType topic;
Dictionary d;
List topicList;

string displayMainMenu();
string displayForumMenu();
void login();
void signup();
void createNewTopic();
void printTopicList(List tlist);

int main()
{
    bool status1 = true;
    bool status2 = true;
    while (status1) {
        string mainMenuOption = displayMainMenu();
        if (mainMenuOption == "1") {
            login();
            status1 = false;
        }
        else if (mainMenuOption == "2") {
            signup();
            //status1 remain true so can loop for main menu option
        }
        else if (mainMenuOption == "0") {
            //exit
            status2 = false;
            cout << "Exiting the program. Byebye!" << endl;
            break;
        }
        else {
            cout << "Please enter a valid option" << endl;
            //status1 remain true so can loop for main menu option
        }
    }
    while (status2) {
        string forumMenuOption = displayForumMenu();
        if (forumMenuOption == "1") {
            createNewTopic();
        }
        else if (forumMenuOption == "2")
        {
            //choose a topic to see
        }
        else if (forumMenuOption == "3")
        {
            //see user's posts
        }
        else if (forumMenuOption == "0") {
            //Exit
            system("cls");
            cout << "Logged Out" << endl;
            status2 = false;
        }
        else {
            //ask for valid option
            cout << "Please enter a valid option" << endl;
        }
    }
}

string displayMainMenu()
{
    cout << "\n----------------- Main Menu -----------------" << endl;
    cout << "Welcome to C++ forum" << endl;
    cout << "[1] Log in" << endl;
    cout << "[2] Sign up" << endl;
    cout << "[3] View Dictionary (delete ltr)" << endl;
    cout << "[0] Exit program" << endl;
    cout << "---------------------------------------------\n" << endl;

    //user main menu option
    string option;
    cout << "Enter an option: ";
    cin >> option;
    return option;
}

void login() 
{
    int count;
    string username, password;
    string userId, pwd;

    cout << "\n------------------- Log In -------------------" << endl;
    cout << "Username: ";//check if username exists
    cin.ignore();
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    /*ifstream input("accounts.txt");

    while (input >> userId >> pwd) 
    {
        if (userId == username && pwd == password) 
        {
            count = 1;
            system("cls");
        }
        input.close();

        if (count == 1) {
            cout << "Login Successful. Welcome, " << username << endl;
            main();
        }
        else 
        {
            cout << "Incorrect username or password." << endl;
            main();
        }
    }*/

    if (d.get(username) == password) //authenticate user -> correct password
    {
        cout << "yay" << endl;
    }
    else //either username doesn't exist or wrong password
    {
        cout << "Incorrect username or password." << endl;
    }
    system("cls");
    cout << "Logged In as " << username << endl;
}

void signup()
{
    string username, password;
    //string userId, pwd;

    system("cls");
    cout << "\n------------------ Sign Up ------------------" << endl;
    cout << "Please enter your username: "; //need check for duplicate username
    cin.ignore();
    getline(cin, username);
    cout << "Please enter your password: "; //if got time do confirm password 
    getline(cin, password);
    Account acc(username, password);
    d.add(username, password);

    /*ofstream f1("accounts.txt", ios::app);
    f1 << userId << ' ' << pwd << endl;*/
    system("cls");
    cout << "Sign Up is successfull!" << endl;
    main();    
}

string displayForumMenu() 
{
    cout << "\n------------------- Forum -------------------\n" << endl;
    if (topicList.isEmpty()) 
    {
        cout << "No Topic Created" << endl;
    }
    else { printTopicList(topicList); }

    //list all the topics and posts
    cout << "\n---------------------------------------------" << endl;
    cout << "[1] Create new topic" << endl;
    cout << "[2] Choose a topic" << endl;
    cout << "[3] Your post(s)" << endl;
    cout << "[0] Exit" << endl;
    cout << "---------------------------------------------\n" << endl;

    //user forum menu option
    string option;
    cout << "Enter an option: ";
    cin >> option;
    system("cls");
    return option;
}

void createNewTopic() 
{
    string topicTitle;

    //check if topic list is empty
    if (!topicList.isEmpty()) {
        cout << "Existing Topics:" << endl;
    }
    printTopicList(topicList);
	cout << "\n--------------- Create Topic ----------------" << endl;

    //create topic object
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter a Topic name: "; //need to validate if topic is duplicated //.proper() + -whitespaces
    getline(cin, topicTitle);

    //check for duplicate topic title
    for (int i = 0; i < topicList.getLength(); i++) {
        topic = topicList.get(i);
        if (topicTitle == topic.getTopicTitle()) {
            cout << "You have entered a Existing Topic Title" << endl;
            return;
        }
    }

    //continue to create a topic object
    int topicId = topicList.getLength();
    string id;
    stringstream ss;
    ss << topicId;
    ss >> id;
    Topic newTopic(id, topicTitle);
    topicList.add(newTopic);
    system("cls");
    #pragma region link on how to use for stringstream
    //https://www.educative.io/answers/how-to-convert-an-int-to-a-string-in-cpp
    #pragma endregion
}

void printTopicList(List tlist) 
{
    for (int i = 0; i < tlist.getLength(); i++)
    {
        topic = tlist.get(i);
        cout << i + 1 << ". " << topic.getTopicTitle() << endl;
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
