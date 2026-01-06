#include "Staff.h"
#include "Attendance.h"
#include "LinkedList.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
#include <regex>
#include <ctime>
#include <sstream>
using namespace std;

int partition(LinkedList<Attendance>& arr, int low, int high);
void quickSort(LinkedList<Attendance>& arr, int low, int high);
void mergeSort(LinkedList<Attendance>& attendances, int left, int right, bool sortByDate);
void merge(LinkedList<Attendance>& attendances, int left, int mid, int right, bool sortByDate);

string findStaffNameByID(const string& staffID) {
    ifstream file("staff.txt");
    if (!file.is_open()) return "Unknown";

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);

        string id, name = "", role, faculty;
        ss >> id;         

        if (id != staffID) continue;

        vector<string> tokens;
        string word;
        while (ss >> word) {
            if (word == "Staff") {
                role = word;
                break;
            }
            tokens.push_back(word);
        }

        for (int i = 0; i < tokens.size(); i++) {
            name += tokens[i];
            if (i + 1 < tokens.size()) name += " ";
        }

        return name;
    }

    return "Unknown";
}

string findStudentNameByID(const string& studentID) {
    ifstream file("student.txt");
    if (!file.is_open()) return "Unknown";

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);

        string id, name = "", role, course;
        ss >> id;     

        if (id != studentID) continue;

        vector<string> tokens;
        string word;
        while (ss >> word) {
            if (word == "Student") {
                role = word;
                break;
            }
            tokens.push_back(word);
        }

        for (int i = 0; i < tokens.size(); i++) {
            name += tokens[i];
            if (i + 1 < tokens.size()) name += " ";
        }

        return name;
    }

    return "Unknown";
}

LinkedList<Attendance> filterByDate(LinkedList<Attendance>& records, string targetDate) {
    LinkedList<Attendance> matchingRecords;
    for (int i=0;i<records.size();i++) {
            if (records.searchNode(i)->getDate() == targetDate) {
                matchingRecords.addNode(*records.searchNode(i));
            }
    }
    return matchingRecords;
}

LinkedList<Attendance> filterByAttendanceID(LinkedList<Attendance>& records, string targetID) {
    LinkedList<Attendance> matchingRecords;
    for (int i=0;i<records.size();i++) {
        if (records.searchNode(i)->getAttendanceID() == targetID) {
            matchingRecords.addNode(*records.searchNode(i));
        }
    }
    return matchingRecords;
}

vector<Attendance> filterByStaffID(const vector<Attendance>& records, string targetStaffID) {
    vector<Attendance> matchingRecords;
    for (const auto& record : records) {
        if (record.getStaffID() == targetStaffID) {
            matchingRecords.push_back(record);
        }
    }
    return matchingRecords;
}

LinkedList<Attendance> filterByStudentID(LinkedList<Attendance>& records, string targetStudentID) {
    LinkedList<Attendance> matchingRecords;
    for (int i=0;i<records.size();i++) {
        if(records.searchNode(i)->getStudentID() == targetStudentID){
            matchingRecords.addNode(*records.searchNode(i));
        }
    }
    return matchingRecords;
}

LinkedList<Attendance> filterByStatus(LinkedList<Attendance>& records, string targetStatus) {
    LinkedList<Attendance> matchingRecords;
    for (int i=0;i<records.size();i++) {
        if (records.searchNode(i)->getAttendanceStatus() == targetStatus) {
            matchingRecords.addNode(*records.searchNode(i));
        }
    }
    return matchingRecords;
}

bool isValidTime(const string& t) {
    regex pattern("^([0-1]\\d|2[0-3]):[0-5]\\d:[0-5]\\d$");
    return regex_match(t, pattern);
}

string getTodayDate() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    char buf[11];
    sprintf(buf, "%04d-%02d-%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    return string(buf);
}

Staff::Staff(string id, string name, string role, string faculty): User(id, name, role) {
    this->faculty=faculty;
}

string Staff::getFaculty(){
    return this->faculty;
}

void Staff::setFaculty(string faculty){
    this->faculty=faculty;
}

