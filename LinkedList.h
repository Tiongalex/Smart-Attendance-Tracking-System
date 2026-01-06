#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <functional>
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(const T& d): data(d), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int count;

public:
    LinkedList(): head(nullptr), count(0) {}
    ~LinkedList() { clear(); }

    LinkedList(const LinkedList& other) : head(nullptr), count(0) {
        Node<T>* cur = other.head;
        while (cur) {
            addNode(cur->data);
            cur = cur->next;
        }
    }

    LinkedList& operator=(const LinkedList& other) {
    if (this == &other) return *this;

    clear();

    Node<T>* cur = other.head;
    while (cur) {
        addNode(cur->data);
        cur = cur->next;
    }
    return *this;
    }

    void addNode(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        ++count;
    }

    void deleteNode(const int index){
        if (head==NULL || index<0 || index>=size()) return;

        Node<T>* temp=head;
        Node<T>* bef=NULL;

        if (index==0){
            head=head->next;
            delete temp;
            --count;
            return;
        }

        for (int i=0;i<index;i++){
            bef=temp;
            temp=temp->next;
        } 

        bef->next=temp->next;
        delete temp;
        --count;
    }

    int size() const {
        return count;
    }

    T* searchNode(int index) {
        if (index < 0) return nullptr;
        Node<T>* cur = head;
        int i = 0;
        while (cur) {
            if (i == index) return &cur->data;
            cur = cur->next;
            i++;
        }
        return nullptr;
    }

    const T* searchNode(int index) const {
        if (index < 0) return nullptr;
        const Node<T>* cur = head;
        int i = 0;
        while (cur) {
            if (i == index) return &cur->data;
            cur = cur->next;
            i++;
        }
        return nullptr;
    }

    void displayList() const {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* cur = head;
        int index = 0;

        while (cur) {
            cout << "[" << index << "] " << cur->data << endl;
            cur = cur->next;
            ++index;
        }
    }


    Node<T>* getHead() {
        return head;
    }

    const Node<T>* getHead() const {
        return head;
    }

    void setHead(Node<T>* newHead){
        head=newHead;
    }

    void clear() {
        Node<T>* cur = head;
        while (cur) {
            Node<T>* tmp = cur->next;
            delete cur;
            cur = tmp;
        }
        head = nullptr;
        count = 0;
    }
};

#endif
