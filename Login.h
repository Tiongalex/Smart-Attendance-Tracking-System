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

    bool login(string type, string id, string pass); 
    int sequentialSearch(string search_key, vector<string> array);
};

#endif
