/*
 Program: Book Club
 Author: Phillip A
 Date: 8-17-2024
 CPP: 17

 The Book Club application is built for managing a book club. The application
 keeps track of member and book information such as each members contact
 information, a books title, author, and whether a book has been read or not.
 There is also a random select feature for both books and club members.
*/
// -----10--------20--------30--------40--------50--------60--------70--------80
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <list>
#include <vector>
#include <cctype>
#include <cstdlib>
#include "member.h"
#include "book.h"
using namespace std;


// Data Handeling
void loadMembers(list<Member>& members);
void loadBooks(list<Book>& books);
void loadData(list<Member>& members, list<Book>& books);
void saveMembers(const list<Member>& members);
void saveBooks(const list<Book>& books);
void saveState(const list<Member>& members, const list<Book>& books);
// User Interface
void greeting();
int mainMenu();
// UI Members
int memberMenu();
void memberFunctions(list<Member>& members);
// UI Books
int bookMenu();
void bookFunctions(list<Book>& books);
// Member Functions
void listMembers(const list<Member>& members);
string getMemberName(const list<Member>& members);
string getMemberPhoneNumber();
string getMemberEmail();
void addMember(list<Member>& members);
void removeMember(list<Member>& members);
const Member* findMemberToUpdate(const list<Member>& members, string name);
int getMemberModifyCase(const Member* modify_member);
void updateMemberInformation(list<Member>& members);
void randomMember(const list<Member>& members);
// Book Functions
void listBooks(const list<Book>& boks);
string getBookTitle(const list<Book>& books);
string getAuthorName();
bool getBookReadState();
void addBook(list<Book>& books);
void removeBook(list<Book>& books);
const Book* findBookToUpdate(const list<Book>& books, string title);
int getBookModifyCase(const Book* modify_book);
void updateBookInformation(list<Book>& books);
void randomBook(const list<Book>& books);
// Multipurpose Functions
int randomIndex(int vector_size);
string titleCase(string title);
string formatPhoneNumber(string phone_number);
bool yesNo(string answer);
void clearConsole();


// Main
int main() {
    // Set Colors on Windows
    #ifdef _WIN32
    // Windows set console colors
        system("color F5");
    #elif _WIN64
    // Windows set console colors
        system("color F5");
    #endif
    // Club members
    list<Member> members;
    // Books
    list<Book> books;
    // Load data
    loadData(members, books);
    //Greeting message
    greeting();
    // Exit value
    const int EXIT = 3;
    // Option
    int option;
    // Run options until case EXIT
    do {
        // Get option from main menu
        option = mainMenu();

        switch (option) {
        case 1:
            // Run member functions
            memberFunctions(members);
            break;
        case 2:
            // Run book functions
            bookFunctions(books);
            break;
        case EXIT:
            // Save state before exit
            saveState(members, books);
            break;
        default:
            // Save and exit failure
            saveState(members, books);
            exit(EXIT_FAILURE);
            break;
        }
        // Continues while not case EXIT
    } while (option != EXIT);
    // Successfully exit program
    return 0;
} // ---------------------------------------------------------------------------

// Load members data
void loadMembers(list<Member>& members) {
    // Member attributes
    string name;
    string phone_number;
    string email;
    // Input path
    string file_name = "Assets/Members.dat";
    // Initialize input
    ifstream input_file(file_name);
    // Check if opened
    if (input_file.is_open()) {
        while (!input_file.eof()) {
            // Get data if not last object
            if (!getline(input_file, name)) {
                break;
            }
            getline(input_file, phone_number);
            getline(input_file, email);
            // Add object to list
            members.push_back(Member(name, phone_number, email));
        }
    } else {
        cerr << "\n  Access Member Data Failed.\n";
    }
    // Close file
    input_file.close();
} // ---------------------------------------------------------------------------

// Load books data
void loadBooks(list<Book>& books) {
    // Book attributes
    string title;
    string author;
    string read_state;
    // Input path
    string file_name = "Assets/Books.dat";
    // Initialize input
    ifstream input_file(file_name);
    // Check if opened
    if (input_file.is_open()) {
        while (!input_file.eof()) {
            // Get data if not last object
            if (!getline(input_file, title)) {
                break;
            }
            getline(input_file, author);
            getline(input_file, read_state);
            // Add object to list
            books.push_back(Book(title, author, stoi(read_state)));
        }
    } else {
        cerr << "\n  Access Book Data Failed.\n";
    }
    // Close file
    input_file.close();
} // ---------------------------------------------------------------------------

// Load data
void loadData(list<Member>& members, list<Book>& books) {
    // Import Members
    loadMembers(members);
    // Import Books
    loadBooks(books);
} // ---------------------------------------------------------------------------

