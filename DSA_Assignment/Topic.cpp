// Topic.cpp – Implementation

#include "Topic.h"

Topic::Topic() { }

Topic::Topic(string t) : title(t) { }

ListPost Topic::getPostList() { return postlist; }

void Topic::setTopicTitle(string t) { title = t; }

string Topic::getTopicTitle() { return title; }

void Topic::addPost(Post post) {
    postlist.add(post);
}

void Topic::editPost(int index, Post post) {
    postlist.replace(index, post);
}

void Topic::deletePost(int index) {
    postlist.remove(index);
}

void Topic::displayPost(ListPost postlist) {
    //cout << "Topic: " << title << endl;
    for (int i = 0; i < postlist.getLength(); i++) {
        Post post = postlist.get(i);
        cout << "Post " << i + 1 << ": " << endl;
        cout << "     Title: " << post.getPostTitle() << endl;
        cout << "     Content: " << post.getPostContent() << endl;
        cout << "     Datetime: " << post.getPostTime() << endl;
        cout << "     Username: " << post.getUsername() << "\n"<< endl;
    }
}

//void Topic::displayOwnPost(ListPost postlist, string username) {
//    //cout << "Topic: " << title << endl;
//    for (int i = 0; i < postlist.getLength(); i++) {
//        Post post = postlist.get(i);
//        if (post.getUsername() == username) {
//            cout << "     Title: " << post.getPostTitle() << endl;
//            cout << "     Content: " << post.getPostContent() << endl;
//            cout << "     Datetime: " << post.getPostTime() << endl;
//            cout << "     Username: " << post.getUsername() << "\n" << endl;
//        }
//    }
//}
//
//bool Topic::displayOwnPostCheck(ListPost postlist, string username) {
//    //cout << "Topic: " << title << endl;
//    bool flag = false;
//    for (int i = 0; i < postlist.getLength(); i++) {
//        Post post = postlist.get(i);
//        if (post.getUsername() == username) {
//            flag = true;
//        }
//    }
//    return flag;
//}
