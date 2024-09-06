/*
 File: book.cpp
 Author: Phillip A
 Date: 8-18-2024
 CPP: 17

 Book Class Functions
 book.cpp contains the function definitions for methods to be performed on
 book objects.
*/
// -----10--------20--------30--------40--------50--------60--------70--------80
#include "book.h"
#include <string>
using namespace std;

Book::Book() {}

Book::Book(string title, string author_name, bool read_state) {
    // Set book's title
    Book::book_title = title;
    // Set book's author's name
    Book::book_author_name = author_name;
    // Set book's state
    Book::book_read_state = read_state;
}

Book::~Book() {}

void Book::setTitle(string title) {
    // Set book's title
    Book::book_title = title;
}

void Book::setAuthor(string author_name) {
    // Set book's author's name
    Book::book_author_name = author_name;
}

void Book::setRead(bool read_state) {
    // Set book's state
    Book::book_read_state = read_state;
}

string Book::getTitle() const {
    // Return book's title
    return Book::book_title;
}

string Book::getAuthor() const {
    // Return book's author's name
    return Book::book_author_name;
}

bool Book::getReadState() const {
    // Return book's state
    return Book::book_read_state;
}