// Save Members to Members.dat
void saveMembers(const list<Member>& members) {
    // Initialize output
    ofstream members_data_file;
    // Set output path
    members_data_file.open("Assets/Members.dat", ios::out);
    // Check if opened properly
    if (members_data_file.is_open()) {
        for (list<Member>::const_iterator it = members.begin();
            it != members.end(); it++) {
            // Write object data to file
            members_data_file << it->getName() << '\n';
            members_data_file << it->getPhoneNumber() << '\n';
            members_data_file << it->getEmail() << '\n';
        }
    } else {
        cerr << "\n  Save Member Data Failed.\n";
    }
    // Close file
    members_data_file.close();
} // ---------------------------------------------------------------------------

// Save Books to Books.dat
void saveBooks(const list<Book>& books) {
    // Initialize output
    ofstream books_data_file;
    // Set output path
    books_data_file.open("Assets/Books.dat", ios::out);
    // Check if opened properly
    if (books_data_file.is_open()) {
        for (list<Book>::const_iterator it = books.begin();
            it != books.end(); it++) {
            // Write object data to file
            books_data_file << it->getTitle() << '\n';
            books_data_file << it->getAuthor() << '\n';
            books_data_file << it->getReadState() << '\n';
        }
    } else {
        cerr << "\n  Save Book Data Failed.\n";
    }
    // Close file
    books_data_file.close();
} // ---------------------------------------------------------------------------

// Save current state of persistent data
void saveState(const list<Member>& members, const list<Book>& books) {
    // Save Members to file
    saveMembers(members);
    // Save Books to file
    saveBooks(books);
} // ---------------------------------------------------------------------------
// Displays greeting
void greeting() {
    cout << "\n   Hello, Book Club!\n"
        "  -------------------";
} // ---------------------------------------------------------------------------

// Displays main menu returns numeric choice
int mainMenu() {
    // Choice range
    const int MIN_CASE = 1;
    const int MAX_CASE = 3;
    // Menu choice
    int choice;
    // Display options until a valid choice is made
    do {
        // Display choices
        cout << "\n"
            "  Main Menu:\n"
            "  1) Members\n"
            "  2) Books\n"
            "  3) Exit\n"
            "\n"
            "  Enter your selection: ";
        // Retrieve choice
        cin >> choice;
        // Check for user error
        if (cin.fail() || choice < MIN_CASE || choice > MAX_CASE) {
            // Clear input stream and inform user
            cin.clear();
            cin.ignore();
            cout << "\n  Invalid option, please make a valid selection.\n";
        } else {
            // Remove newline character from input stream
            cin.ignore();
        }
        // Continue while choice is out of range
    } while (choice < MIN_CASE || choice > MAX_CASE);
    // Clear console
    clearConsole();
    // Return valid choice
    return choice;
} // ---------------------------------------------------------------------------

// Displays member menu returns numeric choice
int memberMenu() {
    // Choice range
    const int MIN_CASE = 1;
    const int MAX_CASE = 6;
    // Choice
    int choice;
    // Perform actions until return to main menu
    do {
        cout << "\n"
            "  Member Menu:\n"
            "  1) List Members\n"
            "  2) Add Member\n"
            "  3) Remove Member\n"
            "  4) Update Member Information\n"
            "  5) Random Member\n"
            "  6) Return to Main Menu\n"
            "\n"
            "  Enter your selection: ";
        // Retrieve choice
        cin >> choice;
        // Check for user error
        if (cin.fail() || choice < MIN_CASE || choice > MAX_CASE) {
            // Clear input stream and inform user
            cin.clear();
            cin.ignore();
            cout << "\n  Invalid option, please make a valid selection.\n";
        } else {
            // Remove newline character from input stream
            cin.ignore();
        }
        // Continue while choice is out of range
    } while (choice < MIN_CASE || choice > MAX_CASE);
    // Clear console
    clearConsole();
    // Return option
    return choice;
} // ---------------------------------------------------------------------------

// Member functions
void memberFunctions(list<Member>& members) {
    // Run member functions
    const int MAIN_MENU = 6;
    // Option
    int option;
    do {
        option = memberMenu();
        // Execute option
        switch (option) {
        case 1:
            // List Members
            listMembers(members);
            break;
        case 2:
            // Add Member
            addMember(members);
            break;
        case 3:
            // Remove Member
            removeMember(members);
            break;
        case 4:
            // Update Member Information
            updateMemberInformation(members);
            break;
        case 5:
            // Random Member
            randomMember(members);
            break;
        case MAIN_MENU:
            // Return to main menu
            return;
        default:
            // Return to main menu
            return;
        }
        // Continue while option not main menu
    } while (option != MAIN_MENU);
} // ---------------------------------------------------------------------------

