#include "Login.h"
#include <iostream>
#include <string>
#include <vector>
#include "LinkedList.h"
using namespace std;

Login::Login(){}

Login::Login(const LinkedList<string>& accountType, const LinkedList<string>& accountID, const LinkedList<string>& accountPassword): accountType(accountType), accountID(accountID), accountPassword(accountPassword) {}

int Login::sequentialSearch(const string& search_key, const LinkedList<string>& array) {
    int p;
    int index = -1;

    for (p = 0; p < array.size(); p++) {
        if (search_key == *array.searchNode(p)) {
            index = p;
            break;
        }
    }
    return index;
}

bool Login::login(const string& type, const string& id, const string& pass) {
    int index = sequentialSearch(id, accountID);

    if (index == -1)
        return false;

    if (*accountType.searchNode(index) != type)
        return false;

    if (*accountPassword.searchNode(index) != pass)
        return false;

    return true;
}

