// Forum.cpp – Implementation

#include "Forum.h"
#include <fstream>

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
        cout << i + 1 << ". Topic: " << topic.getTopicTitle() << endl;
        ListPost postlist = topic.getPostList();
        if (!postlist.isEmpty()) { cout << "   Post: " << endl; }
        for (int j = 0; j < postlist.getLength(); j++) {
            Post post = postlist.get(j);
            cout << "   " << j + 1 << ". Title: " << post.getPostTitle() << endl;
            cout << "      Content: " << post.getPostContent() << endl;
            cout << "      Username: " << post.getUsername() << "\n" << endl;
            ListReply replylist = post.getReplyList();
            if (!replylist.isEmpty()) { cout << "      Reply: " << endl; }
            for (int k = 0; k < replylist.getLength(); k++) {
                Reply reply = replylist.get(k);
                cout << "      " << k + 1 << ". " << reply.getReplyContent() << "\n" << endl;
            }   
        }
    }
}

void Forum::getForum() // to put in the posts.txt file
{
    ofstream postFile("posts.txt");
    if (postFile.is_open())
    {
        for (int i = 0; i < topiclist.getLength(); i++) {

            topic = topiclist.get(i);
            ListPost postlist = topic.getPostList();
            for (int j = 0; j < postlist.getLength(); j++) {// for each post in topic
                Post post = postlist.get(j);
                string tTitle = topic.getTopicTitle();
                string pTitle = post.getPostTitle();
                string pContent = post.getPostContent();
                string pTime = post.getPostTime();
                string pUsername = post.getUsername();
                postFile << tTitle << "," << pTitle << "," << pContent << "," << pTime << "," << pUsername << endl;
            }            
        }
        postFile.close();
    }
}

void Forum::saveForumReplies() //save replies to replies.txt
{
    ofstream replyFile("replies.txt");
    if (replyFile.is_open())
    {
        string trTitle, prTitle, rContent, rUsername;

        for (int i = 0; i < topiclist.getLength(); i++) {

            topic = topiclist.get(i);
            ListPost postlist = topic.getPostList();

            for (int j = 0; j < postlist.getLength(); j++) {
                Post post = postlist.get(j);

                ListReply replylist = post.getReplyList();

                for (int k = 0; k < replylist.getLength(); k++) {
                    Reply reply = replylist.get(k);
                    string trTitle = topic.getTopicTitle();
                    string prTitle = post.getPostTitle();
                    string rContent = reply.getReplyContent();
                    string rUsername = reply.getUsername();
                    replyFile << trTitle << "," << prTitle << "," << rContent << "," << rUsername << endl;
                }
            }
        }
        replyFile.close();
    }
}

void Forum::searchTopic(string keyword)
{
    int foundTopic = 0;
    string topicTitle;

    cout << "\n----------- Topic Search Results -----------" << endl;
    for (int i = 0; i < topiclist.getLength(); i++)
    {
        topic = topiclist.get(i);
        topicTitle = topic.getTopicTitle();
        if (topicTitle.find(keyword) != string::npos)
        {
            foundTopic = 1;
            cout << "Topic: " << topicTitle << endl;
            ListPost postlist = topic.getPostList();
            if (!postlist.isEmpty()) { cout << "   Post: " << endl; }
            for (int j = 0; j < postlist.getLength(); j++) {
                Post post = postlist.get(j);
                cout << "   " << j + 1 << ". Title: " << post.getPostTitle() << endl;
                cout << "      Content: " << post.getPostContent() << endl;
                cout << "      Username: " << post.getUsername() << "\n" << endl;
            }
            

        }
    }
    if (!foundTopic)
    {
        cout << "No topics found with keyword " << keyword << endl;
    }
    cout << endl;
}

// searches for keyword in post content or post title
void Forum::searchPost(string keyword)
{
    int foundPost = 0;
    string postTitle, postContent;
    cout << "\n------------ Post Search Results ------------" << endl;
    for (int i = 0; i < topiclist.getLength(); i++)
    {
        topic = topiclist.get(i);
        ListPost postList = topic.getPostList();
        for (int j = 0; j < postList.getLength(); j++)
        {
            Post post = postList.get(j);
            postTitle = post.getPostTitle();
            postContent = post.getPostContent();
            if (postTitle.find(keyword) != string::npos || postContent.find(keyword) != string::npos)
            {
                foundPost = 1;
                cout << "Title: " << postTitle << endl;
                cout << "Content: " << postContent << endl;
                cout << "Username: " << post.getUsername() << "\n" << endl;

            }
        }
    }
    if (!foundPost)
    {
        cout << "No posts found with keyword " << keyword << endl;
    }
    cout << endl;

    
}

void Forum::searchUser(string keyword) 
{
    int foundUser = 0;
    string username;
    cout << "\n------------ User Search Results ------------" << endl;
    for (int i = 0; i < topiclist.getLength(); i++)
    {
        topic = topiclist.get(i);
        ListPost postList = topic.getPostList();
        for (int j = 0; j < postList.getLength(); j++)
        {
            Post post = postList.get(j);
            username = post.getUsername();
            if (username.find(keyword) != string::npos)
            {
                foundUser = 1;
                cout << "Username: " << username << endl;
                cout << "Topic: " << topic.getTopicTitle() << endl;
                cout << "Title: " << post.getPostTitle() << endl;
                cout << "Title: " << post.getPostTitle() << endl;
                cout << "Content: " << post.getPostContent() << "\n" << endl;
            }
        }
    }
    if (!foundUser)
    {
        cout << "No users found with keyword " << keyword << endl;
    }
}

//void Forum::loadForumReplies()
//{
//    ifstream replyFile("replies.txt");
//    if (replyFile.is_open())
//    {
//        string trTitle, prTitle, rContent, rUsername;
//        while (getline(replyFile, trTitle, ',') && getline(replyFile, prTitle, ',') && getline(replyFile, rContent, ',') && getline(replyFile, rUsername, ','))
//        {
//            for (int i = 0; i < topiclist.getLength(); i++)
//            {
//                topic = topiclist.get(i);
//                if (topic.getTopicTitle() == trTitle)
//                {
//                    ListPost postlist = topic.getPostList();
//                    for (int j = 0; j < postlist.getLength(); j++)
//                    {
//                        Post post = postlist.get(j);
//                        if (post.getPostTitle() == prTitle)
//                        {
//                            Reply newReply(rContent, rUsername);
//                            replyList.add(newReply);
//                            forum.addReply(trTitle, prTitle, rContent, rUsername);
//                            post.addReply(newReply);
//                        }
//                    }
//                }
//            }
//        }
//        replyFile.close();
//    }
//}

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