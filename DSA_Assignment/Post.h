// Post.h � Specification
#pragma once            // generated by Visual Studio
#include <iostream>     // for input/output
#include <string>       // for string class
#include <ctime>
#include "ListReply.h"

using namespace std;

class Post
{
// data (properties)
private:
    string title;
    string content;
    string postTime; //not sure if is this format [time_t now = time(0); to get current time]
    string username;
    ListReply replylist;

// functions (methods)
public:
    Post();	                      
    Post(string tp, string c, string pt, string un);
    void setPostTitle(string t);    
    string getPostTitle();        
    void setPostContent(string c);  
    string getPostContent();      
    void setPostTime(string pt);     
    string getPostTime();
    void setUsername(string un);
    string getUsername();
    void addReply(Reply reply);
    void displayReply(ListReply replylist);
};