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

void Forum::editPost(int postIndex,string topicTitle, string postTitle, string content, string postTime, string username)
{
    for (int i = 0; i < topiclist.getLength(); i++) {
        topic = topiclist.get(i);
        if (topic.getTopicTitle() == topicTitle) {
            Post post(postTitle, content, postTime, username);
            postlist.replace(postIndex,post);
            topic.editPost(postIndex, post);
            topiclist.replace(i, topic);
            break;
        }
    }
}

void Forum::deletePost(int postIndex, string topicTitle)
{
    for (int i = 0; i < topiclist.getLength(); i++) {
        topic = topiclist.get(i);
        if (topic.getTopicTitle() == topicTitle) {
            postlist.remove(postIndex);
            topic.deletePost(postIndex);
            topiclist.replace(i, topic);
            break;
        }
    }
}

void Forum::addReply(string topicTitle, string postTitle, string content, string postTime, string postUser, string replyContent, string replyUser) {
    for (int i = 0; i < topiclist.getLength(); i++) {
        topic = topiclist.get(i);
        if (topic.getTopicTitle() == topicTitle) {
            for (int j = 0; j < topic.getPostList().getLength(); j++) {
                Post post = topic.getPostList().get(j);
                if (post.getPostTitle() == postTitle) {
                    Reply reply(replyContent, replyUser);
                    post.addReply(reply);
                    topic.getPostList().replace(j, post);
                    topiclist.replace(i, topic);
                    break;
                }
            }
            break;
        }
    }
    if (topic.getTopicTitle() != topicTitle) {
        cout << "Error: added reply to wrong post [could not find topic with title]" << endl;
    }
}

//void Forum::displayTopics() 
//{
//    for (int i = 0; i < topiclist.getLength(); i++) {
//        topic = topiclist.get(i);
//        cout << i + 1 << ". " << topic.getTopicTitle() << endl;
//        ListPost postlist = topic.getPostList();
//        topic.displayPost(postlist);
//        for (int j = 0; j < postlist.getLength(); j++) {
//            Post post = postlist.get(j);
//            //cout << "\t" << j + 1 << ". " << post.getPostTitle() << endl;
//            ListReply replylist = post.getReplyList();
//            post.displayReply(replylist);
//        }
//    }
//}

void Forum::displayTopics()
{
    for (int i = 0; i < topiclist.getLength(); i++) {
        topic = topiclist.get(i);
        cout << i + 1 << ". " << topic.getTopicTitle() << endl;
        ListPost postlist = topic.getPostList();
        if (!postlist.isEmpty()) { cout << "   Post: " << endl; }
        for (int j = 0; j < postlist.getLength(); j++) {
            Post post = postlist.get(j);
            cout << "   " << j + 1 << ". Title: " << post.getPostTitle() << endl;
            cout << "      Content: " << post.getPostContent() << endl;
            ListReply replylist = post.getReplyList();
            if (!replylist.isEmpty()) { cout << "      Reply: " << endl; }
            for (int k = 0; k < replylist.getLength(); k++) {
                Reply reply = replylist.get(k);
                cout << "      " << k + 1 << ". " << reply.getReplyContent() << endl;
            }   
        }
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