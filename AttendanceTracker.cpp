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

    vector<Admin> getAdmins(){
        return this->admin;
    }

    vector<Staff> getStaff(){
        return this->staff;
    }

    vector<Student> getStudents(){
        return this->student;
    }
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

    return 0;
}