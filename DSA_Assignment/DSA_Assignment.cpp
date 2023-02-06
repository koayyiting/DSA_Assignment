//======================================================================
// Student Name & ID : Ng Zi Yi (S10222211K), Koay Yi Ting (S10221765G) 
//      Module Group : P03
//       Team Number : Team 8
//======================================================================
// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string.h>
#include <fstream>
//#include <vector>
#include <sstream>
//#include <ctime>
#include "Topic.h"
#include "Dictionary.h"
#include "Account.h"
#include "ListTopic.h"
#include "ListPost.h"
#include "ListReply.h"
#include "Post.h"
#include "Forum.h"

using namespace std;

Dictionary d;
ListTopic topicList;
ListPost postList;
ListReply replyList;
//Forum ForumTopicList;

ListPost userPost;
bool executeOnce = false;

Forum forum;
Topic topic;
Post post;
Reply reply;
Account currentUser;

string displayMainMenu();
string displayForumMenu();
bool login();
void signup();
//void createNewTopic();
//void createPost();
//void printTopicList(ListTopic tlist);

void createNewTopic() {
    string topicTitle;

    //check if topic list is empty
    if (!topicList.isEmpty()) {
        cout << "Existing Topics:" << endl;
    }
    forum.displayTopics();
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
        
    Topic newTopic(topicTitle);
    topicList.add(newTopic);
    forum.addTopic(newTopic);

    ofstream topicFile("topics.txt", ios::app);
    if (topicFile.is_open())
    {
        topicFile << topicTitle << endl;
        topicFile.close();
    }
    else
    {
        cout << "Problem with opening file" << endl;
    }

    system("cls");
}

string topicOption() {
    string option;
    cout << "\n------------------- Topic -------------------\n" << endl;
    if (topicList.isEmpty())
    {
        cout << "No Topic Created" << endl;
    }
    else { forum.displayTopics(); }

    //list all the topics and posts
    cout << "\n---------------------------------------------" << endl;
    cout << "[1] Create a Post" << endl;
    cout << "[2] Create a Reply" << endl;
    cout << "[0] Back" << endl;
    cout << "---------------------------------------------\n" << endl;

    cout << "Enter an Option: ";
    cin >> option;
    return option;
}

void createPost(int topicIndex, Account currentUser)
{
    string postTitle;
    string content;
    //string postTime;
    string username;

    cout << "\n--------------- Create Post ----------------" << endl;

    //create topic object
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter a Post Title: ";
    getline(cin, postTitle);

    cout << "Enter your Post Content: ";
    getline(cin, content);

    time_t currentDateTime; 
    struct tm ti;
    char buffer[30];

    time(&currentDateTime);
    localtime_s(&ti,&currentDateTime);
    strftime(buffer, sizeof(buffer), "%d %b %Y %T", &ti);
    string postTime(buffer);

    username = currentUser.getUsername();
    
    Post newPost(postTitle, content, postTime, username);
    Topic topic = topicList.get(topicIndex);
    postList.add(newPost);
    topic.addPost(newPost);
    topicList.replace(topicIndex,topic);

    string tTitle = topic.getTopicTitle();
    string pTitle = newPost.getPostTitle();
    string pContent = newPost.getPostContent();
    string pTime = newPost.getPostTime();
    string un = newPost.getUsername();

    forum.addPost(tTitle, pTitle, pContent, pTime, un);

    ofstream postFile("posts.txt", ios::app);
    if (postFile.is_open())
    {
        postFile << tTitle << "," << pTitle << "," << pContent << "," << pTime << "," << un << endl;
        postFile.close();
    }

    //cout << "Your post is added! Time: " << postTime << endl;
}

//display all post title [no topic]
void printPostList() 
{
    for (int i = 0; i < postList.getLength(); i++)
    {
        post = postList.get(i);
        cout << i + 1 << ". " << post.getPostTitle() << endl;
    }
}

