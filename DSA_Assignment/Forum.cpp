// Forum.cpp – Implementation

#include "Forum.h"

Forum::Forum() { }

Forum::Forum(ListTopic topiclist) : topiclist(topiclist) { }

void Forum::addTopic(Topic topic) { topiclist.add(topic); }

void Forum::addPost(string topicTitle, string postTitle, string content, string postTime, string username)
{ 
    for (int i = 0; i < topiclist.getLength(); i++) {
        topic = topiclist.get(i);
        if (topic.getTopicTitle() == topicTitle) {
            Post post(postTitle, content, postTime, username);
            postlist.add(post);
            topic.addPost(post);
            topiclist.replace(i, topic);
            break;
        }
    }
    if (topic.getTopicTitle() != topicTitle) {
        cout << "Error: added wrong topic [could not find topic with title]" << endl;
    }
}

void Forum::displayTopics() 
{
    for (int i = 0; i < topiclist.getLength(); i++) {
        topic = topiclist.get(i);
        cout << i + 1 << ". " << topic.getTopicTitle() << endl;
        ListPost postlist = topic.getPostList();
        topic.displayPost(postlist);
    }
}

//void Forum::displayOwnTPosts(string username)
//{
//    for (int i = 0; i < topiclist.getLength(); i++) {
//        
//        topic = topiclist.get(i);
//        if (topic.displayOwnPostCheck(postlist, username)) {
//            cout << "Topic: " << i + 1 << ". " << topic.getTopicTitle() << endl;
//            ListPost postlist = topic.getPostList();
//            topic.displayOwnPost(postlist, username);
//        }
//    }
//}