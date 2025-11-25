#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>
using namespace std;

class Login {
private:
    vector<string> accountType;
    vector<string> accountID;
    vector<string> accountPassword;

public:
    Login();
    Login(vector<string> accountType, vector<string> accountID, vector<string> accountPassword);

    void login(); 
};

#endif