ListPost getUserPost() 
{
    if (executeOnce == false) {
        for (int i = 0; i < topicList.getLength(); i++) {
            topic = topicList.get(i);
            for (int j = 0; j < topic.getPostList().getLength(); j++)
            {
                post = topic.getPostList().get(j);
                if (post.getUsername() == currentUser.getUsername()) {
                    userPost.add(post);
                    executeOnce = true;
                    
                }
            }
        }
        return userPost;
    }
    else {
        for (int i = 0; i < topicList.getLength(); i++) {
            topic = topicList.get(i);
            for (int j = 0; j < topic.getPostList().getLength(); j++)
            {
                post = topic.getPostList().get(j);
                if (post.getUsername() == currentUser.getUsername()) {
                    return userPost;
                }
            }
        }
        return userPost;
    }
}

//ListPost getUserPost()
//{
//    for (int i = 0; i < topicList.getLength(); i++) {
//        topic = topicList.get(i);
//        for (int j = 0; j < topic.getPostList().getLength(); j++)
//        {
//            post = topic.getPostList().get(j);
//            if (post.getUsername() == currentUser.getUsername()) {
//                userPost.add(post);
//                
//            }
//        }
//    }
//    return userPost;
//}

//display only user post
int printUserPost() {
    int option;
    bool flag = false;
    int postNumber = 1;
    cout << "\n--------------- Your post(s) ----------------\n" << endl;
    for (int i = 0; i < topicList.getLength(); i++) {
        topic = topicList.get(i);
        for (int j = 0; j < topic.getPostList().getLength(); j++)
        {
            post = topic.getPostList().get(j);
            if (post.getUsername() == currentUser.getUsername()) {
                cout << postNumber << ". " << "Topic: " << topic.getTopicTitle() << endl;
                //cout << j << ". " << "Topic: " << topic.getTopicTitle() << endl;
                cout << "   Title: " << post.getPostTitle() << endl;
                cout << "   Content: " << post.getPostContent() << endl;
                cout << endl;
                flag = true;
                postNumber += 1;
            }
        }
    }
    if (flag == false) {
        cout << "No Post Created" << endl;
    }
    cout << "\n---------------------------------------------" << endl;
    cout << "[0] Back" << endl;
    cout << "---------------------------------------------\n" << endl;
    cout << "Enter a Post number to modify or Back: ";
    cin >> option;
    return option;
}

int modifyPost(int postOption)
{
    int option;
    bool flag = false;
    int postIndex = postOption - 1;

    ListPost userPost = getUserPost();

    //getchosenpost: 
    Post selectedPost = userPost.get(postIndex);

    // display selected post
    for (int i = 0; i < topicList.getLength(); i++) {
        topic = topicList.get(i);

        // Check if the post is in the current topic
        for (int j = 0; j < topic.getPostList().getLength(); j++) {
            post = topic.getPostList().get(j);
            if (selectedPost.getUsername() == currentUser.getUsername() && selectedPost.getPostTitle() == post.getPostTitle()) {
                cout << "\nSelected post: " << endl;
                cout << "Topic: " << topic.getTopicTitle() << endl;
                cout << "Title: " << post.getPostTitle() << endl;
                cout << "Content: " << post.getPostContent() << endl;
                cout << endl;
                flag = true;
                break;
            }
        }
        if (flag) {
            break;
        }
    }

    if (!flag) {
        cout << "Error: selected post not found" << endl;
        return 0;
    }

    cout << "\n---------------------------------------------" << endl;
    cout << "[1] Edit" << endl;
    cout << "[2] Delete" << endl;
    cout << "[0] Back" << endl;
    cout << "---------------------------------------------\n" << endl;
    cout << "Enter an option: ";
    cin >> option;
    return option;
}

