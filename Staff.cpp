#include "Staff.h"
#include "Attendance.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void mergeSort(vector<Attendance>& attendances, int left, int right, bool sortByDate = true);
void merge(vector<Attendance>& attendances, int left, int mid, int right, bool sortByDate);

vector<Attendance> filterByDate(const vector<Attendance>& records, string targetDate) {
    vector<Attendance> matchingRecords;
    for (const auto& record : records) {
        if (!record.getDate().empty()) {
            if (record.getDate()[0] == targetDate) {
                matchingRecords.push_back(record);
            }
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
        vector<Student> students = record.getStudent();
        bool found = false;
        for (const auto& s : students) {
            if (s.getID() == targetStudentID) {
                found = true;
                break;
            }
        }
        
        if (found) {
            matchingRecords.push_back(record);
        }
    }
    return matchingRecords;
}

vector<Attendance> filterByStatus(const vector<Attendance>& records, string targetStatus) {
    vector<Attendance> matchingRecords;
    for (const auto& record : records) {
        vector<string> statuses = record.getAttendanceStatus();
        bool found = false;
        for (const auto& s : statuses) {
            if (s == targetStatus) {
                found = true;
                break;
            }
        }
        
        if (found) {
            matchingRecords.push_back(record);
        }
    }
    return matchingRecords;
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

void Staff::createAttendance(){

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
        string d = rec.getDate().empty() ? "N/A" : rec.getDate()[0];
        string t = rec.getTime().empty() ? "N/A" : rec.getTime()[0];
        string sName = rec.getStudent().empty() ? "Unknown" : rec.getStudent()[0].getName();
        string status = rec.getAttendanceStatus().empty() ? "N/A" : rec.getAttendanceStatus()[0];

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
            string d = rec.getDate().empty() ? "N/A" : rec.getDate()[0];
            string t = rec.getTime().empty() ? "N/A" : rec.getTime()[0];
            string status = rec.getAttendanceStatus().empty() ? "N/A" : rec.getAttendanceStatus()[0];
            string sName = rec.getStudent().empty() ? "Unknown" : rec.getStudent()[0].getName();
            
            cout << d << " | " << t << " | " << rec.getAttendanceID() 
                 << " | " << sName << " | " << status << endl;
        }
        cout << "----------------------------------------------------------------" << endl;
        cout << "Total displayed: " << results.size() << endl;
    }
}

void Staff::exportSummary(string attendanceID){

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

    for (int i = 0; i < n1; i++)
        L[i] = attendances[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = attendances[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        string dateL = L[i].getDate().empty() ? "" : L[i].getDate()[0];
        string dateR = R[j].getDate().empty() ? "" : R[j].getDate()[0];

        if ((sortByDate && dateL <= dateR) || (!sortByDate && dateL >= dateR)) {
            attendances[k] = L[i];
            i++;
        } else {
            attendances[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        attendances[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        attendances[k] = R[j];
        j++;
        k++;
    }
}
