#include "Staff.h"
#include "Attendance.h"
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

int partition(vector<Attendance>& arr, int low, int high);
void quickSort(vector<Attendance>& arr, int low, int high);
void mergeSort(vector<Attendance>& attendances, int left, int right, bool sortByDate);
void merge(vector<Attendance>& attendances, int left, int mid, int right, bool sortByDate);

string findStaffNameByID(const string& staffID) {
    ifstream file("staff.txt");
    if (!file.is_open()) return "Unknown";

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);

        string id, name = "", role, faculty;
        ss >> id;         // read ID

        if (id != staffID) continue;

        // Now read everything until the word "Staff"
        vector<string> tokens;
        string word;
        while (ss >> word) {
            if (word == "Staff") {
                role = word;
                break;
            }
            tokens.push_back(word);
        }

        // join tokens into full name (handles spaces in name)
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
        ss >> id;         // read ID

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

        // join tokens into full name (handles spaces in name)
        for (int i = 0; i < tokens.size(); i++) {
            name += tokens[i];
            if (i + 1 < tokens.size()) name += " ";
        }

        return name;
    }

    return "Unknown";
}

vector<Attendance> filterByDate(const vector<Attendance>& records, string targetDate) {
    vector<Attendance> matchingRecords;
    for (const auto& record : records) {
            if (record.getDate() == targetDate) {
                matchingRecords.push_back(record);
            }
    }
    return matchingRecords;
}

