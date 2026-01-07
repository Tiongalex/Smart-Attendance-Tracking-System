#ifndef REGISTRATIONQUEUE_H
#define REGISTRATIONQUEUE_H

#include <iostream>
#include <string>
#include "User.h" 

using namespace std;

struct PendingUser {
    string role;     
    string id;
    string name;
    string password;
    string course; 

    PendingUser(string r, string i, string n, string p, string  c) 
        : role(r), id(i), name(n), password(p), course(c) {}
    
    PendingUser() {}
};

struct QNode {
    PendingUser data;
    QNode* next;
};

class RegistrationQueue {
private:
    QNode* front;
    QNode* rear;

public:
    RegistrationQueue() {
        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(string id, string name, string password, string course) {
        PendingUser newUser("Student",id, name, password, course);
        
        QNode* newNode = new QNode;
        newNode->data = newUser;
        newNode->next = nullptr;

        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "\n[Success] Registration submitted! Please wait for Admin approval.\n";
        system("pause");
    }

    void dequeue() {
        if (isEmpty()) return;
        
        QNode* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;

        system("pause");
    }

    PendingUser peek() {
        if (isEmpty()) return PendingUser("", "", "", "",""); 
        return front->data;
    }

    PendingUser getFront() {
        if (isEmpty()) {
            cout << "[Error] Queue is empty. No next request to review." << endl;
            return PendingUser("", "", "", "","");
        }
        return front->data; 
    }

    PendingUser getRear() {
        if (isEmpty()) {
            cout << "[Error] Queue is empty. No recent entries." << endl;
            return PendingUser("", "", "", "","");
        }
        return rear->data;
    }
};

#endif