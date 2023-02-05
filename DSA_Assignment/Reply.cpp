// Reply.cpp – Implementation

#include "Reply.h"

Reply::Reply() { }
Reply::Reply(string c, string un) : content(c), username(un) { }
void Reply::setReplyContent(string c) { content = c; }
string Reply::getReplyContent() { return content; }
void Reply::setUsername(string un) { username = un; }
string Reply::getUsername() { return username; }