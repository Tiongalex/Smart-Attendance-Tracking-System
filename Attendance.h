#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>
using namespace std;

class Attendance {
private:
    string attendanceID;
    string staffID;
    string studentID;    
    string attendanceStatus;
    string date;
    string time;
    string endTime;

public:
    Attendance();

    Attendance(string attendanceID,
               string staffID,
               string date,
               string time,
               string endTime,
               string studentID,
               string attendanceStatus);

    string getAttendanceID() const;
    string getStaffID() const;
    string getStudentID() const;
    string getAttendanceStatus() const;
    string getDate() const;
    string getTime() const;
    string getEndTime() const;

    void setAttendanceStatus(string s);
    void setStudentID(string id);
};

#endif