void editPost(int postOption, Account currentUser) 
{
    string postTitle;
    string content;
    string titleChange;
    string contentChange;

    cout << "\n--------------- Edit Post ----------------" << endl;

    // create a post object
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Do you want to change your Post Title? (y/n): ";
    cin >> titleChange;
    if (titleChange == "n") {
        postTitle = post.getPostTitle();
    }
    else if (titleChange == "y") {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a new Post title: ";
        getline(cin, postTitle);
    }
    
    cout << "Do you want to change your Post Content? (y/n): ";
    cin >> contentChange;
    if (contentChange == "n") {
        content = post.getPostContent();
    }
    else if (contentChange == "y") {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a new Post Content: ";
        getline(cin, content);
    }

    time_t currentDateTime;
    struct tm ti;
    char buffer[30];

    time(&currentDateTime);
    localtime_s(&ti, &currentDateTime);
    strftime(buffer, sizeof(buffer), "%d %b %Y %T", &ti);
    string timeChange;

    ListPost userPost = getUserPost();

    //getchosenpost: 
    Post selectedPost = userPost.get(postOption-1);

    for (int i = 0; i < topicList.getLength(); i++) {
        topic = topicList.get(i);

        // Check if the post is in the current topic
        for (int j = 0; j < topic.getPostList().getLength(); j++) {
            post = topic.getPostList().get(j);
            if (selectedPost.getUsername() == currentUser.getUsername() && selectedPost.getPostTitle() == post.getPostTitle()) {
                Post editedPost(postTitle, content, timeChange, currentUser.getUsername());
                //replace post
                topic.getPostList().replace(j, editedPost);
                //replace topic
                topicList.replace(i, topic);
                //replace post in postlist
                postList.replace(j, editedPost);
                forum.editPost(j, topic.getTopicTitle(), editedPost.getPostTitle(), editedPost.getPostContent(), editedPost.getPostTime(), editedPost.getUsername());
                userPost.replace(postOption, editedPost);
                break;
            }
        }
    }

    cout << "Post edited!" << endl;
    forum.getForum();
}

void deletePost(int postOption) {

    ListPost userPost = getUserPost();

    //getchosenpost: 
    Post selectedPost = userPost.get(postOption - 1);

    for (int i = 0; i < topicList.getLength(); i++) {
        topic = topicList.get(i);

        // Check if the post is in the current topic
        for (int j = 0; j < topic.getPostList().getLength(); j++) {
            post = topic.getPostList().get(j);
            if (selectedPost.getUsername() == currentUser.getUsername() && selectedPost.getPostTitle() == post.getPostTitle()) {
                ListPost postList = topic.getPostList();
                postList.remove(j);
                topic.setPostList(postList);
                topicList.replace(i, topic);
                postList.remove(j);
                forum.deletePost(j, topic.getTopicTitle());
                userPost.remove(postOption - 1);
                break;
            }
        }
        break;
    }

    cout << "Post deleted!" << endl;
    forum.getForum();
}

void createReply(int topicIndex, int postIndex, Account currentUser) {
    string content;
    string username;

    cout << "\n--------------- Create Reply ----------------" << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Content Reply: ";
    getline(cin, content);

    username = currentUser.getUsername();

    Reply newReply(content, username);
    Topic topic = topicList.get(topicIndex);
    ListPost pl = topic.getPostList();
    Post post = pl.get(postIndex);
    replyList.add(newReply);
    post.addReply(newReply);
    pl.replace(postIndex, post);
    topic.setPostList(pl);
    topicList.replace(topicIndex, topic);
    forum.addReply(topic.getTopicTitle(), post.getPostTitle(), post.getPostContent(), post.getPostTime(), post.getUsername(), content, username);

    forum.saveForumReplies();

    //cout << "Your reply is added! Time: " << postTime << endl;
}

// display the options for searching
int searchMenu()
{
    int option;
    cout << "\n------------------ Search -------------------" << endl;
    cout << "[1] Search for a Topic" << endl;
    cout << "[2] Search for a Post" << endl;
    cout << "[3] Search for a User" << endl; // only displays users that have created a post
    cout << "[0] Back" << endl;
    cout << "---------------------------------------------\n" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter an option: ";
    cin >> option;
    return option;
}