// List members
void listMembers(const list<Member>& members) {
    // If there are members list by name, number, email
    if (!members.empty()) {
        cout << "\n  Member List"
            "\n  -----------";
        for (list<Member>::const_iterator it = members.begin();
            it != members.end(); it++) {
            cout << "\n"
                "  Name: " << it->getName() << '\n' <<
                "  Phone Number: " << it->getPhoneNumber() << '\n' <<
                "  Email: " << it->getEmail() << '\n';
        }
    } else {
        // Report there are no members
        cout << "\n  There are no members at this time.\n";
    }
} // ---------------------------------------------------------------------------

// Get member name
string getMemberName(const list<Member>& members) {
    // Member name
    string name;
    // Unique member name
    bool unique_name;
    do {
        // Set unique_name to true
        unique_name = true;
        cout << "\n  Enter member's full name: ";
        getline(cin, name);
        // Format name
        name = titleCase(name);
        // Make sure user name is unique
        if (!members.empty()) {
            // Not empty list search for user name
            for (list<Member>::const_iterator it = members.begin();
                it != members.end(); it++) {
                // User found
                if (it->getName() == name) {
                    cout << "\n  User exists, new user name must be unique.\n";
                    unique_name = false;
                    break;
                }
            }
        }
        // Continue if member name is not unique
    } while (!unique_name);
    // Return unique member name
    return name;
} // ---------------------------------------------------------------------------

// Get member phone number
string getMemberPhoneNumber() {
    // Phone number
    string phone_number;
    // Number of digits in U.S. phone number
    const int PHONE_NUMBER_DIGITS = 10;
    do {
        // phone_number must be ten characters
        cout << "  Enter ten digit phone number(digits only): ";
        getline(cin, phone_number);
        // Validate number of digits
        if (phone_number.length() != PHONE_NUMBER_DIGITS) {
            cout << "\n  You entered: " << phone_number << ". "
                " Phone numbers must contain ten digits.\n";
        }
        // Continue if phone_number does not have the correct number of digits
    } while (phone_number.length() != PHONE_NUMBER_DIGITS);
    // Return phone number formatted for U.S. (***) ***-****
    return formatPhoneNumber(phone_number);
} // ---------------------------------------------------------------------------

// Get member email
string getMemberEmail() {
    // Email
    string email;
    // Get email
    cout << "  Enter email: ";
    getline(cin, email);
    // Return email
    return email;
} // ---------------------------------------------------------------------------

// Add member
void addMember(list<Member>& members) {
    // Member attributes
    string name;
    string phone_number;
    string email;
    // Confirmation
    string yes_no_answer;
    bool confirm_information;
    // Member information
    do {
        // Get name
        cout << "\n  Add Member,";
        name = getMemberName(members);
        // Get phone number
        phone_number = getMemberPhoneNumber();
        // Get email
        email = getMemberEmail();
        // Confirm member information
        cout << "\n"
            "  Name: " << name << '\n' <<
            "  Phone Number: " << phone_number << '\n' <<
            "  Email: " << email << '\n' <<
            "  Is the member's information correct? [Yes/No]: ";
        getline(cin, yes_no_answer);
        // Set confirm information true or false
        confirm_information = yesNo(yes_no_answer);
        // Inform user if confirm_information false
        if (!confirm_information) {
            cout << "\n  Okay, try again.\n";
        }
        // Continue while information not correct
    } while (!confirm_information);
    // Add new member
    if (members.empty()) {
        // Is first member
        members.push_back(Member(name, phone_number, email));
    } else {
        // Insert member alphabetically
        for (list<Member>::iterator it = members.begin();
            it != members.end(); it++) {
            // Member name has lower value insert in current position
            if (it->getName() > name) {
                // Inserts in position
                members.insert(it, Member(name, phone_number, email));
                // End function call
                return;
            }
        }
        // Member name is highest value add to end
        members.push_back(Member(name, phone_number, email));
    }
    // Clear console
    clearConsole();
} // ---------------------------------------------------------------------------

// Remove member
void removeMember(list<Member>& members) {
    // Check if list has members
    if (members.empty()) {
        // Inform user exit function
        cout << "\n  There are no current members.\n";
        return;
    }
    // Member removed
    bool member_removed = false;
    do {
        // Get member name
        string name;
        // Get name of member to remove
        cout << "\n  Remove Member,\n"
            "  Enter name of member to remove: ";
        getline(cin, name);
        // Validate formatted
        name = titleCase(name);
        // Search for member
        for (list<Member>::iterator it = members.begin();
            it != members.end(); it++) {
            // Found
            if (it->getName() == name) {
                // Remove member
                members.erase(it);
                // Inform user exit function
                cout << "\n  " << name << " has been removed.\n";
                return;
            }
        }
        // User not found
        if (!member_removed) {
            // Inform user
            cout << "\n  " << name << " was not found.\n";
        }
        // Continue while member not removed
    } while (!member_removed);
} // ---------------------------------------------------------------------------

