#include "Attendance.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Attendance::Attendance() {}

Attendance::Attendance(string attendanceID, string staffID, vector<Student> student, vector<string> attendanceStatus, vector<string> date, vector<string> tume):
attendanceID(attendanceID), staffID(staffID), student(student), attendanceStatus(attendanceStatus), date(date), time(time) {}

string Attendance::getAttendanceID(){
    return this->attendanceID;
}

vector<Student> Attendance::getStudent(){
    return this->student;
}

vector<string> Attendance::getAttendanceStatus(){
    return this->attendanceStatus;
}

vector<string> Attendance::getDate(){
    return this->date;
}

vector<string> Attendance::getTime(){
    return this->time;
}

void Attendance::setAttendanceStatus(string stuID, string attendance){
    
}

void Attendance::setDate(string stuID, string date){

}

void Attendance::setTime(string stuID, string time){
    
}