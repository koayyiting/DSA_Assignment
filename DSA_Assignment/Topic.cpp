// Topic.cpp – Implementation

#include "Topic.h"

Topic::Topic() { }
Topic::Topic(string t) : title(t) { }
void Topic::setTopicTitle(string t) { title = t; }
string Topic::getTopicTitle() { return title; }
void addPost(Post post) {}
//void displayPost(ListPost postlist) {}

#pragma region topicId
//Topic::Topic() { }
//Topic::Topic(string tid, string t) : topicId(tid), title(t) { }
//void Topic::setTopicId(string tid) { topicId = tid; }
//string Topic::getTopicId() { return topicId; }
//void Topic::setTopicTitle(string t) { title = t; }
//string Topic::getTopicTitle() { return title; }
#pragma endregion