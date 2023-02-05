#include "Topic.h"
#pragma once
#include <iostream>
#include <string>
#include "ListTopic.h"
#include "ListPost.h"
using namespace std;

class Forum 
{
private:
    ListTopic topiclist;
    ListPost postlist;
    Topic topic;
    Post post;

public:
    Forum();
    Forum(ListTopic topiclist);
    //ListTopic getTopicList() { return topiclist; }
    //ListPost getPostList() { return postlist; }

    void addTopic(Topic topic);
    void addPost(string topicTitle, string postTitle, string content, string postTime, string username);
    void displayTopics();

    /*void addTopic(Topic topic) {
        topiclist.add(topic);
    }
    void addPost(string topicTitle, string postTitle, string content, string postTime, string username) {
        for (int i = 0; i < topiclist.getLength(); i++) {
            topic = topiclist.get(i);
            if (topic.getTopicTitle() == topicTitle) {
                Post post(postTitle, content, postTime, username);
                postlist.add(post);
                topic.addPost(post);
                topiclist.replace(i,topic);
                break;
            }
        }
        if (topic.getTopicTitle() != topicTitle) {
            cout << "Error: added wrong topic [could not find topic with title]" << endl;
        }
    }
    void displayTopics() {
            for (int i = 0;i < topiclist.getLength(); i++) {
                topic = topiclist.get(i);
                cout << i + 1 << ". " << topic.getTopicTitle() << endl;
                ListPost postlist = topic.getPostList();
                topic.displayPost(postlist);
            }
        }*/
    };