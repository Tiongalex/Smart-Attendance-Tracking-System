#include "Attendance.h"

Attendance::Attendance() {
    attendanceStatus = "Absent";
}

Attendance::Attendance(string attendanceID, string staffID, string date, string time, string endTime, string studentID, string status)
    : attendanceID(attendanceID),
      staffID(staffID),
      date(date),
      time(time),
      endTime(endTime),
      studentID(studentID), 
      attendanceStatus(status) {}

string Attendance::getAttendanceID() const { return attendanceID; }
string Attendance::getStaffID() const { return staffID; }
string Attendance::getStudentID() const { return studentID; }
string Attendance::getAttendanceStatus() const { return attendanceStatus; }
string Attendance::getDate() const { return date; }
string Attendance::getTime() const { return time; }
string Attendance::getEndTime() const { return endTime; }

void Attendance::setAttendanceStatus(string s) { attendanceStatus = s; }
void Attendance::setStudentID(string id) { studentID = id; }
