// Post.cpp – Implementation

#include "Post.h"

Post::Post() { }
Post::Post(string tp, string c, string pt,string un) : title(tp), content(c), postTime(pt),username(un) { }
ListReply Post::getReplyList() { return replylist; }
void Post::setPostTitle(string t) { title = t; }
string Post::getPostTitle() { return title; }
void Post::setPostContent(string c) { content = c; }
string Post::getPostContent() { return content; }
void Post::setPostTime(string pt) { postTime = pt; }
string Post::getPostTime() { return postTime; }
void Post::setUsername(string un) { username = un; }
string Post::getUsername() { return username; }

void Post::addReply(Reply reply) {
    replylist.add(reply);
}

// display the reply
void Post::displayReply(ListReply replylist) {
    if (replylist.isEmpty()) {
        cout << endl;
    }
    else {
        cout << "   Reply: " << endl;
        for (int i = 0; i < replylist.getLength(); i++) {
            Reply reply = replylist.get(i);
            cout << "        Content: " << reply.getReplyContent() << endl;
            cout << "        Username: " << reply.getUsername() << endl;
        }
    }   
}