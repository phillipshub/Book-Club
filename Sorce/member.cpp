/*
 File: member.cpp
 Author: Phillip A
 Date: 8-18-2024
 CPP: 17

 Members Class Functions
 member.cpp contains the function definitions for methods to be performed on
 member objects.
*/
// -----10--------20--------30--------40--------50--------60--------70--------80
#include "member.h"
#include <string>
using namespace std;

Member::Member() {}

Member::Member(string name, string phone_number, string email) {
    // Set member's name to name
    Member::member_name = name;
    // Set member's phone number to phone number
    Member::member_phone_number = phone_number;
    // Set member's email to email
    Member::member_email = email;
}

Member::~Member() {}

void Member::setName(string name) {
    // Set member's name to name
    Member::member_name = name;
}

void Member::setPhoneNumber(string phone_number) {
    // Set member's phone number to phone number
    Member::member_phone_number = phone_number;
}

void Member::setEmail(string email) {
    // Set member's email to email
    Member::member_email = email;
}

string Member::getName() const {
    // Return member's name
    return Member::member_name;
}

string Member::getPhoneNumber() const {
    // Return member's phone number
    return Member::member_phone_number;
}

string Member::getEmail() const {
    // Return member's email address
    return Member::member_email;
}
