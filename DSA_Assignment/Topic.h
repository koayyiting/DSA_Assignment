// Topic.h � Specification
#pragma once            // generated by Visual Studio
#include <iostream>     // for input/output
#include <string>       // for string class
#include <ctime>
#include "ListPost.h"
//#include "Post.h"
using namespace std;
class Topic
{
    // data (properties)
private:
    string title;
    ListPost postlist;

    // functions (methods)
public:
    Topic();	                    // default constructor
    Topic(string title);	        // parameterized constructor
    ListPost getPostList();
    void setPostList(ListPost pl);
    void setTopicTitle(string title);     // set topic name
    string getTopicTitle();         // get topic name
    //void addPost(string tp, string c, string pt) {
    //    Post post(tp, c, pt);
    //    postlist.add(post);
    //}
    void addPost(Post post);
    void editPost(int index, Post post);
    void deletePost(int index);

    //[NOT USED]
    //void displayPost(ListPost postlist);
    /*void displayOwnPost(ListPost postlist, string username);
    bool displayOwnPostCheck(ListPost postlist, string username);*/
};


