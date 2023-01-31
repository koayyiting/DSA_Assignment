// Account.cpp – Implementation

#include "Account.h"

Account::Account() { }

Account::Account(string id, string pwd) 
{
	username = id;
	password = pwd;
}

void Account::setUsername(string id) { username = id; }

string Account::getUsername() { return username; }

void Account::setPassword(string pwd) { password = pwd; }

string Account::getPassword() { return password; }