// main function that runs the start of program
int main()
{
    // load user account info (username, password) 
    string username;
    string password;
    ifstream accFile("accounts.txt");
    // Check if the file is open
    if (accFile.is_open())
    {
        // Read the file line by line
        while (accFile >> username >> password)
        {
            // Add the username and password to the dictionary
            d.add(username, password);
        }
        // Close the file
        accFile.close();
    }

    // load forum topics
    string topicTitle;
    ifstream topicFile("topics.txt");
    // Check if the file is open
    if (topicFile.is_open())
    {
        // store the entire title (including space) in one string
        while (getline(topicFile, topicTitle))
        {
            // Add the topic title to the list
            topicList.add(topicTitle);
            forum.addTopic(topicTitle);
        }
        // Close the file
        topicFile.close();
    }

    // load forum posts
    ifstream postFile("posts.txt");
    string tTitle, pTitle, pContent, postTime, un;
    // Check if the file is open
    if (postFile.is_open())
    {
        // store the entire post along with the topic title its in (including space) in one string, and seperate the variables by comma
        while (getline(postFile, tTitle, ',') && getline(postFile, pTitle, ',') && getline(postFile, pContent, ',') && getline(postFile, postTime, ',') && getline(postFile, un))
        {
            // create a post object and add it to the list
            Post post(pTitle, pContent, postTime, un);

            // add the post to the correct topic
            for (int i = 0; i < topicList.getLength(); i++)
            {
                if (topicList.get(i).getTopicTitle() == tTitle)
                {
                    Topic foundTopic = topicList.get(i);
                    foundTopic.addPost(post);
                    postList.add(post);
                    topicList.replace(i, foundTopic);
                    forum.addPost(tTitle, pTitle, pContent, postTime, un);
                    break;
                }
            }
        }
        // Close the file
        postFile.close();
    }

    //load forum replies
    ifstream replyFile("replies.txt");
    string trTitle, prTitle, rContent, rUsername;
    if (replyFile.is_open())
    {     
        while (getline(replyFile, trTitle, ',') && getline(replyFile, prTitle, ',') && getline(replyFile, rContent, ',') && getline(replyFile, rUsername))
        {
            for (int i = 0; i < topicList.getLength(); i++)
            {
                topic = topicList.get(i);
                if (topic.getTopicTitle() == trTitle)
                {
                    ListPost postlist = topic.getPostList();
                    for (int j = 0; j < postlist.getLength(); j++)
                    {
                        Post post = postlist.get(j);
                        if (post.getPostTitle() == prTitle)
                        {
                            Reply newReply(rContent, rUsername);
                            replyList.add(newReply);
                            forum.addReply(trTitle, prTitle, post.getPostContent(), post.getPostTime(), post.getUsername(), rContent, rUsername);
                            post.addReply(newReply);
                        }
                    }
                }
            }
        }
        replyFile.close();
    }


    bool status1 = true;
    bool status2 = true;
    bool status1_2 = true;
    while (status1_2) {
        while (status1) {
            status2 = true;
            string mainMenuOption = displayMainMenu();
            if (mainMenuOption == "1") {
                if (login() == true) {
                    status1 = false;
                    //system("cls");
                }
                else {
                    status2 = false;
                }
            }
            else if (mainMenuOption == "2") {
                signup();
                //status1 remain true so can loop for main menu option
            }
            else if (mainMenuOption == "3") {
                d.print();
            }
            else if (mainMenuOption == "0") {
                //exit
                status2 = false;
                status1_2 = false;
                cout << "Exiting the program. Byebye!" << endl;
                exit(0);//use this instead of break
            }
            else {
                cout << "Please enter a valid option" << endl;
                //status1 remain true so can loop for main menu option
            }
        }
        // forum display
        while (status2) {
            string forumMenuOption = displayForumMenu();            
            //forum.displayTopics();            
            if (forumMenuOption == "1") {
                createNewTopic();
            }
            else if (forumMenuOption == "2")
            {
                bool status2_2 = true;
                if (topicList.isEmpty()) {
                    cout << "Please create a topic before a post or reply" << endl;
                    status2_2 = false;
                }
                while (status2_2) {
                    //choose a topic to see
                    string topicMenuOption = topicOption();
                    if (topicMenuOption == "0") {
                        status2_2 = false;
                    }
                    else if (topicMenuOption == "1") {
                        int topicIndex;
                        cout << "Please Enter a Topic number: ";
                        cin >> topicIndex;
                        if (topicIndex - 1 <= topicList.getLength() && topicIndex != 0) {
                            createPost(topicIndex - 1, currentUser);
                            status2_2 = false;
                        }
                        else { cout << "Please enter a valid topic number." << endl; }
                    }
                    else if (topicMenuOption == "2") {
                        if (!postList.isEmpty()) {
                            int topicIndex;
                            int postIndex;
                            cout << "Please Enter a Topic number: ";
                            cin >> topicIndex;
                            cout << "Please Enter the Post number of the Topic: ";
                            cin >> postIndex;
                            createReply(topicIndex - 1, postIndex - 1, currentUser);
                        }
                        else {
                            cout << "There is no post to reply to" << endl;
                        }
                        status2_2 = false;
                    }
                    else {
                        cout << "Please Enter a Valid Option!" << endl;
                    }
                }
            }
            else if (forumMenuOption == "3")
            {
                int userPostOption = printUserPost();
                if (userPostOption == 0) {
                    break;//stop if statement
                }
                else 
                {
                    int editOption = modifyPost(userPostOption);
                    if (editOption == 1) {
                        editPost(userPostOption, currentUser);
                    }
                    else if (editOption == 2) {
                        deletePost(userPostOption);
                    }
                }
            }
            else if (forumMenuOption == "4")
            {
                int searchOption = searchMenu();
                string keyword;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "What do you want to search for: ";
                getline(cin, keyword);
                if (searchOption == 1) // search for topic
                {
                    forum.searchTopic(keyword);
                }
                else if (searchOption == 2) // search for post
                {
                    forum.searchPost(keyword);
                }
                else if (searchOption == 3)
                {
                    forum.searchUser(keyword); // search for user
                }
                else if (searchOption == 0) // back
                {
                    break;
                }                
            }
            else if (forumMenuOption == "0") {
                //Exit
                cout << "Logged Out" << endl;
                status1 = true;
                status2 = false;
                //system("cls");
            }
            else {
                //ask for valid option
                cout << "Please enter a valid option" << endl;
            }
        }
    }
}

