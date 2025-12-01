#include "Login.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Login::Login(){}

Login::Login(vector<string> accountType, vector<string> accountID, vector<string> accountPassword): accountType(accountType), accountID(accountID), accountPassword(accountPassword) {}

int Login::sequentialSearch(string search_key, vector<string> array) {
    int p;
    int index = -1;

    for (p = 0; p < array.size(); p++) {
        if (search_key == array[p]) {
            index = p;
            break;
        }
    }
    return index;
}

bool Login::login(string type, string id, string pass) {
    int index = sequentialSearch(id, accountID);

    if (index == -1)
        return false;

    if (accountType[index] != type)
        return false;

    if (accountPassword[index] != pass)
        return false;

    return true;
}
