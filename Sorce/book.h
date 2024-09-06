/*
 File: book.h
 Author: Phillip A
 Date: 8-18-2024
 CPP: 17

 Book Class
 The book class defines a book object, its attributes and methods. 
*/
// -----10--------20--------30--------40--------50--------60--------70--------80
#ifndef book_h
#define book_h
#include <string>
using namespace std;

class Book {
private:
    // Book Attributes
    string book_title;
    string book_author_name;
    bool book_read_state;
public:
    // Book Functions
    Book();
    Book(string book_title, string author_name, bool read_state);
    ~Book();
    void setTitle(string book_title);
    void setAuthor(string author_name);
    void setRead(bool read);
    string getTitle() const;
    string getAuthor() const;
    bool getReadState() const;
};
#endif /* book_h */
