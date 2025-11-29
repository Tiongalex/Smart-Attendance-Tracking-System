#include "Staff.h"
#include "Attendance.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int partition(vector<Attendance>& arr, int low, int high);
void quickSort(vector<Attendance>& arr, int low, int high);
void mergeSort(vector<Attendance>& attendances, int left, int right, bool sortByDate);
void merge(vector<Attendance>& attendances, int left, int mid, int right, bool sortByDate);

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
        if(record.getStudent().getID() == targetStudentID){
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
        string d = rec.getDate();
        string t = rec.getTime();
        string sName = rec.getStudent().getName();
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
            string sName = rec.getStudent().getName();
            
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
        outFile << "Lecturer     : " << this->getName() << "\n";
        outFile << "Total Students: " << total << "\n";
        outFile << "Stats        : Present: " << present << " | Absent: " << absent << " | Late: " << late << "\n";
        outFile << "========================================\n";
        outFile << left << setw(25) << "Student Name" << setw(15) << "Student ID" << "Status\n";
        outFile << "--------------------------------------------------\n";

        for (const auto& rec : sessionRecords) {
            string name = rec.getStudent().getName();
            string id = rec.getStudent().getID();
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

int partition(vector<Attendance>& arr, int low, int high){
    int loop, cutPoint, bottom, top;
    string pivot = arr[low].getStudent().getName();
    bottom = low;
    top = high;

    while(loop){
        while (arr[top].getStudent().getName()>pivot)
            top--;
        while (arr[bottom].getStudent().getName() < pivot)
            bottom++;

        if (bottom < top) swap(arr[bottom], arr[top]);
        else{
            loop = 0;
            cutPoint = top;
        }
    }
    return cutPoint;
}
void quickSort(vector<Attendance>& arr, int low, int high){
    if (low < high) {
        int cut = partition(arr, low, high);
        quickSort(arr, low, cut);
        quickSort(arr, cut+1, high);
    }
}