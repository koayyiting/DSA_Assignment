#pragma once           

#include <iostream>     
#include <string>       
using namespace std;

class Account
{
private:
    string username;
    string password;

public:
    Account();	            
    Account(string id, string pwd);	
    void setUsername(string id);	
    string getUsername();
    void setPassword(string pwd);
    string getPassword();
};
