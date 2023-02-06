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
    //ListReply replylist;
    Topic topic;
    Post post;
    //Reply reply

public:
    Forum();
    Forum(ListTopic topiclist);
    //ListTopic getTopicList() { return topiclist; }
    //ListPost getPostList() { return postlist; }

    void addTopic(Topic topic);
    void addPost(string topicTitle, string postTitle, string content, string postTime, string username);
    void editPost(int postIndex, string topicTitle, string postTitle, string content, string postTime, string username);
    void deletePost(int postIndex, string topicTitle);
    void addReply(string topicTitle, string postTitle, string content, string postTime, string postUser, string replyContent, string replyUser);
    void displayTopics();
    void getForum();
    void saveForumReplies();
    void searchTopic(string keyword);
    void searchPost(string keyword);
    void searchUser(string keyword);
    //void loadForumReplies();
    //void displayOwnTPosts(string username);

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