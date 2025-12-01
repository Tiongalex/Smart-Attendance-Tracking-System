#include "Student.h"
#include "Attendance.h"  
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

void mergeSort2(vector<Attendance>& attendances, int left, int right, bool sortByDate);
void merge2(vector<Attendance>& attendances, int left, int mid, int right, bool sortByDate);

Student::Student() {}

Student::Student(string id, string name, string role, string course): User(id, name, role) {
    this->course=course;
}

string Student::getCourse(){
    return this->course;
}

void Student::setCourse(string course){
    this->course=course;
}

Attendance Student::checkIn(string studentID, const vector<Attendance>& availableSession){
    if (availableSession.empty()) {
        cout << "No attendance sessions available today.\n";
        return Attendance(); // return empty object
    }

    cout << "Available Attendance Sessions:\n";
    for (auto &att : availableSession) {
        cout << att.getAttendanceID() << " "
             << att.getStaffID() << " "
             << att.getDate() << " "
             << att.getTime() << " "
             << att.getEndTime() << "\n";
    }

    cout << "\nEnter Attendance ID to check-in: ";
    string inputAID;
    cin >> inputAID;

    Attendance session;
    bool found = false;

    for (auto &att : availableSession) {
        if (att.getAttendanceID() == inputAID) {
            session = att;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Invalid Attendance ID.\n";
        return Attendance();
    }

    // ------------------------------------------------------
    //  Determine Present or Late
    // ------------------------------------------------------

    // Get current time
    time_t now = time(nullptr);
    tm *t = localtime(&now);

    char currentTimeStr[9];
    sprintf(currentTimeStr, "%02d:%02d:%02d",
            t->tm_hour, t->tm_min, t->tm_sec);

    string nowStr = currentTimeStr;
    string endTime = session.getEndTime();

    string status = "Absent"; // default

    if (nowStr <= endTime)
        status = "Present";
    else
        status = "Late";

    // ------------------------------------------------------
    // Create Attendance for this student
    // ------------------------------------------------------

    Attendance newRecord(
        session.getAttendanceID(),
        session.getStaffID(),
        session.getDate(),
        session.getTime(),
        session.getEndTime(),
        studentID,
        status
    );

    cout << "\nCheck-in successful!\n";
    cout << "Status: " << status << "\n";

    return newRecord;
}

void mergeSort2(vector<Attendance>& attendances, int left, int right, bool sortByDate) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort2(attendances, left, mid, sortByDate);
        mergeSort2(attendances, mid + 1, right, sortByDate);
        merge2(attendances, left, mid, right, sortByDate);
    }
}

void merge2(vector<Attendance>& attendances, int left, int mid, int right, bool sortByDate) {
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

void Student::viewAttendance(const vector<Attendance>& allRecords) {
    cout << "\n--- Attendance History for Student: " << this->getName() << " ---\n";

    // Collect only this student's records
    vector<Attendance> myRecords;
    for (const auto& rec : allRecords) {
        if (rec.getStudentID() == this->getID()) {
            myRecords.push_back(rec);
        }
    }

    if (myRecords.empty()) {
        cout << "No attendance records found.\n";
        return;
    }

    // Sort by date using your mergeSort function
    mergeSort2(myRecords, 0, myRecords.size() - 1, true);

    cout << "\nAttendance Records (Sorted by Date):\n";
    cout << "==============================================\n";
    cout << left << setw(12) << "Date"
         << setw(10) << "Time"
         << setw(10) << "AttID"
         << setw(10) << "Status" << "\n";
    cout << "----------------------------------------------\n";

    for (const auto& rec : myRecords) {
        cout << left << setw(12) << rec.getDate()
             << setw(10) << rec.getTime()
             << setw(10) << rec.getAttendanceID()
             << setw(10) << rec.getAttendanceStatus()
             << "\n";
    }

    cout << "----------------------------------------------\n";
    cout << "Total Records: " << myRecords.size() << endl;
}
