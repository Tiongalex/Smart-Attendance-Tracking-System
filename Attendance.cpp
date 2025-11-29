#include "Attendance.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Attendance::Attendance() {}

Attendance::Attendance(string attendanceID, string staffID, vector<Student> student, vector<string> attendanceStatus, vector<string> date, vector<string> time):
attendanceID(attendanceID), staffID(staffID), student(student), attendanceStatus(attendanceStatus), date(date), time(time) {}

string Attendance::getStaffID() const {
    return this->staffID;
}

string Attendance::getAttendanceID() const {
    return this->attendanceID;
}

vector<Student> Attendance::getStudent() const {
    return this->student;
}

vector<string> Attendance::getAttendanceStatus() const{
    return this->attendanceStatus;
}

vector<string> Attendance::getDate() const{
    return this->date;
}

vector<string> Attendance::getTime() const{
    return this->time;
}

void Attendance::setAttendanceStatus(string stuID, string attendance){
    
}

void Attendance::setDate(string stuID, string date){

}

void Attendance::setTime(string stuID, string time){
    
}