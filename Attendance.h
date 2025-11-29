#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include "Student.h"
#include <string>
#include <vector>
using namespace std;

class Attendance{
private:
    string attendanceID;
    string staffID;
    Student student;
    string attendanceStatus;
    string date;
    string time;
public:
    Attendance();
    Attendance(string attendanceID, string staffID, Student student, string attendanceStatus, string date, string time);
    
    string getStaffID() const ;
    string getAttendanceID() const ;

    Student getStudent() const;
    string getAttendanceStatus() const;
    string getDate() const;
    string getTime() const;

    void setAttendanceStatus(string attendance);
    void setDate(string date);
    void setTime(string time);
};

#endif