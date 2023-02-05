// Topic.cpp – Implementation

#include "Post.h"

Post::Post() { }
Post::Post(string tp, string c, string pt,string un) : title(tp), content(c), postTime(pt),username(un) { }
void Post::setPostTitle(string t) { title = t; }
string Post::getPostTitle() { return title; }
void Post::setPostContent(string c) { content = c; }
string Post::getPostContent() { return content; }
void Post::setPostTime(string pt) { postTime = pt; }
string Post::getPostTime() { return postTime; }
void Post::setUsername(string un) { username = un; }
string Post::getUsername() { return username; }