void Staff::createAttendance(LinkedList<Attendance>& attendance, LinkedList<Attendance>& availableSession, string staffID){
    string startTime, endTime;

    cout << "Enter starting time (hh:mm:ss): ";
    cin >> startTime;

    if (!isValidTime(startTime)) {
        cout << "Invalid format!\n";
        return;
    }

    cout << "Enter ending time (hh:mm:ss): ";
    cin >> endTime;

    if (!isValidTime(endTime)) {
        cout << "Invalid format!\n";
        return;
    }

    if (endTime <= startTime) {
        cout << "Ending time must be later than starting time!\n";
        return;
    }

    int biggest = 0;
    for (int i=0;i<attendance.size();i++) {
        string num = attendance.searchNode(i)->getAttendanceID().substr(3); 
        biggest = max(biggest, stoi(num));
    }


    string newAID = "AID" + to_string(biggest + 1);

    string today = getTodayDate();

    Attendance newAtt(newAID, staffID, today, startTime, endTime, "", "Absent");

    availableSession.addNode(newAtt);

    cout << "Attendance session " << newAID << " created successfully!\n";
}

void Staff::viewAttendance(LinkedList<Attendance>& inputAttendances){
    cout << "\n--- Staff View: " << this->getName() << " ---" << endl;
    
    LinkedList<Attendance> records;
    for(int i=0;i<inputAttendances.size();i++){
        if(inputAttendances.searchNode(i)->getStaffID() == this->getID()){
            records.addNode(*inputAttendances.searchNode(i));
        }
    }


    if (!records.getHead()) {
        cout << "No attendance records found for you Staff ID." << endl;
        return;
    }

    mergeSort(records, 0, records.size() - 1, true);
    
    cout << "Attendance Records (Sorted by Date):" << endl;
    cout << "=====================================" << endl;
    
    for (int i=0;i<records.size();i++) {
        string d = records.searchNode(i)->getDate();
        string t = records.searchNode(i)->getTime();
        string sName = records.searchNode(i)->getStudentID();
        string status = records.searchNode(i)->getAttendanceStatus();

        cout << "[" << d << " " << t << "] ID: " << records.searchNode(i)->getAttendanceID() << " | " << sName << " (" << status << ")" << endl;
    }
    
    int choice;
    string searchKey;
    vector<Attendance> results;

    cout << "Total Records Found: " << records.size() << endl;
    cout << "\n[ Filter Options ]" << endl;
    cout << "1. Show All Records" << endl;
    cout << "2. Filter by Date (YYYY-MM-DD)" << endl;
    cout << "3. Filter by Attendance ID" << endl;
    cout << "4. Filter by Student ID" << endl;
    cout << "5. Filter by Status (Present/Absent/Late)" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            for (int i = 0; i < records.size(); i++)
                results.push_back(*records.searchNode(i));
            break;
        case 2:
            cout << "Enter Date: ";
            cin >> searchKey;
            for (int i = 0; i < records.size(); i++)
                if (records.searchNode(i)->getDate() == searchKey)
                    results.push_back(*records.searchNode(i));
            break;
        case 3:
            cout << "Enter Attendance ID: ";
            cin >> searchKey;
            for (int i = 0; i < records.size(); i++)
                if (records.searchNode(i)->getAttendanceID() == searchKey)
                    results.push_back(*records.searchNode(i));
            break;
        case 4:
            cout << "Enter Student ID: ";
            cin >> searchKey;
            for (int i = 0; i < records.size(); i++)
                if (records.searchNode(i)->getStudentID() == searchKey)
                    results.push_back(*records.searchNode(i));
            break;
        case 5:
            cout << "Enter Status: ";
            cin >> searchKey;
            for (int i = 0; i < records.size(); i++)
                if (records.searchNode(i)->getAttendanceStatus() == searchKey)
                    results.push_back(*records.searchNode(i));
            break;
        default:
            cout << "Invalid choice. Showing all records." << endl;
            for (int i = 0; i < records.size(); i++)
                results.push_back(*records.searchNode(i));
            break;
    }

    cout << "\n[ Results ]" << endl;
    if (results.empty()) {
        cout << "No records found matching criteria." << endl;
    } else {
        cout << "----------------------------------------------------------------" << endl;
        cout << "Date       | Time     | AttID  | Student Name         | Status" << endl;
        cout << "----------------------------------------------------------------" << endl;

        for (auto &att : results) {
            string sName = findStudentNameByID(att.getStudentID());
            cout << att.getDate() << " | " << att.getTime() << " | " << att.getAttendanceID()
                << " | " << sName << " | " << att.getAttendanceStatus() << endl;
        }

        cout << "----------------------------------------------------------------" << endl;
        cout << "Total displayed: " << results.size() << endl;
    }
}

