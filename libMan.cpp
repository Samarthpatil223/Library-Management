#include<iostream>
#include<string>
#include<unordered_map>
#include<list>
using namespace std;

// Book class
class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book(int id,string title,string author):id(id),title(title),author(author),isIssued(false){}
};

// Member class
class Member {
public:
    int memberId;
    string name;

    Member(int id,string name):memberId(id),name(name){}
};

// Transaction class
class Transaction {
public:
    int bookId;
    int memberId;
    string issueDate;
    string returnDate;

    Transaction(int bookId, int memberId, string issueDate, string returnDate = "")
        : bookId(bookId), memberId(memberId), issueDate(issueDate), returnDate(returnDate) {}
};

// Library class to manage the system
class Library {
private:
    unordered_map<int, Book*> books; // Hash map for book management
    unordered_map<int, Member*> members;
    list<Transaction> transactions;  // Linked list to store transactions

public:
    // Add a new book to the library
    void addBook(int id, string title, string author) {
        books[id] = new Book(id, title, author);
        cout << "Book added: " << title << endl;
    }

    // Add a new member to the library
    void addMember(int id, string name) {
        members[id] = new Member(id, name);
        cout << "Member added: " << name << endl;
    }

    // Issue a book to a member
    void issueBook(int bookId, int memberId, string issueDate) {
        if (books.find(bookId) != books.end() && members.find(memberId) != members.end()) {
            if (!books[bookId]->isIssued) {
                books[bookId]->isIssued = true;
                transactions.push_back(Transaction(bookId, memberId, issueDate));
                cout << "Book issued: " << books[bookId]->title << " to member " << members[memberId]->name << endl;
            } else {
                cout << "Book is already issued." << endl;
            }
        } else {
            cout << "Invalid book or member ID." << endl;
        }
    }

    // Return a book to the library
    void returnBook(int bookId, int memberId, string returnDate) {
        if (books.find(bookId) != books.end() && books[bookId]->isIssued) {
            books[bookId]->isIssued = false;

            for (auto& transaction : transactions) {
                if (transaction.bookId == bookId && transaction.memberId == memberId) {
                    transaction.returnDate = returnDate;
                    cout << "Book returned: " << books[bookId]->title << " by member " << members[memberId]->name << endl;
                    return;
                }
            }
        } else {
            cout << "Invalid return request." << endl;
        }
    }

    // Search for a book by ID (using hash map for fast lookup)
    void searchBookById(int id) {
        if (books.find(id) != books.end()) {
            Book* book = books[id];
            cout << "Book found: " << book->title << " by " << book->author << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    // Display all books in the library
    void displayBooks() {
        cout << "Library Books:" << endl;
        for (const auto& pair : books) {
            cout << "ID: " << pair.second->id << ", Title: " << pair.second->title 
                 << ", Author: " << pair.second->author << ", Issued: " << (pair.second->isIssued ? "Yes" : "No") << endl;
        }
    }
};

int main() {
    Library library;

    library.addBook(1, "The Great Gatsby", "F. Scott Fitzgerald");
    library.addBook(2, "1984", "George Orwell");
    library.addBook(3, "To Kill a Mockingbird", "Harper Lee");

    library.addMember(101, "Alice");
    library.addMember(102, "Bob");

    library.issueBook(1, 101, "2024-09-19");
    library.returnBook(1, 101, "2024-09-25");

    library.searchBookById(2);

    library.displayBooks();

    return 0;
}