// Search for member
const Member* findMemberToUpdate(const list<Member>& members, string name) {
    // Search for member by name
    for (list<Member>::const_iterator it = members.begin();
        it != members.end(); it++) {
        // Found member
        if (it->getName() == name) {
            // Return pointer to member
            return it.operator->();
        }
    }
    // Member not found return null pointer
    return nullptr;
} // ---------------------------------------------------------------------------

// Get member modify case
int getMemberModifyCase(const Member* modify_member) {
    // Modify case range
    const int MIN_CASE = 1;
    const int MAX_CASE = 4;
    // Modify case
    int modify_case;
    do {
        // Confirm member or choose to exit
        cout << "\n  Update Member,\n"
            "  Current member information:\n" <<
            "  " << modify_member->getName() << '\n' <<
            "  " << modify_member->getPhoneNumber() << '\n' <<
            "  " << modify_member->getEmail() << '\n' <<
            "\n"
            "  What would you like to change:\n"
            "  1) Name\n"
            "  2) Phone Number\n"
            "  3) Email\n"
            "  4) Nothing\n"
            "\n"
            "  Enter your selection: ";
        cin >> modify_case;
        // Check for user error
        if (cin.fail() || modify_case < MIN_CASE || modify_case > MAX_CASE) {
            // Clear input stream and inform user
            cin.clear();
            cin.ignore();
            cout << "\n  Invalid option, please make a valid selection.\n";
        } else {
            // Remove newline character from input stream
            cin.ignore();
        }
        // Continue while modify case is out of range
    } while (modify_case < MIN_CASE || modify_case > MAX_CASE);
    // Return modify case
    return modify_case;
} // ---------------------------------------------------------------------------

// Update member information
void updateMemberInformation(list<Member>& members) {
    // Pointer to member
    Member* modify_member = nullptr;
    // Member attributes
    string name;
    string phone_number;
    string email;
    // Attribute modify case
    int modify_case = 0;
    // Confirm member to modify
    string yes_no_answer;
    bool confirm_modify;
    // Find existing member
    do {
        // Get member name
        cout << "\n  Update Member,\n"
            "  Enter member's name: ";
        getline(cin, name);
        // Title format name
        name = titleCase(name);
        // Search for member
        modify_member = const_cast<Member*> (findMemberToUpdate(members, name));
        // Member found
        if (modify_member != nullptr) {
            // Get modify case
            modify_case = getMemberModifyCase(modify_member);
            // Set confirm_modify true
            confirm_modify = true;
            // Member not found
        } else {
            // User can choose to exit or try again
            cout << "\n  Member not found.\n"
                "  Would you like to try again? [Yes/No]: ";
            getline(cin, yes_no_answer);
            // Yes continues
            confirm_modify = !yesNo(yes_no_answer);
            if (confirm_modify == true) {
                // Exit function
                return;
            }
        }
        // Continue while not confirmed
    } while (!confirm_modify);

    // Modify case
    switch (modify_case) {
    case 1:
        // Get and confirm update
        do {
            // Get name update
            name = getMemberName(members);
            // Get confirmation
            cout << "\n  Update Name,\n"
                "  New name: " << name << '\n' <<
                "  Is name correct? [Yes/No]: ";
            getline(cin, yes_no_answer);
            // Set confirm_modify
            confirm_modify = yesNo(yes_no_answer);
            // While confirm_modify false
        } while (!confirm_modify);
        // Get additional attributes
        phone_number = modify_member->getPhoneNumber();
        email = modify_member->getEmail();
        // Find member in list
        for (list<Member>::iterator it = members.begin();
            it != members.end(); it++) {
            // Remove member in list
            if (it->getName() == modify_member->getName()) {
                members.erase(it);
                break;
            }
        }
        // Place new member to correct location in list
        for (list<Member>::iterator it = members.begin();
            it != members.end(); it++) {
            if (it->getName() > name) {
                members.insert(it, Member(name, phone_number, email));
                break;
            }
        }
        // Append list if new member name has highest value
        if (prev(members.end())->getName() < name) {
            members.push_back(Member(name, phone_number, email));
        }
        // Clear console
        clearConsole();
        break;
    case 2:
        // Get and confirm phone number update
        do {
            // Get phone number update
            phone_number = getMemberPhoneNumber();
            // Get confirmation
            cout << "\n  Update Phone Number,\n"
                "  New phone number: " << phone_number << '\n' <<
                "  Is phone number correct? [Yes/No]: ";
            getline(cin, yes_no_answer);
            // Set confirm_modify
            confirm_modify = yesNo(yes_no_answer);
            // While confirm_modify false
        } while (!confirm_modify);
        // Update phone number
        modify_member->setPhoneNumber(phone_number);
        // Clear console
        clearConsole();
        break;
    case 3:
        // Get email update
        do {
            email = getMemberEmail();
            // Get confirmation
            cout << "\n  Update Email,\n"
                "  New email: " << email << '\n' <<
                "  Is email correct? [Yes/No]: ";
            getline(cin, yes_no_answer);
            // Set confirm_modify
            confirm_modify = yesNo(yes_no_answer);
            // While confirm_modify false
        } while (!confirm_modify);
        // Update email
        modify_member->setEmail(email);
        // Clear console
        clearConsole();
        break;
    case 4:
        // Make no changes
        return;
    default:
        // Return to member menu
        return;
    }
} // ---------------------------------------------------------------------------

