#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    string id;
    string name;
    string role;

public:
    User();                         
    User(string id, string name, string role);   

    string getID() const;
    string getName() const;
    string getRole() const;

    void setID(string id);
    void setName(string name);
    void setRole(string role);
};

#endif
