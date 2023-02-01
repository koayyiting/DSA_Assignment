// Topic.cpp – Implementation

#include "Post.h"

Post::Post() { }
Post::Post(string t, string c, time_t pt) : title(t), content(c), postTime(pt) { }
void Post::setPostTitle(string t) { title = t; }
string Post::getPostTitle() { return title; }
void Post::setPostContent(string c) { content = c; }
string Post::getPostContent() { return content; }
void Post::setPostTime(time_t pt) { postTime = pt; }
time_t Post::getPostTime() { return postTime; }