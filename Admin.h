#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
public:
    Admin(string id, string name, string role);
    
    void addRecord();
    void editRecord();
    void removeRecord();
    void viewStudent();
    void viewAdmin();
    void viewStaff();
};

#endif
