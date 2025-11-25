#include <iostream>
#include "User.h"
using namespace std;

User::User(){}
User::User(string id, string name, string role){
    this->id=id;
    this->name=name;
    this->role=role;
}

string User::getID(){
    return this->id;
}

string User::getName(){
    return this->name;
}

string User::getRole(){
    return this->role;
}

void User::setID(string id){
    this->id=id;
}

void User::setName(string name){
    this->name=name;
}

void User::setRole(string role){
    this->role=role;
}