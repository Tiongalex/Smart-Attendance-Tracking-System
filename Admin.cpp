#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> split(const string &line) {
    stringstream ss(line);
    vector<string> parts;
    string temp;
    while (ss >> temp) parts.push_back(temp);
    return parts;
}

Admin::Admin(string id, string name, string role)
    : User(id, name, role) {}

void appendRecord(const string& filename, const string& record) {

    ifstream in(filename);

    bool addNewline = false;

    if (in) {
        // move to last character
        in.seekg(0, ios::end);
        long long size = in.tellg();

        if (size > 0) {
            in.seekg(-1, ios::end);
            char last;
            in.get(last);

            if (last != '\n')
                addNewline = true;
        }
    }

    in.close();

    ofstream out(filename, ios::app);

    if (addNewline)
        out << "\n";

    out << record << "\n";
}

void Admin::addRecord() {
    cout << "Add Record\n";
    cout << "Select role to add (Admin/Staff/Student): ";
    string role;
    cin >> role;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (role == "Admin") {
        string id, name;
        cout << "Enter Admin ID: ";
        getline(cin, id);
        cout << "Enter Admin Name: ";
        getline(cin, name);

        appendRecord("admin.txt", id + " " + name + " Admin");
        cout << "\nAdmin record added successfully.\n";
    }
    else if (role == "Staff") {
        string id, name, faculty;
        cout << "Enter Staff ID: ";
        getline(cin, id);
        cout << "Enter Staff Name: ";
        getline(cin, name);
        cout << "Enter Faculty: ";
        getline(cin, faculty);

        appendRecord("staff.txt", id + " " + name + " Staff " + faculty);
        cout << "\nStaff record added successfully.\n";
    }
    else if (role == "Student") {
        string id, name, course;
        cout << "Enter Student ID: ";
        getline(cin, id);
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Course: ";
        getline(cin, course);

        appendRecord("student.txt", id + " " + name + " Student " + course);
        cout << "\nStudent record added successfully.\n";
    }
    else {
        cout << "Invalid role.\n";
    }
}

void Admin::editRecord() {
    cout << "Edit Record\n";
    cout << "Select role to edit (Admin/Staff/Student): ";
    string role;
    cin >> role;

    string filename = (role == "Admin") ? "admin.txt"
                     : (role == "Staff") ? "staff.txt"
                     : (role == "Student") ? "student.txt"
                     : "";

    if (filename == "") {
        cout << "Invalid role.\n";
        return;
    }

    cin.ignore();
    cout << "Enter ID of the record to edit: ";
    string targetID;
    getline(cin, targetID);

    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool found = false;

    while (getline(infile, line)) {
        vector<string> parts = split(line);
        if (!parts.empty() && parts[0] == targetID) {
            found = true;

            // Rewrite new record based on role
            if (role == "Admin") {
                string id = targetID, name;
                cout << "Enter new Admin Name: ";
                getline(cin, name);
                line = id + " " + name + " Admin";
            }
            else if (role == "Staff") {
                string id = targetID, name, faculty;
                cout << "Enter new Staff Name: ";
                getline(cin, name);
                cout << "Enter new Faculty: ";
                getline(cin, faculty);
                line = id + " " + name + " Staff " + faculty;
            }
            else if (role == "Student") {
                string id = targetID, name, course;
                cout << "Enter new Student Name: ";
                getline(cin, name);
                cout << "Enter new Course: ";
                getline(cin, course);
                line = id + " " + name + " Student " + course;
            }
        }
        lines.push_back(line);
    }
    infile.close();

    if (!found) {
        cout << "Record not found.\n";
        return;
    }

    // Rewrite file
    ofstream outfile(filename);
    for (auto &l : lines) outfile << l << "\n";
    outfile.close();

    cout << "Record updated successfully.\n";
}

void Admin::removeRecord() {
    cout << "Remove Record\n";
    cout << "Select role to remove (Admin/Staff/Student): ";
    string role;
    cin >> role;

    string filename = (role == "Admin") ? "admin.txt"
                     : (role == "Staff") ? "staff.txt"
                     : (role == "Student") ? "student.txt"
                     : "";

    if (filename == "") {
        cout << "Invalid role.\n";
        return;
    }

    cin.ignore();
    cout << "Enter ID of the record to remove: ";
    string targetID;
    getline(cin, targetID);

    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return;
    }

    vector<string> lines;
    string line;
    bool removed = false;

    while (getline(infile, line)) {
        vector<string> parts = split(line);
        if (!parts.empty() && parts[0] == targetID) {
            removed = true;
            continue;  // skip this line
        }
        lines.push_back(line);
    }
    infile.close();

    if (!removed) {
        cout << "Record not found.\n";
        return;
    }

    ofstream outfile(filename);
    for (auto &l : lines) outfile << l << "\n";
    outfile.close();

    cout << "Record removed successfully.\n";
}

void Admin::viewStudent() {
    ifstream file("student.txt");
    if (!file.is_open()) {
        cout << "Error: cannot open student.txt\n";
        return;
    }

    cout << "------ Student Records ------\n";
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
}

void Admin::viewAdmin() {
    ifstream file("admin.txt");
    if (!file.is_open()) {
        cout << "Error: cannot open admin.txt\n";
        return;
    }

    cout << "------ Admin Records ------\n";
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
}

void Admin::viewStaff() {
    ifstream file("staff.txt");
    if (!file.is_open()) {
        cout << "Error: cannot open staff.txt\n";
        return;
    }

    cout << "------ Staff Records ------\n";
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
}
