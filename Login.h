#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>
#include "LinkedList.h"
using namespace std;

class Login {
private:
    LinkedList<string> accountType;
    LinkedList<string> accountID;
    LinkedList<string> accountPassword;

public:
    Login();
    Login(const LinkedList<string>& accountType, const LinkedList<string>& accountID, const LinkedList<string>& accountPassword);

    bool login(const string& type, const string& id, const string& pass); 
    int sequentialSearch(const string& search_key, const LinkedList<string>& array);
};

#endif