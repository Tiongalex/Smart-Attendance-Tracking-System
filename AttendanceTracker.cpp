#include "Login.h"
#include "Student.h"
#include "Staff.h"
#include "Admin.h"
#include "Attendance.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

class AttendanceTracker{
private:
    Login loginSystem;
    vector<Student> student;
    vector<Staff> staff;
    vector<Admin> admin;
    vector<Attendance> attendance;
public:
    AttendanceTracker(){
        loadAdmins();
        loadStaff();
        loadStudents();
        loadAttendance(); 
    }
     
    void loadAdmins() {
        ifstream file("admin.txt");
        string line;
        while (getline(file, line)) {
            admin.push_back(parseAdmin(line));
        }
    }

    void loadStaff() {
        ifstream file("staff.txt");
        string line;
        while (getline(file, line)) {
            staff.push_back(parseStaff(line));
        }
    }

    void loadStudents() {
        ifstream file("student.txt");
        string line;
        while (getline(file, line)) {
            student.push_back(parseStudent(line));
        }
    }

    void loadAttendance() {
        ifstream file("attendance.txt");
        string line;
        
        if (!file.is_open()) {
            cout << "Warning: attendance.txt not found." << endl;
            return;
        }

        while (getline(file, line)) attendance.push_back(parseAttendance(line));
    }

    Attendance parseAttendance(string line) {
        stringstream ss(line);
        string aid, staffID, date, time, studentID, status;

        ss >> aid >> staffID >> date >> time >> studentID >> status;

        if (status.empty()) {
            status = studentID;  
            studentID = "Unknown"; 
        }

        Student studentObj(studentID, "Unknown Name", "Student", "Unknown Course");
        
        for (Student& s : this->student) {
            if (s.getID() == studentID) {
                studentObj = s;
                break;
            }
        }

        vector<Student> v_students;
        v_students.push_back(studentObj);

        vector<string> v_status;
        v_status.push_back(status);

        vector<string> v_date;
        v_date.push_back(date);

        vector<string> v_time;
        v_time.push_back(time);

        return Attendance(aid, staffID , v_students, v_status, v_date, v_time);
    }

    Student parseStudent(string line) {
        stringstream ss(line);
        string id, word, role, course;
        vector<string> parts;

        ss >> id;

        while (ss >> word) parts.push_back(word);

        int index = -1;
        for (int i = 0; i < parts.size(); i++) {
            if (parts[i] == "Student") {
                index = i;
                break;
            }
        }

        string name = "";
        for (int i = 0; i < index; i++) {
            name += parts[i];
            if (i < index - 1) name += " ";
        }

        role = parts[index];
        course = parts[index + 1];

        return Student(id, name, role, course);
    }

    Admin parseAdmin(string line) {
        stringstream ss(line);
        string id, word;
        vector<string> parts;

        ss >> id;
        while (ss >> word) parts.push_back(word);

        int index = -1;
        for (int i = 0; i < parts.size(); i++) {
            if (parts[i] == "Admin") {
                index = i;
                break;
            }
        }

        string name = "";
        for (int i = 0; i < index; i++) {
            name += parts[i];
            if (i < index - 1) name += " ";
        }

        return Admin(id, name, "Admin");
    }


    Staff parseStaff(string line) {
        stringstream ss(line);
        string id, word;
        vector<string> parts;

        ss >> id;
        while (ss >> word) parts.push_back(word);

        int index = -1;
        for (int i = 0; i < parts.size(); i++) {
            if (parts[i] == "Staff") {
                index = i;
                break;
            }
        }

        string name = "";
        for (int i = 0; i < index; i++) {
            name += parts[i];
            if (i < index - 1) name += " ";
        }

        string faculty = parts[index + 1];

        return Staff(id, name, "Staff", faculty);
    }

    vector<Admin> getAdmins(){ return this->admin;}
    vector<Staff> getStaff(){ return this->staff; }
    vector<Student> getStudents(){ return this->student; }
    vector<Attendance> getAttendances(){ return this->attendance; }
};

int main(){
    AttendanceTracker system;
    cout << "\n--- Admin List ---\n";
    for (auto& a : system.getAdmins()) {
        cout << a.getID() << " | " << a.getName() << " | " << a.getRole() << endl;
    }

    cout << "\n--- Staff List ---\n";
    for (auto& s : system.getStaff()) {
        cout << s.getID() << " | " << s.getName() << " | " << s.getRole()
             << " | " << s.getFaculty() << endl;
    }

    cout << "\n--- Student List ---\n";
    for (auto& st : system.getStudents()) {
        cout << st.getID() << " | " << st.getName() << " | " << st.getRole()
             << " | " << st.getCourse() << endl;
    }

    cout << "\n--- Attendance List ---\n";
    for (auto& at : system.getAttendances()) {
        cout << at.getAttendanceID() << " | " << at.getStaffID() <<endl;
    }

    vector<Staff> staffList = system.getStaff();
    if (!staffList.empty()) {
        cout << "\n[System] Staff Login detected: " << staffList[0].getName() << endl;
        staffList[0].viewAttendance(system.getAttendances());

    } else {
        cout << "No staff loaded." << endl;
    }

    return 0;
}