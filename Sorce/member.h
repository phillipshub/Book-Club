/*
 File: member.h
 Author: Phillip A
 Date: 8-18-2024
 CPP: 17

 Member Class
 The member class defines a member object, its attributes and methods. 
*/
// -----10--------20--------30--------40--------50--------60--------70--------80
#ifndef member_h
#define member_h
#include <string>
using namespace std;

class Member {
private:
    // Member Attributes
    string member_name;
    string member_phone_number;
    string member_email;
public:
    // Member Functions
    Member();
    Member(string name, string phone_number, string email);
    ~Member();
    void setName(string name);
    void setPhoneNumber(string phone_number);
    void setEmail(string email);
    string getName() const;
    string getPhoneNumber() const;
    string getEmail() const;
};
#endif /* member_h */
