#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include <fstream>
#include <iostream>

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
static void appendRecord(const string& filename, const string& record) {

    ifstream in(filename);

    bool addNewline = false;

    if (in) {
        in.seekg(0, ios::end);
        long long size = in.tellg();

        if (size > 0) {
            in.seekg(-1, ios::end);
            char last;
            in.get(last);

            if (last != '\n')
                addNewline = true;
        }
    }

    in.close();

    ofstream out(filename, ios::app);

    if (addNewline)
        out << "\n";

    out << record << "\n";
}
#endif
