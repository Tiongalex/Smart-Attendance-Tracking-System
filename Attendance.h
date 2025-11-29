#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include "Student.h"
#include <string>
#include <vector>
using namespace std;

class Attendance{
private:
    string attendanceID;
    string staffID; // Determine which staff yg create the attendance entity
    vector<Student> student;
    vector<string> attendanceStatus;
    vector<string> date;
    vector<string> time;
public:
    Attendance();
    Attendance(string attendanceID, string staffID, vector<Student> student, vector<string> attendanceStatus, vector<string> date, vector<string> time);
    
    string getStaffID() const ;
    string getAttendanceID() const ;

    vector<Student> getStudent() const;

    vector<string> getAttendanceStatus() const;
    vector<string> getDate() const;
    vector<string> getTime() const;

    void setAttendanceStatus(string stuID, string attendance);
    void setDate(string stuID, string date);
    void setTime(string stuID, string time);
};

#endif