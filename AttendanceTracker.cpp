#include "Login.h"
#include "Student.h"
#include "Staff.h"
#include "Admin.h"
#include "Attendance.h"
#include "LinkedList.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstdlib>   
#include <limits>    
#include <regex>
#include <ctime>

using namespace std;

class AttendanceTracker{
private:
    Login loginSystem;
    LinkedList<Student> student;
    LinkedList<Staff> staff;
    LinkedList<Admin> admin;
    LinkedList<Attendance> attendance;
    string userID;
    LinkedList<Attendance> availableSession;
public:
    AttendanceTracker(){
        loadAdmins(); 
        loadStaff(); 
        loadStudents(); 
        loadAttendance(); 
        loadLogin(); 
    }
    
    string getUserID(){
        return this->userID;
    }

    void setuserID(string userID){
        this->userID=userID;
    }

    void loadAdmins() {
        ifstream file("admin.txt");
        string line;
        while (getline(file, line)) {
            admin.addNode(parseAdmin(line));
        }
    }

    void loadStaff() {
        ifstream file("staff.txt");
        string line;
        while (getline(file, line)) {
            staff.addNode(parseStaff(line));
        }
    }

    void loadStudents() {
        ifstream file("student.txt");
        string line;
        while (getline(file, line)) {
            student.addNode(parseStudent(line));
        }
    }

    void loadAttendance() {
        ifstream file("attendance.txt");
        string line;
        
        if (!file.is_open()) {
            cout << "Warning: attendance.txt not found." << endl;
            return;
        }

        while (getline(file, line)) attendance.addNode(parseAttendance(line));
    }

void loadLogin() {
    ifstream file("login.txt");
    if (!file.is_open()) {
        cout << "Error: login.txt missing!" << endl;
        return;
    }

    LinkedList<string> ids, roles, passwords;
    string line;
    
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id, role, pass;
        ss >> id >> role >> pass;

        if (id.empty() || role.empty() || pass.empty()) continue;

        ids.addNode(id);
        roles.addNode(role);
        passwords.addNode(pass);
    }

