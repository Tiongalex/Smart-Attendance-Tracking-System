#include "Staff.h"
#include "Attendance.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void mergeSort(vector<Attendance>& attendances, int left, int right, bool sortByDate = true);
void merge(vector<Attendance>& attendances, int left, int mid, int right, bool sortByDate);
int binarySearch(const vector<Attendance>& attendances, const string& key, bool searchByDate = true);

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

void Staff::viewAttendance(){
     vector<Attendance> attendances;
    
    // In real implementation, you would load attendances from database/file
    // attendances = loadAttendancesForStaff(this->getID());
    
    if (attendances.empty()) {
        cout << "No attendance records found." << endl;
        return;
    }
    
    // Sort attendances by date using merge sort
    mergeSort(attendances, 0, attendances.size() - 1, true);
    
    cout << "Attendance Records (Sorted by Date):" << endl;
    cout << "=====================================" << endl;
    
    for (const auto& attendance : attendances) {
        cout << "Attendance ID: " << attendance.getAttendanceID() << endl;
        vector<string> dates = attendance.getDate();
        if (!dates.empty()) {
            cout << "Date: " << dates[0] << endl; // Using first date
        }
        cout << "-------------------------" << endl;
    }
    
    // Binary search example - search for specific attendance by date
    string searchDate;
    cout << "\nEnter date to search (YYYY-MM-DD): ";
    cin >> searchDate;
    
    int foundIndex = binarySearch(attendances, searchDate, true);
    
    if (foundIndex != -1) {
        cout << "Attendance found at index " << foundIndex << ":" << endl;
        Attendance found = attendances[foundIndex];
        cout << "Attendance ID: " << found.getAttendanceID() << endl;
        
        vector<Student> students = found.getStudent();
        vector<string> status = found.getAttendanceStatus();
        vector<string> dates = found.getDate();
        vector<string> times = found.getTime();
        
        cout << "Student Attendance Details:" << endl;
        for (size_t i = 0; i < students.size() && i < status.size(); i++) {
            cout << "Student: " << students[i].getName() 
                 << " | Status: " << status[i];
            if (i < dates.size()) cout << " | Date: " << dates[i];
            if (i < times.size()) cout << " | Time: " << times[i];
            cout << endl;
        }
    } else {
        cout << "No attendance record found for date: " << searchDate << endl;
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

int binarySearch(const vector<Attendance>& attendances, const string& key, bool searchByDate) {
    int left = 0;
    int right = attendances.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        string currentValue;
        if (searchByDate) {
            vector<string> dates = attendances[mid].getDate();
            currentValue = dates.empty() ? "" : dates[0];
        } else {
            currentValue = attendances[mid].getAttendanceID();
        }
        
        if (currentValue == key) {
            return mid; // Found
        } else if (currentValue < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Not found
}