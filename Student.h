#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User {
private:
    string course;
public:
    Student(string id, string name, string role, string course);

    string getCourse();
    
    void setCourse(string course);
    void checkIn(string id, string attendanceID);
    void viewAttendance();
};

#endif
