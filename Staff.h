#ifndef STAFF_H
#define STAFF_H

#include "User.h"
#include "Attendance.h"
#include <string>
#include <vector>
using namespace std;
class Staff : public User {
private:
    string faculty;
public:
    Staff(string id, string name, string role, string faculty);

    string getFaculty();
    
    void setFaculty(string faculty);
    void createAttendance();
    void viewAttendance(const vector<Attendance>& attendances);
    void exportSummary(const vector<Attendance>& records, string attendanceID);
};

#endif
