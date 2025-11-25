#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(string id, string name, string role, string course): User(id, name, role) {
    this->course=course;
}

string Student::getCourse(){
    return this->course;
}

void Student::setCourse(string course){
    this->course=course;
}

void Student::checkIn(string id, string attendanceID){

}

void Student::viewAttendance(){
    
}
