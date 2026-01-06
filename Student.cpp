#include "Student.h"
#include "Attendance.h"  
#include "LinkedList.h"
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

void mergeSort2(LinkedList<Attendance>& attendances, int left, int right, bool sortByDate);
void merge2(LinkedList<Attendance>& attendances, int left, int mid, int right, bool sortByDate);

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

Attendance Student::checkIn(string studentID, LinkedList<Attendance>& availableSession){
    if (!availableSession.getHead()) {
        cout << "No attendance sessions available today.\n";
        return Attendance(); 
    }

    cout << "Available Attendance Sessions:\n";
    for (int i=0;i<availableSession.size();i++) {
        cout << availableSession.searchNode(i)->getAttendanceID() << " "
             << availableSession.searchNode(i)->getStaffID() << " "
             << availableSession.searchNode(i)->getDate() << " "
             << availableSession.searchNode(i)->getTime() << " "
             << availableSession.searchNode(i)->getEndTime() << "\n";
    }

    cout << "\nEnter Attendance ID to check-in: ";
    string inputAID;
    cin >> inputAID;

    Attendance* session;
    bool found = false;

    for (int i=0;i<availableSession.size();i++) {
        if (availableSession.searchNode(i)->getAttendanceID() == inputAID) {
            session = availableSession.searchNode(i);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Invalid Attendance ID.\n";
        return Attendance();
    }

    time_t now = time(nullptr);
    tm *t = localtime(&now);

    char currentTimeStr[9];
    sprintf(currentTimeStr, "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);

    string nowStr = currentTimeStr;
    string endTime = session->getEndTime();

    string status = "Absent"; 

    if (nowStr <= endTime)
        status = "Present";
    else
        status = "Late";

    Attendance newRecord(
        session->getAttendanceID(),
        session->getStaffID(),
        session->getDate(),
        session->getTime(),
        session->getEndTime(),
        studentID,
        status
    );

    cout << "\nCheck-in successful!\n";
    cout << "Status: " << status << "\n";

    return newRecord;
}

void mergeSort2(LinkedList<Attendance>& attendances, int left, int right, bool sortByDate) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort2(attendances, left, mid, sortByDate);
        mergeSort2(attendances, mid + 1, right, sortByDate);
        merge2(attendances, left, mid, right, sortByDate);
    }
}

void merge2(LinkedList<Attendance>& attendances, int left, int mid, int right, bool sortByDate) {
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

void Student::viewAttendance(LinkedList<Attendance>& allRecords) {
    cout << "\n--- Attendance History for Student: " << this->getName() << " ---\n";

    LinkedList<Attendance> myRecords;
    for (int i=0;i<allRecords.size();i++) {
        if (allRecords.searchNode(i)->getStudentID() == this->getID()) {
            myRecords.addNode(*allRecords.searchNode(i));
        }
    }

    if (!myRecords.getHead()) {
        cout << "No attendance records found.\n";
        return;
    }

    mergeSort2(myRecords, 0, myRecords.size() - 1, true);

    cout << "\nAttendance Records (Sorted by Date):\n";
    cout << "==============================================\n";
    cout << left << setw(12) << "Date"
         << setw(10) << "Time"
         << setw(10) << "AttID"
         << setw(10) << "Status" << "\n";
    cout << "----------------------------------------------\n";

    for (int i=0;i<myRecords.size();i++) {
        cout << left << setw(12) << myRecords.searchNode(i)->getDate()
             << setw(10) << myRecords.searchNode(i)->getTime()
             << setw(10) << myRecords.searchNode(i)->getAttendanceID()
             << setw(10) << myRecords.searchNode(i)->getAttendanceStatus()
             << "\n";
    }

    cout << "----------------------------------------------\n";
    cout << "Total Records: " << myRecords.size() << endl;
}
