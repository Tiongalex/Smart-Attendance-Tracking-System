#ifndef STAFF_H
#define STAFF_H

#include "User.h"

class Staff : public User {
private:
    string faculty;
public:
    Staff(string id, string name, string role, string faculty);

    string getFaculty();
    
    void setFaculty(string faculty);
    void createAttendance();
    void viewAttendance();
    void exportSummary(string attendanceID);
};

#endif