// Random member
void randomMember(const list<Member>& members) {
    // Vector of strings, member names
    vector<string> member_names;
    // Random member index
    int random_member_index;
    // Read member names into vector
    for (list<Member>::const_iterator it = members.begin();
        it != members.end(); it++) {
        member_names.push_back(it->getName());
    }
    // Yes no answer
    string yes_no_answer;
    // Begin
    string begin;
    // Welcome message
    cout << "\n"
        "   Welcome To Random Member\n"
        "  --------------------------\n"
        "  Press enter and a random book club member's name will be provided.\n"
        "  After a member has been chosen their name will not be eligible again\n"
        "  until the next time you choose Random Member.\n"
        "\n"
        "  Press enter to begin ->";
    getline(cin, begin);
    // Display random member
    do {
        // If all members have been chosen
        if (member_names.empty()) {
            // Clear console
            clearConsole();
            // Inform user and return to Member Menu
            cout << "\n  There are no more members to choose from. Returning"
                " to Member Menu.\n";
            return;
        } else {
            // Display member name
            random_member_index = randomIndex(int(member_names.size()));
            cout << "\n"
                "  Random Member: " << member_names[random_member_index] << "\n\n"
                "  Would you like to choose another member? [Yes/No]: ";
            getline(cin, yes_no_answer);
            // Remove member name
            member_names.erase(member_names.begin() + random_member_index);
        }
        // Continues while yes_no_answer is yes
    } while (yesNo(yes_no_answer));
    // Clear console
    clearConsole();
} // ---------------------------------------------------------------------------

// Displays book menu returns numeric choice
int bookMenu() {
    // Choice range
    const int MIN_CASE = 1;
    const int MAX_CASE = 6;
    // Choice
    int choice;
    // Perform actions until return to main menu
    do {
        cout << "\n"
            "  Book Menu:\n"
            "  1) List Books\n"
            "  2) Add Book\n"
            "  3) Remove Book\n"
            "  4) Update Book\n"
            "  5) Random Book\n"
            "  6) Return to Main Menu\n"
            "\n"
            "  Enter your selection: ";
        // Retrieve choice
        cin >> choice;
        // Check for user error
        if (cin.fail() || choice < MIN_CASE || choice > MAX_CASE) {
            // Clear input stream and inform user
            cin.clear();
            cin.ignore();
            cout << "\n  Invalid option, please make a valid selection.\n";
        } else {
            // Remove newline character from input stream
            cin.ignore();
        }
        // Continue while choice out of range
    } while (choice < MIN_CASE || choice > MAX_CASE);
    // Clear console
    clearConsole();
    // Return choice
    return choice;
} // ---------------------------------------------------------------------------

// Book functions
void bookFunctions(list<Book>& books) {
    // Run book functions
    const int MAIN_MENU = 6;
    // Option
    int option;
    do {
        option = bookMenu();
        // Execute option
        switch (option) {
        case 1:
            // List Books
            listBooks(books);
            break;
        case 2:
            // Add Book
            addBook(books);
            break;
        case 3:
            // Remove Book
            removeBook(books);
            break;
        case 4:
            // Update Book
            updateBookInformation(books);
            break;
        case 5:
            // Random Book
            randomBook(books);
            break;
        case MAIN_MENU:
            // Return to main menu
            return;
        default:
            // Return to main menu
            return;
        }
        // Continue while option not main menu
    } while (option != MAIN_MENU);
} // ---------------------------------------------------------------------------

