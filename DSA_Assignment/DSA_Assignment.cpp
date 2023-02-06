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
    string postTime;
    string username;

    cout << "\n--------------- Create Post ----------------" << endl;

    //create topic object
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter a Post title: ";
    getline(cin, postTitle);

    cout << "Enter your post Content: ";
    getline(cin, content);

    cout << "Enter your post Time: ";
    //time_t ct = time(0);
    //postTime = ctime(&ct);
    getline(cin, postTime);

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

//display only user post
int printUserPost() {
    int option;
    bool flag = false;
    cout << "\n--------------- Your post(s) ----------------\n" << endl;
    for (int i = 0; i < topicList.getLength(); i++) {
        topic = topicList.get(i);
        for (int j = 0; j < topic.getPostList().getLength(); j++)
        {
            post = topic.getPostList().get(j);
            if (post.getUsername() == currentUser.getUsername()) {
                cout << j + 1 << ". " << "Topic: " << topic.getTopicTitle() << endl;
                cout <<  "   Title: " << post.getPostTitle() << endl;
                cout << "   Content: " << post.getPostContent() << endl;
                cout << endl;
                flag = true;
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

    // display selected post
    for (int i = 0; i < topicList.getLength(); i++) {
        topic = topicList.get(i);

        // Check if the post is in the current topic
        for (int j = 0; j < topic.getPostList().getLength(); j++) {
            post = topic.getPostList().get(j);
            if (post.getUsername() == currentUser.getUsername() && j == postIndex) {
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
        cout << "Enter a new post Content: ";
        getline(cin, content);
    }

    Post editedPost(postTitle, content, "2.30pm", currentUser.getUsername());
    post = topic.getPostList().get(postOption - 1);
    //post.setPostTitle(postTitle);
    //post.setPostContent(content);
    topic.getPostList().replace(postOption - 1, editedPost);
    topicList.replace(postOption - 1, topic);
    postList.replace(postOption - 1, editedPost);
    forum.editPost(postOption-1,topic.getTopicTitle(),editedPost.getPostTitle(),editedPost.getPostContent(),editedPost.getPostTime(),editedPost.getUsername());

    cout << "Post edited!" << endl;
    
    //Post editedPost = postlist.get(PostOption - 1);
    

    //Post updatedPost = postList.get(postOption - 1);
    //updatedPost.setPostTitle(postTitle);
    //updatedPost.setPostContent(content);
    //postList.replace(postOption - 1, updatedPost);

    //cout << "Post updated successfully." << endl;

    //int option = modifyPost(postOption);

    //if (option == 1) {
    //    //Edit code
    //    int topicIndex = 0, postIndex = postOption - 1;
    //    for (int i = 0; i < topicList.getLength(); i++) {
    //        topic = topicList.get(i);
    //        if (postIndex >= topic.getPostList().getLength()) {
    //            postIndex -= topic.getPostList().getLength();
    //            topicIndex++;
    //        }
    //        else {
    //            break;
    //        }
    //    }
    //    cout << "Enter the new post title: ";
    //    string postTitle;
    //    getline(cin, postTitle);
    //    cout << "Enter the new post content: ";
    //    string postContent;
    //    getline(cin, postContent);
    //    string postTime;
    //    cout << "Enter your post Time: ";
    //    getline(cin, postTime);

    //    string username = currentUser.getUsername();

    //    post = topic.getPostList().get(postIndex);
    //    post.setPostTitle(postTitle);
    //    post.setPostContent(postContent);
    //    topic.getPostList().replace(postIndex, post);
    //    topicList.replace(topicIndex, topic);
    //}
}

void deletePost(int postOption) {
    post = topic.getPostList().get(postOption - 1);
    //post.setPostTitle(postTitle);
    //post.setPostContent(content);
    topic.getPostList().remove(postOption - 1);
    topicList.replace(postOption - 1,topic);
    postList.remove(postOption - 1);
    forum.deletePost(postOption - 1, topic.getTopicTitle());

    cout << "Post deleted!" << endl;
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
    Post post = postList.get(postIndex);
    replyList.add(newReply);
    forum.addReply(topic.getTopicTitle(), post.getPostTitle(), post.getPostContent(), post.getPostTime(), post.getUsername(), content, username);

    //cout << "Your reply is added! Time: " << postTime << endl;
}


int main()
{
    //Topic t1("Linked List");
    //Topic t2("DSA");
    //forum.addTopic(t1);
    //forum.addTopic(t2);
    //Post p1("Post 1", "Content 1", "MON");
    //Post p2("Post 2", "Content 2", "TUES");
    //Post p3("Post 3", "Content 3", "WED");
    //t1.addPost(p1);
    //t1.addPost(p2);
    //t2.addPost(p3);
    //forum.addPost(t1.getTopicTitle(), p1.getPostTitle(), p1.getPostContent(), p1.getPostTime());
    //forum.addPost(t1.getTopicTitle(), p2.getPostTitle(), p2.getPostContent(), p2.getPostTime());
    //forum.addPost(t2.getTopicTitle(), p3.getPostTitle(), p3.getPostContent(), p3.getPostTime());
    //forum.displayTopics();


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

    ifstream postFile("posts.txt");
    string tTitle, pTitle, pContent, postTime, un;
    // Check if the file is open
    if (postFile.is_open())
    {
        // Read the file line by line
        while (getline(postFile, tTitle, ',') && getline(postFile, pTitle, ',') && getline(postFile, pContent, ',') && getline(postFile, postTime, ',') && getline(postFile, username))
        {
            // create a post object and add it to the list
            Post post(pTitle, pContent, postTime, username);

            // add the post to the correct topic
            for (int i = 0; i < topicList.getLength(); i++)
            {
                if (topicList.get(i).getTopicTitle() == tTitle)
                {
                    topicList.get(i).addPost(post);
                    postList.add(post);
                    topic.addPost(post);
                    topicList.replace(i, topicList.get(i));
                    forum.addPost(tTitle, pTitle, pContent, postTime, username);
                    break;
                }
            }
        }
        // Close the file
        postFile.close();
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
    cout << "[0] Log out" << endl;
    cout << "---------------------------------------------\n" << endl;

    //user forum menu option
    string option;
    cout << "Enter an option: ";
    cin >> option;
    system("cls");
    return option;
}

//void createNewTopic() 
//{
//    string topicTitle;
//
//    //check if topic list is empty
//    if (!topicList.isEmpty()) {
//        cout << "Existing Topics:" << endl;
//    }
//    printTopicList(topicList);
//	cout << "\n--------------- Create Topic ----------------" << endl;
//
//    //create topic object
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    cout << "Enter a Topic name: "; //need to validate if topic is duplicated //.proper() + -whitespaces
//    getline(cin, topicTitle);
//
//    //check for duplicate topic title
//    for (int i = 0; i < topicList.getLength(); i++) {
//        topic = topicList.get(i);
//        if (topicTitle == topic.getTopicTitle()) {
//            cout << "You have entered a Existing Topic Title" << endl;
//            return;
//        }
//    }
//
//    //continue to create a topic object
//    int topicId = topicList.getLength();
//    
//    Topic newTopic(topicTitle);
//    topicList.add(newTopic);
//    system("cls");
//
//    #pragma region topic id
//    /*Topic newTopic(id,topicTitle);
//    string id;
//    stringstream ss;
//    ss << topicId;
//    ss >> id;*/
//    #pragma endregion
//
//    #pragma region link on how to use for stringstream
//    //https://www.educative.io/answers/how-to-convert-an-int-to-a-string-in-cpp
//    #pragma endregion
//}
//
//void printTopicList(List tlist) 
//{
//    for (int i = 0; i < tlist.getLength(); i++)
//    {
//        topic = tlist.get(i);
//        cout << i + 1 << ". " << topic.getTopicTitle() << endl;
//    }
//}
//
//void createPost() 
//{
//    string postTitle;
//    string content;
//    time_t postTime;
//
//    cout << "\n--------------- Create Topic ----------------" << endl;
//
//    //create topic object
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    cout << "Enter a Post title: "; 
//    getline(cin, postTitle);
//
//    cout << "Enter your post Content: ";
//    getline(cin, content);

//void printTopicList(ListTopic tlist)
//{
//    for (int i = 0; i < tlist.getLength(); i++)
//    {
//        topic = tlist.get(i);
//        cout << i + 1 << ". " << topic.getTopicTitle() << endl;
//    }
//}

//void createPost() 
//{
//    string postTitle;
//    string content;
//    time_t postTime;
//
//    cout << "\n--------------- Create Topic ----------------" << endl;
//
//    //create topic object
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    cout << "Enter a Post title: "; 
//    getline(cin, postTitle);
//
//    cout << "Enter your post Content: ";
//    getline(cin, content);
//
//    time_t now = time(0);
//
//    Post newPost(postTitle, content, now);
//    //postList.push_back(newPost);
//    system("cls");
//}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
