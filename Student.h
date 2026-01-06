#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "LinkedList.h"
#include <vector>
#include <string>

class Attendance;   

using namespace std;

class Student : public User {
private:
    string course;

public:
    Student();  
    Student(string id, string name, string role, string course);

    string getCourse();
    void setCourse(string course);

    Attendance checkIn(string studentID, LinkedList<Attendance>& availableSession);

    void viewAttendance(LinkedList<Attendance>& allRecords);    
};

#endif