// List books
void listBooks(const list<Book>& books) {
    // Book state
    string book_read_state;
    // If there are books list by title, author, state
    if (!books.empty()) {
        cout << "\n  Book List"
            "\n  ---------";
        for (list<Book>::const_iterator it = books.begin();
            it != books.end(); it++) {
            book_read_state = it->getReadState() ? "yes" : "no";
            cout << "\n" <<
                "  Title: " << it->getTitle() << '\n' <<
                "  Author: " << it->getAuthor() << '\n' <<
                "  Read: " << book_read_state << '\n';
        }
    } else {
        // Report there are no books
        cout << "\n  There are no books at this time.\n";
    }
} // ---------------------------------------------------------------------------

// Get book's title
string getBookTitle(const list<Book>& books) {
    // Book title
    string title;
    // Unique book title
    bool unique_title;
    do {
        // Set unique_title to true
        unique_title = true;
        cout << "\n  Enter book's title: ";
        getline(cin, title);
        // Format title
        title = titleCase(title);
        // Make sure book title is unique
        if (!books.empty()) {
            // Not empty list search for book title
            for (list<Book>::const_iterator it = books.begin();
                it != books.end(); it++) {
                // Book found
                if (it->getTitle() == title) {
                    cout << "\n  Book exists, new book name must be unique.\n";
                    unique_title = false;
                    break;
                }
            }
        }
        // Continue if book title is not unique
    } while (!unique_title);
    // Return unique book title
    return title;
} // ---------------------------------------------------------------------------

// Get author's name
string getAuthorName() {
    // Author's name
    string author_name;
    // Get author's name
    cout << "  Enter author's name: ";
    getline(cin, author_name);
    // Return author's name formatted
    return titleCase(author_name);
} // ---------------------------------------------------------------------------

// Get book's read state
bool getBookReadState() {
    // Yes or no answer
    string yes_no_answer;
    cout << "  Has this book been read? [Yes/No]: ";
    getline(cin, yes_no_answer);
    // Return read state, yes = true, no = false
    return yesNo(yes_no_answer);
} // ---------------------------------------------------------------------------

// Add book
void addBook(list<Book>& books) {
    // Book attributes
    string title;
    string author_name;
    bool read_state;
    string book_read_state;
    // Confirmation
    string yes_no_answer;
    bool confirm_information;
    // Book information
    do {
        // Get title
        cout << "\n  Add Book,";
        title = getBookTitle(books);
        // Get author's name
        author_name = getAuthorName();
        // Get book's read state
        read_state = getBookReadState();
        // Set book_read_state yes or no
        book_read_state = read_state ? "yes" : "no";
        // Confirm book information
        cout << "\n" <<
            "  Title: " << title << '\n' <<
            "  Author: " << author_name << '\n' <<
            "  Read: " << book_read_state << '\n' <<
            "  Is the book's information correct? [Yes/No]: ";
        getline(cin, yes_no_answer);
        // Set confirm information true or false
        confirm_information = yesNo(yes_no_answer);
        // Inform user if confirm_information false
        if (!confirm_information) {
            cout << "\n  Okay, try again.\n";
        }
        // Continue while information not correct
    } while (!confirm_information);
    // Add new book
    if (books.empty()) {
        // Is first book
        books.push_back(Book(title, author_name, read_state));
    } else {
        // Insert book alphabetically
        for (list<Book>::iterator it = books.begin();
            it != books.end(); it++) {
            // Book title has lower value insert in current position
            if (it->getTitle() > title) {
                // Inserts in position
                books.insert(it, Book(title, author_name, read_state));
                // End function call
                return;
            }
        }
        // Book title is highest value add to end
        books.push_back(Book(title, author_name, read_state));
    }
    // Clear console
    clearConsole();
} // ---------------------------------------------------------------------------

// Remove book
void removeBook(list<Book>& books) {
    // Check if list has books
    if (books.empty()) {
        // Inform user exit function
        cout << "\n  There are no current books.\n";
        return;
    }
    // Book removed
    bool book_removed = false;
    do {
        // Get book title
        string title;
        // Get name of book to remove
        cout << "\n  Remove Book,\n"
            "  Enter title of book to remove: ";
        getline(cin, title);
        // Validate formatted
        title = titleCase(title);
        // Search for book
        for (list<Book>::iterator it = books.begin();
            it != books.end(); it++) {
            // Found
            if (it->getTitle() == title) {
                // Remove book
                books.erase(it);
                // Inform user exit function
                cout << "\n  " << title << " has been removed.\n";
                return;
            }
        }
        // Book not found
        if (!book_removed) {
            // Inform user
            cout << "\n  " << title << " was not found.\n";
        }
        // Continue while book not removed
    } while (!book_removed);
} // ---------------------------------------------------------------------------

