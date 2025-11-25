#include "Login.h"
#include "Student.h"
#include "Staff.h"
#include "Admin.h"
#include "Attendance.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class AttendanceTracker{
private:
    Login loginSystem;
    vector<Student> student;
    vector<Staff> staff;
    vector<Admin> admin;
    vector<Attendance> attendance;
public:
    AttendanceTracker(){}
};

int main(){
    AttendanceTracker system;
}