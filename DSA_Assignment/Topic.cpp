// Topic.cpp – Implementation

#include "Topic.h"

Topic::Topic() { }
Topic::Topic(string t) : title(t) { }
void Topic::setTopic(string t) { title = t; }
string Topic::getTopic() { return title; }