// Search for book
const Book* findBookToUpdate(const list<Book>& books, string title) {
    // Search for book by title
    for (list<Book>::const_iterator it = books.begin();
        it != books.end(); it++) {
        // Found book
        if (it->getTitle() == title) {
            // Return pointer to book
            return it.operator->();
        }
    }
    // Book not found return null pointer
    return nullptr;
} // ---------------------------------------------------------------------------

// Get book modify case
int getBookModifyCase(const Book* modify_book) {
    // Modify case range
    const int MIN_CASE = 1;
    const int MAX_CASE = 4;
    // Modify case
    int modify_case;
    // Book read state
    string book_read_state;
    bool read_state = modify_book->getReadState();
    book_read_state = read_state ? "yes" : "no";
    // Get case
    do {
        // Confirm book or choose to exit
        cout << "\n"
            "  Current book information:\n" <<
            "  Title: " << modify_book->getTitle() << '\n' <<
            "  Author: " << modify_book->getAuthor() << '\n' <<
            "  Read: " << book_read_state << '\n' <<
            "\n"
            "  What would you like to change:\n"
            "  1) Title\n"
            "  2) Author\n"
            "  3) Has Been Read\n"
            "  4) Nothing\n"
            "\n"
            "  Enter your selection: ";
        cin >> modify_case;
        // Check for user error
        if (cin.fail() || modify_case < MIN_CASE || modify_case > MAX_CASE) {
            // Clear input stream and inform user
            cin.clear();
            cin.ignore();
            cout << "\n  Invalid option, please make a valid selection.\n";
        } else {
            // Remove newline character from input stream
            cin.ignore();
        }
        // Continue while modify case is out of range
    } while (modify_case < MIN_CASE || modify_case > MAX_CASE);
    // Return modify case
    return modify_case;
} // ---------------------------------------------------------------------------

// Update book information
void updateBookInformation(list<Book>& books) {
    // Pointer to book
    Book* modify_book = nullptr;
    // Book attributes
    string title;
    string author;
    bool read_state;
    string book_read_state;
    // Attribute modify case
    int modify_case = 0;
    // Confirm book
    string yes_no_answer;
    bool confirm_modify;

    // Find existing book
    do {
        // Get book title
        cout << "\n  Update Book,\n"
            "  Enter book's title: ";
        getline(cin, title);
        // Title format title
        title = titleCase(title);
        // Search for book
        modify_book = const_cast<Book*> (findBookToUpdate(books, title));
        // Book found
        if (modify_book != nullptr) {
            // Get modify case
            modify_case = getBookModifyCase(modify_book);
            // Set confirm_modify true
            confirm_modify = true;
            // Book not found
        } else {
            // User can choose to exit or try again
            cout << "\n  Book not found.\n"
                "  Would you like to try again? [Yes/No]: ";
            getline(cin, yes_no_answer);
            // Yes continues
            confirm_modify = !yesNo(yes_no_answer);
            if (confirm_modify == true) {
                // Exit function
                return;
            }
        }
        // Continue while not confirmed
    } while (!confirm_modify);

    // Modify case
    switch (modify_case) {
    case 1:
        // Get and confirm update
        do {
            // Get title update
            cout << "\n  Update Title,";
            title = getBookTitle(books);
            // Get confirmation
            cout << "\n"
                "  New title: " << title << '\n' <<
                "  Is title correct? [Yes/No]: ";
            getline(cin, yes_no_answer);
            // Set confirm_modify
            confirm_modify = yesNo(yes_no_answer);
            // While confirm_modify false
        } while (!confirm_modify);
        // Get additional attributes
        author = modify_book->getAuthor();
        read_state = modify_book->getReadState();
        // Find book in list
        for (list<Book>::iterator it = books.begin();
            it != books.end(); it++) {
            // Remove book in list
            if (it->getTitle() == modify_book->getTitle()) {
                books.erase(it);
                break;
            }
        }
        // Place new book to correct location in list
        for (list<Book>::iterator it = books.begin();
            it != books.end(); it++) {
            if (it->getTitle() > title) {
                books.insert(it, Book(title, author, read_state));
                break;
            }
        }
        // Append list if new book title has highest value
        if (prev(books.end())->getTitle() < title) {
            books.push_back(Book(title, author, read_state));
        }
        // Clear console
        clearConsole();
        break;
    case 2:
        // Get and confirm author update
        do {
            // Get author update
            cout << "\n  Update Author,\n";
            author = getAuthorName();
            // Get confirmation
            cout << "\n"
                "  New Author: " << author << '\n' <<
                "  Is phone number correct? [Yes/No]: ";
            getline(cin, yes_no_answer);
            // Set confirm_modify
            confirm_modify = yesNo(yes_no_answer);
            // While confirm_modify false
        } while (!confirm_modify);
        // Update author
        modify_book->setAuthor(author);
        // Clear console
        clearConsole();
        break;
    case 3:
        // Get read state update
        do {
            cout << "\n  Update Read,\n";
            read_state = getBookReadState();
            // Update read status
            book_read_state = read_state ? "yes" : "no";
            // Get confirmation
            cout << "\n"
                "  New read status: " << book_read_state << '\n' <<
                "  Is this correct? [Yes/No]: ";
            getline(cin, yes_no_answer);
            // Set confirm_modify
            confirm_modify = yesNo(yes_no_answer);
            // While confirm_modify false
        } while (!confirm_modify);
        // Update read state
        modify_book->setRead(read_state);
        // Clear console
        clearConsole();
        break;
    case 4:
        // Make no changes
        return;
    default:
        // Return to book menu
        return;
    }
} // ---------------------------------------------------------------------------

