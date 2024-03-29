// Topic.cpp � Implementation

#include "Topic.h"

Topic::Topic() { }

Topic::Topic(string t) : title(t) { }

ListPost Topic::getPostList() { return postlist; }

void Topic::setPostList(ListPost pl) { postlist = pl; }

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

// display posts in topic [NOT USED]
//void Topic::displayPost(ListPost postlist) {
//    //cout << "Topic: " << title << endl;
//    for (int i = 0; i < postlist.getLength(); i++) {
//        Post post = postlist.get(i);
//        cout << "Post " << i + 1 << ": " << endl;
//        cout << "     Title: " << post.getPostTitle() << endl;
//        cout << "     Content: " << post.getPostContent() << endl;
//        cout << "     Datetime: " << post.getPostTime() << endl;
//        cout << "     Username: " << post.getUsername() << "\n"<< endl;
//    }
//}
