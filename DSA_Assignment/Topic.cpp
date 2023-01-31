// Topic.cpp – Implementation

#include "Topic.h"

Topic::Topic() { }
Topic::Topic(string tid, string t) : topicId(tid), title(t) { }
void Topic::setTopicId(string tid) { topicId = tid; }
string Topic::getTopicId() { return topicId; }
void Topic::setTopicTitle(string t) { title = t; }
string Topic::getTopicTitle() { return title; }