// Random book
void randomBook(const list<Book>& books) {
    // Vector of strings, book titles
    vector<string> book_titles;
    // Random book index
    int random_book_index;
    // Read book names into vector
    for (list<Book>::const_iterator it = books.begin();
        it != books.end(); it++) {
        book_titles.push_back(it->getTitle());
    }
    // Yes no answer
    string yes_no_answer;
    // Begin
    string begin;
    // Welcome message
    cout << "\n"
        "   Welcome To Random Book\n"
        "  --------------------------\n"
        "  Press enter and a random book title will be provided.\n"
        "  After a title has been chosen it will not be eligible again\n"
        "  until the next time you choose Random Book.\n"
        "\n"
        "  Press enter to begin ->";
    getline(cin, begin);
    // Display random book
    do {
        // If all books have been chosen
        if (book_titles.empty()) {
            // Clear console
            clearConsole();
            // Inform user and return to Book Menu
            cout << "\n  There are no more titles to choose from. Returning"
                " to Book Menu.\n";
            return;
        } else {
            // Display book title
            random_book_index = randomIndex(int(book_titles.size()));
            cout << "\n"
                "  Random Title: " << book_titles[random_book_index] << "\n\n"
                "  Would you like to choose another title? [Yes/No]: ";
            getline(cin, yes_no_answer);
            // Remove book title
            book_titles.erase(book_titles.begin() + random_book_index);
        }
        // Continues while yes_no_answer is yes
    } while (yesNo(yes_no_answer));
    // Clear console
    clearConsole();
} // ---------------------------------------------------------------------------

// Returns a random index of a vector
int randomIndex(int vector_size) {
    // Align index positions
    vector_size -= 1;
    // True random generator
    random_device random;
    // A Mersenne Twister pseudo-random generator gets seed from random_device
    mt19937 generator(random());
    // Range of values from zero to max index
    uniform_int_distribution<int> distribution(0, vector_size);
    // Return random index within range of vector
    return distribution(generator);
} // ---------------------------------------------------------------------------

// Title case
string titleCase(string title) {
    // After a space uppercase else lowercase
    for (int i = 1; i < title.length(); i++)
        title[i] = (title[i - 1] == ' ') ? toupper(title[i]) :
        tolower(title[i]);
    // First character uppercase
    title[0] = toupper(title[0]);
    // Return formatted title
    return title;
} // ---------------------------------------------------------------------------

// Format U.S. phone number (***) ***-****
string formatPhoneNumber(string phone_number) {
    // Formatted U.S. phone number
    string formattedNumber;
    // First character
    formattedNumber = "(";
    // Three digit area code
    for (int i = 0; i < 3; i++) {
        formattedNumber += phone_number[i];
    }
    // Add closing parenthesis and space
    formattedNumber += ") ";
    // First three numbers
    for (int i = 3; i < 6; i++) {
        formattedNumber += phone_number[i];
    }
    // Add dash
    formattedNumber += "-";
    // Last four numbers
    for (int i = 6; i < 10; i++) {
        formattedNumber += phone_number[i];
    }
    // Return formatted phone number
    return formattedNumber;
} // ---------------------------------------------------------------------------

// Yes No statement, yes returns true
bool yesNo(string answer) {
    // Yes or No
    bool valid;
    // Character at first index equals y return true else false
    valid = tolower(answer[0]) == 'y' ? true : false;
    // Return valid
    return valid;
} // ---------------------------------------------------------------------------

// Clear console
void clearConsole() {
    // Choose command for system
    #ifdef _WIN32
    // Windows clear command
        system("cls");
    #elif _WIN64
    // Windows clear command
        system("cls");
    #else
    // Clear command for most Unix based systems
        system("clear");
    #endif
} // ---------------------------------------------------------------------------
