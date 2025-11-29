#include "Attendance.h"
#include <iostream>
#include <string>
using namespace std;

Attendance::Attendance() {}

Attendance::Attendance(string attendanceID, string staffID, Student student, string attendanceStatus, string date, string time):
    attendanceID(attendanceID), staffID(staffID), student(student), attendanceStatus(attendanceStatus), date(date), time(time) {}

string Attendance::getStaffID() const {
    return this->staffID;
}

string Attendance::getAttendanceID() const {
    return this->attendanceID;
}

Student Attendance::getStudent() const {
    return this->student;
}

string Attendance::getAttendanceStatus() const{
    return this->attendanceStatus;
}

string Attendance::getDate() const{
    return this->date;
}

string Attendance::getTime() const{
    return this->time;
}

void Attendance::setAttendanceStatus(string attendance){
    this->attendanceStatus=attendance;
}

void Attendance::setDate(string date){
    this->date=date;
}

void Attendance::setTime(string time){
    this->time=time;
}