    loginSystem = Login(roles, ids, passwords);
}

    Attendance parseAttendance(string line) {
        stringstream ss(line);
        string aid, staffID, date, time, endTime, studentID, status;

        ss >> aid >> staffID >> date >> time >> endTime >> studentID >> status;

        return Attendance(aid, staffID, date, time, endTime, studentID, status);
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

        string role = parts[index];

        return Admin(id, name, role);
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

        string role = parts[index];
        string faculty = parts[index + 1];

        return Staff(id, name, role, faculty);
    }

    void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #endif
    }

    void pressEnterToContinue() {
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    int findStudentIndex(AttendanceTracker& system, const string& id) {
        auto& students = system.getStudents(); 
        for (int i = 0; i < (int)students.size(); ++i) {
            if (students.searchNode(i)->getID() == id) return i;
        }
        return -1;
    }

    int findStaffIndex(AttendanceTracker& system, const string& id) {
        auto& staffs = system.getStaff();
        for (int i = 0; i < (int)staffs.size(); ++i) {
            if (staffs.searchNode(i)->getID() == id) return i;
        }
        return -1;
    }

    int findAdminIndex(AttendanceTracker& system, const string& id) {
        auto& admins = system.getAdmins();
        for (int i = 0; i < (int)admins.size(); ++i) {
            if (admins.searchNode(i)->getID() == id) return i;
        }
        return -1;
    }

    string getTodayDate() {
        time_t now = time(nullptr);
        tm* t = localtime(&now);
        char buf[11];
        sprintf(buf, "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
        return string(buf);
    }

    LinkedList<Attendance>& getAvailableSession() {
        string today = getTodayDate();

        // Remove old sessions from availableSession
        Node<Attendance>* prev = nullptr;
        Node<Attendance>* cur = availableSession.getHead();

        while (cur != nullptr) {
            if (cur->data.getDate() != today) {
                // delete this node
                if (prev == nullptr) {
                    // deleting head
                    availableSession.setHead(cur->next);
                } else {
                    prev->next = cur->next;
                }

                Node<Attendance>* toDelete = cur;
                cur = cur->next;
                delete toDelete;
                continue;
            }

            prev = cur;
            cur = cur->next;
        }

        // Add today sessions if not already in availableSession
        Node<Attendance>* a = attendance.getHead();
        while (a != nullptr) {
            if (a->data.getDate() == today) {

                // check if exists
                bool exists = false;
                Node<Attendance>* b = availableSession.getHead();
                while (b != nullptr) {
                    if (b->data.getAttendanceID() == a->data.getAttendanceID()) {
                        exists = true;
                        break;
                    }
                    b = b->next;
                }

                if (!exists) {
                    availableSession.addNode(a->data);
                }
            }
            a = a->next;
        }

        return availableSession;
    }


    void saveNewAttendance(const Attendance& att) {
        attendance.addNode(att);

        fstream f("attendance.txt", ios::in | ios::out);
        if (!f) {
            ofstream newFile("attendance.txt");
            newFile << att.getAttendanceID() << " "
                    << att.getStaffID() << " "
                    << att.getDate() << " "
                    << att.getTime() << " "
                    << att.getEndTime() << " "
                    << att.getStudentID() << " "
                    << att.getAttendanceStatus() << "\n";
            return;
        }

        f.seekg(0, ios::end);
        long long pos = f.tellg();

        bool needNewline = false;

        if (pos > 0) {
            f.seekg(-1, ios::end);
            char lastChar;
            f.get(lastChar);
            if (lastChar != '\n') needNewline = true;
        }

        f.close();

        ofstream out("attendance.txt", ios::app);
        if (needNewline) out << "\n";

        out << att.getAttendanceID() << " "
            << att.getStaffID() << " "
            << att.getDate() << " "
            << att.getTime() << " "
            << att.getEndTime() << " "
            << att.getStudentID() << " "
            << att.getAttendanceStatus() << "\n";
    }



        LinkedList<Admin>& getAdmins() { return this->admin;}
        LinkedList<Staff>& getStaff() { return this->staff; }
        LinkedList<Student>& getStudents() { return this->student; }
        LinkedList<Attendance>& getAttendances() { return this->attendance; }
        Login getLogin() const { return this->loginSystem; }
    };

int main() {
    AttendanceTracker system;

    while (true) {
        system.clearScreen();
        cout << "===== Smart Attendance System =====\n";
        cout << "1. Admin\n";
        cout << "2. Staff\n";
        cout << "3. Student\n";
        cout << "0. Exit\n\n";
        cout << "Select option: ";

        int topChoice;
        if (!(cin >> topChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Press Enter to return to menu.";
            cin.get();
            continue;
        }

        if (topChoice == 0) {
            system.clearScreen();
            cout << "Exiting... \n";
            return 0;
        }

        string role;
        if (topChoice == 1) role = "Admin";
        else if (topChoice == 2) role = "Staff";
        else if (topChoice == 3) role = "Student";
        else {
            cout << "Invalid selection. Press Enter to continue.";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            continue;
        }

        system.clearScreen();
        cout << "Role: " << role << "\n";
        cout << "Enter Account ID: ";
        string inputID;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, inputID);

        cout << "Enter Password: ";
        string inputPass;
        getline(cin, inputPass);

        bool ok = system.getLogin().login(role, inputID, inputPass);

        if (!ok) {
            system.clearScreen();
            cout << "Login Failed: account ID or account password not match.\n";
            cout << "Press Enter to continue...";
            cin.get();
            continue; 
        }

        system.setuserID(inputID);

        if (role == "Student") {
            while (true) {
                system.clearScreen();
                cout << "--- Student Page ---\n";
                int idx = system.findStudentIndex(system, system.getUserID());
                cout << "Logged in as: " << system.getStudents().searchNode(idx)->getName() << "\n\n";
                cout << "1. Check-in attendance\n";
                cout << "2. View attendance history\n";
                cout << "0. Log Out\n\n";
                cout << "Select option: ";

                int sChoice;
                if (!(cin >> sChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (sChoice == 0) {
                    system.setuserID("");
                    break; 
                } else if (sChoice == 1) {
                    int idx = system.findStudentIndex(system, system.getUserID());
                    if (idx == -1) {
                        cout << "Student record not found.\n";
                        system.pressEnterToContinue();
                        continue;
                    }
                    auto& students = system.getStudents();
                    Attendance newAtt = students.searchNode(idx)->checkIn(system.getUserID(), system.getAvailableSession());
                    if (newAtt.getAttendanceID() != "") {
                        system.saveNewAttendance(newAtt); 
                    }
                    system.pressEnterToContinue();
                } else if (sChoice == 2) {
                    int idx = system.findStudentIndex(system, system.getUserID());
                    if (idx == -1) {
                        cout << "Student record not found.\n";
                        system.pressEnterToContinue();
                        continue;
                    }
                    auto& students = system.getStudents();
                    students.searchNode(idx)->viewAttendance(system.getAttendances()); 
                    system.pressEnterToContinue();
                } else {
                    cout << "Invalid choice.\n";
                    system.pressEnterToContinue();
                }
            } 
        }
        else if (role == "Staff") {
            int staffIdx = system.findStaffIndex(system, system.getUserID());
            if (staffIdx == -1) {
                system.clearScreen();
                cout << "Staff record not found. Logging out.\n";
                system.setuserID("");
                system.pressEnterToContinue();
                continue;
            }

            while (true) {
                system.clearScreen();
                cout << "--- Staff Page ---\n";
                int idx = system.findStaffIndex(system, system.getUserID());
                cout << "Logged in as: " << system.getStaff().searchNode(idx)->getName() << "\n\n";
                cout << "1. Create attendance session\n";
                cout << "2. View attendance history\n";
                cout << "3. Export attendance summary\n";
                cout << "0. Log Out\n\n";
                cout << "Select option: ";

                int sfChoice;
                if (!(cin >> sfChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (sfChoice == 0) {
                    system.setuserID("");
                    break;
                } else if (sfChoice == 1) {
                    auto& staffs = system.getStaff();
                    staffs.searchNode(staffIdx)->createAttendance(system.getAttendances(), system.getAvailableSession(), system.getUserID()); 
                    system.pressEnterToContinue();
                } else if (sfChoice == 2) {
                    auto& staffs = system.getStaff();
                    auto& attendances = system.getAttendances();
                    staffs.searchNode(staffIdx)->viewAttendance(attendances);
                    system.pressEnterToContinue();
                } else if (sfChoice == 3) {
                    cout << "Enter Attendance ID to export summary: ";
                    string attID;
                    cin >> ws;
                    getline(cin, attID);
                    auto& staffs = system.getStaff();
                    auto& attendances = system.getAttendances();
                    staffs.searchNode(staffIdx)->exportSummary(attendances, attID);
                    system.pressEnterToContinue();
                } else {
                    cout << "Invalid choice.\n";
                    system.pressEnterToContinue();
                }
            } 
        }
        else if (role == "Admin") {
            int adminIdx = system.findAdminIndex(system, system.getUserID());
            if (adminIdx == -1) {
                system.clearScreen();
                cout << "Admin record not found. Logging out.\n";
                system.setuserID("");
                system.pressEnterToContinue();
                continue;
            }

            while (true) {
                system.clearScreen();
                cout << "--- Admin Page ---\n";
                int idx = system.findAdminIndex(system, system.getUserID());
                cout << "Logged in as: " << system.getAdmins().searchNode(idx)->getName() << "\n\n";
                cout << "1. View Records\n";
                cout << "2. Add Records\n";
                cout << "3. Edit Records\n";
                cout << "4. Remove Records\n";
                cout << "0. Log Out\n\n";
                cout << "Select option: ";

                int aChoice;
                if (!(cin >> aChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (aChoice == 0) {
                    system.setuserID("");
                    break;
                } else if (aChoice == 1) {
                    while (true) {
                        system.clearScreen();
                        cout << "--- View Records ---\n";
                        cout << "1. Admin\n";
                        cout << "2. Staff\n";
                        cout << "3. Student\n";
                        cout << "0. Return\n\n";
                        cout << "Select option: ";
                        int vr;
                        if (!(cin >> vr)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (vr == 0) break;
                        system.clearScreen();
                        if (vr == 1) {
                            int idx = system.findAdminIndex(system, system.getUserID());
                            system.getAdmins().searchNode(idx)->viewAdmin(); 
                        } else if (vr == 2) {
                            int idx = system.findAdminIndex(system, system.getUserID());
                            system.getAdmins().searchNode(idx)->viewStaff(); 
                        } else if (vr == 3) {
                            int idx = system.findAdminIndex(system, system.getUserID());
                            system.getAdmins().searchNode(idx)->viewStudent(); 
                        } else {
                            cout << "Invalid selection.\n";
                            system.pressEnterToContinue();
                            continue;
                        }
                        system.pressEnterToContinue();
                        break;
                    } 
                } else if (aChoice == 2) {
                    auto& admins = system.getAdmins();
                    admins.searchNode(adminIdx)->addRecord(); 
                    system.pressEnterToContinue();
                } else if (aChoice == 3) {
                    auto& admins = system.getAdmins();
                    admins.searchNode(adminIdx)->editRecord(); 
                    system.pressEnterToContinue();
                } else if (aChoice == 4) {
                    auto& admins = system.getAdmins();
                    admins.searchNode(adminIdx)->removeRecord(); 
                    system.pressEnterToContinue();
                } else {
                    cout << "Invalid selection.\n";
                    system.pressEnterToContinue();
                }
            } 
        }

     
    } 

    return 0;
}