vector<Attendance> filterByAttendanceID(const vector<Attendance>& records, string targetID) {
    vector<Attendance> matchingRecords;
    for (const auto& record : records) {
        if (record.getAttendanceID() == targetID) {
            matchingRecords.push_back(record);
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

vector<Attendance> filterByStudentID(const vector<Attendance>& records, string targetStudentID) {
    vector<Attendance> matchingRecords;
    for (const auto& record : records) {
        if(record.getStudentID() == targetStudentID){
            matchingRecords.push_back(record);
        }
    }
    return matchingRecords;
}

vector<Attendance> filterByStatus(const vector<Attendance>& records, string targetStatus) {
    vector<Attendance> matchingRecords;
    for (const auto& record : records) {
        if (record.getAttendanceStatus() == targetStatus) {
            matchingRecords.push_back(record);
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

void Staff::createAttendance(vector<Attendance>& attendance, vector<Attendance>& availableSession, string staffID){
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

    // --- FIND LARGEST AID ---
    int biggest = 0;
    for (auto& att : attendance) {
        string num = att.getAttendanceID().substr(3); // remove AID
        biggest = max(biggest, stoi(num));
    }


    string newAID = "AID" + to_string(biggest + 1);

    // Today’s date
    string today = getTodayDate();

    // Create new attendance
    Attendance newAtt(newAID, staffID, today, startTime, endTime, "", "Absent");


    // Add into today's available session list
    availableSession.push_back(newAtt);

    cout << "Attendance session " << newAID << " created successfully!\n";
}

void Staff::viewAttendance(const vector<Attendance>& inputAttendances){
    cout << "\n--- Staff View: " << this->getName() << " ---" << endl;
    
    vector<Attendance> records;
    for(const auto& rec : inputAttendances){
        if(rec.getStaffID() == this->getID()){
            records.push_back(rec);
        }
    }


    if (records.empty()) {
        cout << "No attendance records found for you Staff ID." << endl;
        return;
    }

    mergeSort(records, 0, records.size() - 1, true);
    
    cout << "Attendance Records (Sorted by Date):" << endl;
    cout << "=====================================" << endl;
    
    for (const auto& rec : records) {
        string d = rec.getDate();
        string t = rec.getTime();
        string sName = rec.getStudentID();
        string status = rec.getAttendanceStatus();

        cout << "[" << d << " " << t << "] ID: " << rec.getAttendanceID() 
             << " | " << sName << " (" << status << ")" << endl;
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
    cout << "5. Filter by Status (Present/Absent)" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            results = records; 
            break;
        case 2:
            cout << "Enter Date: ";
            cin >> searchKey;
            results = filterByDate(records, searchKey);
            break;
        case 3:
            cout << "Enter Attendance ID: ";
            cin >> searchKey;
            results = filterByAttendanceID(records, searchKey);
            break;
        case 4:
            cout << "Enter Student ID: ";
            cin >> searchKey;
            results = filterByStudentID(records, searchKey);
            break;
        case 5:
            cout << "Enter Status: ";
            cin >> searchKey;
            results = filterByStatus(records, searchKey);
            break;
        default:
            cout << "Invalid choice. Showing all records." << endl;
            results = records;
            break;
    }

    cout << "\n[ Results ]" << endl;
    if (results.empty()) {
        cout << "No records found matching criteria." << endl;
    } else {
        cout << "----------------------------------------------------------------" << endl;
        cout << "Date       | Time     | AttID  | Student Name         | Status" << endl;
        cout << "----------------------------------------------------------------" << endl;
        
        for (const auto& rec : results) {
            string d = rec.getDate();
            string t = rec.getTime();
            string status = rec.getAttendanceStatus();
            string sName = rec.getStudentID();
            
            cout << d << " | " << t << " | " << rec.getAttendanceID() 
                 << " | " << sName << " | " << status << endl;
        }
        cout << "----------------------------------------------------------------" << endl;
        cout << "Total displayed: " << results.size() << endl;
    }
}

void Staff::exportSummary(const vector<Attendance>& records, string attendanceID){
    cout << "   Generating Summary for Session: " << attendanceID << endl;
    vector<Attendance> sessionRecords = filterByAttendanceID(records, attendanceID);
    if (sessionRecords.empty()) {
        cout << "[Error] No records found for Attendance ID: " << attendanceID << endl;
        return;
    }
    quickSort(sessionRecords, 0, sessionRecords.size() - 1);
    int total = sessionRecords.size();
    int present = 0, absent = 0, late = 0;

    for (const auto& rec : sessionRecords) {
        string status = rec.getAttendanceStatus();
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
        string lecturer = findStaffNameByID(records[0].getStaffID());
        outFile << "Lecturer     : " << lecturer << "\n";
        outFile << "Total Students: " << total << "\n";
        outFile << "Stats        : Present: " << present << " | Absent: " << absent << " | Late: " << late << "\n";
        outFile << "========================================\n";
        outFile << left << setw(25) << "Student Name" << setw(15) << "Student ID" << "Status\n";
        outFile << "--------------------------------------------------\n";

        for (const auto& rec : sessionRecords) {
            string name = findStudentNameByID(rec.getStudentID());
            string id = rec.getStudentID();
            string status = rec.getAttendanceStatus();
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

void mergeSort(vector<Attendance>& attendances, int left, int right, bool sortByDate) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(attendances, left, mid, sortByDate);
        mergeSort(attendances, mid + 1, right, sortByDate);
        merge(attendances, left, mid, right, sortByDate);
    }
}

void merge(vector<Attendance>& attendances, int left, int mid, int right, bool sortByDate) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Attendance> L(n1);
    vector<Attendance> R(n2);

    for (int i = 0; i < n1; i++) L[i] = attendances[left + i];
    for (int j = 0; j < n2; j++) R[j] = attendances[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        string dateL = L[i].getDate();
        string dateR = R[j].getDate();

        if ((sortByDate && dateL <= dateR) || (!sortByDate && dateL >= dateR)) {
            attendances[k] = L[i];
            i++;
        } else {
            attendances[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) { attendances[k] = L[i]; i++; k++; }

    while (j < n2) { attendances[k] = R[j]; j++; k++; }
}

int partition(vector<Attendance>& arr, int low, int high) {
    string pivot = arr[high].getStudentID(); 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].getStudentID() <= pivot) {
            i++; 
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<Attendance>& arr, int low, int high) {
    if (low < high) {
        int cut = partition(arr, low, high);
        quickSort(arr, low, cut - 1);
        quickSort(arr, cut + 1, high);
    }
}