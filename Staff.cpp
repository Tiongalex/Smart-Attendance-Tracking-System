#include "Staff.h"
#include <iostream>
using namespace std;

Staff::Staff(string id, string name, string role, string faculty): User(id, name, role) {
    this->faculty=faculty;
}

string Staff::getFaculty(){
    return this->faculty;
}

void Staff::setFaculty(string faculty){
    this->faculty=faculty;
}

void Staff::createAttendance(){

}

void Staff::viewAttendance(){

}

void Staff::exportSummary(string attendanceID){

}