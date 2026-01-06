#ifndef STAFF_H
#define STAFF_H

#include "User.h"
#include "Attendance.h"
#include "LinkedList.h"
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
    void createAttendance(LinkedList<Attendance>& attendance, LinkedList<Attendance>& availableSession, string staffID);
    void viewAttendance(LinkedList<Attendance>& attendances);
    void exportSummary(LinkedList<Attendance>& records, string attendanceID);
};

#endif
