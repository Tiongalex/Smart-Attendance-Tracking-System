#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(string id, string name, string role);
    
    void addStudent();
    void editStudent();
    void removeStudent();
    void viewStudent();
};

#endif