// Displays the main menu and returns user's option
string displayMainMenu()
{
    cout << "\n----------------- Main Menu -----------------" << endl;
    cout << "Welcome to C++ forum" << endl;
    cout << "[1] Log in" << endl;
    cout << "[2] Sign up" << endl;
    cout << "[3] print accounts (delete ltr)" << endl;
    cout << "[0] Exit program" << endl;
    cout << "---------------------------------------------\n" << endl;

    //user main menu option
    string option;
    cout << "Enter an option: ";
    cin >> option;
    cin.ignore();//dont delete i need
    return option;
}

// Allow users to login. return true if successful login, returns false if login fails.
bool login() 
{
    string username, password;

    cout << "\n------------------- Log In -------------------" << endl;
    cout << "Username: ";//check if username exists
    
    getline(cin, username);
    cout << "Password: ";
    cin >> password;

    if (d.find(username)) {
        string userpwd = d.get(username);
        if (userpwd == password) {
            cout << "\nLogin Successful. Welcome, " << username << endl;
            Account acc(username, password);
            currentUser.setUsername(username);
            currentUser.setPassword(password);
            return true;
        }
        else 
        {
            cout << "Incorrect username or password." << endl;
            return false;
        }
    }
    else {
        cout << "Incorrect username or password." << endl;
        return false;
    }
}

// Allows user to register for an account, checks for duplicate username and writes account info to txt file upon successful registration
void signup()
{
    string username, password;
    
    cout << "\n------------------ Sign Up ------------------" << endl;
    cout << "Please enter your username: "; //need check for duplicate username
    getline(cin, username);
    //check if username exists in dictionary -> if it does display "username is taken, choose a different username"
    if (d.find(username)) 
    {
        system("cls");
        cout << "Username is taken, choose a different username" << endl;
        signup();
    }
    cout << "Please enter your password: ";
    cin >> password;

    Account acc(username, password);
    d.add(username, password);
    ofstream accFile("accounts.txt", ios::app);
    if (accFile.is_open())
    {
        accFile << username << ' ' << password << endl;
        accFile.close();
    }
    else
    {
        cout << "Problem with opening file" << endl;
    }
    system("cls");
    cout << "Sign up is successfull!" << endl;
}

// Displays forum menu and returns user's option
string displayForumMenu() 
{
    cout << "\n------------------- Forum -------------------\n" << endl;
    if (topicList.isEmpty()) 
    {
        cout << "No Topic Created" << endl;
    }
    else { forum.displayTopics(); }

    //list all the topics and posts
    cout << "\n---------------------------------------------" << endl;
    cout << "[1] Create new topic" << endl;
    cout << "[2] Create a Post or Reply" << endl;
    cout << "[3] Your Post(s)" << endl;
    cout << "[4] Search" << endl;
    cout << "[0] Log out" << endl;
    cout << "---------------------------------------------\n" << endl;

    //user forum menu option
    string option;
    cout << "Enter an option: ";
    cin >> option;
    system("cls");
    return option;
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