void Staff::exportSummary(LinkedList<Attendance>& records, string attendanceID){
    cout << "   Generating Summary for Session: " << attendanceID << endl;
    LinkedList<Attendance> sessionRecords = filterByAttendanceID(records, attendanceID);
    if (!sessionRecords.getHead()) {
        cout << "[Error] No records found for Attendance ID: " << attendanceID << endl;
        return;
    }
    quickSort(sessionRecords, 0, sessionRecords.size() - 1);
    int total = sessionRecords.size();
    int present = 0, absent = 0, late = 0;

    for (int i=0;i<sessionRecords.size();i++) {
        string status = sessionRecords.searchNode(i)->getAttendanceStatus();
        if (status == "Present") present++;
        else if (status == "Absent") absent++;
        else if (status == "Late") late++;
    }

    string filename = "Summary_" + attendanceID + ".txt";
    ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << "Attendance Summary Report\n";
        outFile << "========================================\n";
        outFile << "Session ID   : " << attendanceID << "\n";
        string lecturer = findStaffNameByID(records.searchNode(0)->getStaffID());
        outFile << "Lecturer     : " << lecturer << "\n";
        outFile << "Total Students: " << total << "\n";
        outFile << "Stats        : Present: " << present << " | Absent: " << absent << " | Late: " << late << "\n";
        outFile << "========================================\n";
        outFile << left << setw(25) << "Student Name" << setw(15) << "Student ID" << "Status\n";
        outFile << "--------------------------------------------------\n";

        for (int i=0;i<sessionRecords.size();i++) {
            string name = findStudentNameByID(sessionRecords.searchNode(i)->getStudentID());
            string id = sessionRecords.searchNode(i)->getStudentID();
            string status = sessionRecords.searchNode(i)->getAttendanceStatus();
            outFile << left << setw(25) << name << setw(15) << id << status << "\n";
        }
        outFile.close();

        cout << "Summary generated successfully!" << endl;
        cout << "Filename: " << filename << endl;
        cout << "Stats: Present(" << present << "), Absent(" << absent << "), Late(" << late << ")" << endl;
    } else {
        cout << "[Error] Unable to create file " << filename << endl;
    }
}

void mergeSort(LinkedList<Attendance>& attendances, int left, int right, bool sortByDate) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(attendances, left, mid, sortByDate);
        mergeSort(attendances, mid + 1, right, sortByDate);
        merge(attendances, left, mid, right, sortByDate);
    }
}

void merge(LinkedList<Attendance>& attendances, int left, int mid, int right, bool sortByDate) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Attendance> L(n1);
    vector<Attendance> R(n2);

    for (int i = 0; i < n1; i++) L[i] = *attendances.searchNode(left + i);
    for (int j = 0; j < n2; j++) R[j] = *attendances.searchNode(mid + 1 + j);

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        string dateL = L[i].getDate();
        string dateR = R[j].getDate();

        if ((sortByDate && dateL <= dateR) || (!sortByDate && dateL >= dateR)) {
            *attendances.searchNode(k) = L[i];
            i++;
        } else {
            *attendances.searchNode(k) = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) { *attendances.searchNode(k) = L[i]; i++; k++; }

    while (j < n2) { *attendances.searchNode(k) = R[j]; j++; k++; }
}

int partition(LinkedList<Attendance>& arr, int low, int high) {
    string pivot = arr.searchNode(high)->getStudentID(); 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (arr.searchNode(j)->getStudentID() <= pivot) {
            i++; 
            swap(*arr.searchNode(i), *arr.searchNode(j));
        }
    }
    swap(*arr.searchNode(i+1), *arr.searchNode(high));
    return (i + 1);
}

void quickSort(LinkedList<Attendance>& arr, int low, int high) {
    if (low < high) {
        int cut = partition(arr, low, high);
        quickSort(arr, low, cut - 1);
        quickSort(arr, cut + 1, high);
    }
}