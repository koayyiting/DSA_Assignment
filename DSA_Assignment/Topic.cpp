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

void Topic::displayPost(ListPost postlist) {
    //cout << "Topic: " << title << endl;
    for (int i = 0; i < postlist.getLength(); i++) {
        Post post = postlist.get(i);
        cout << "     Title: " << post.getPostTitle() << endl;
        cout << "     Content: " << post.getPostContent() << endl;
        cout << "     Datetime: " << post.getPostTime() << endl;
        cout << "     Username: " << post.getUsername() << endl;
    }
}