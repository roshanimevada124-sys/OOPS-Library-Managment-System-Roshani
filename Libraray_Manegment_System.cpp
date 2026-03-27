#include <iostream>
#include <vector>
using namespace std;

// 📘 Base Class (Abstraction)
class Book {
protected:
    int id;
    string name;
    string author;

public:
    Book() {}

    Book(int id, string name, string author) {
        this->id = id;
        this->name = name;
        this->author = author;
    }

    // Encapsulation (getters)
    int getId() { return id; }
    string getName() { return name; }
    string getAuthor() { return author; }

    // Virtual function (Polymorphism)
    virtual void display() {
        cout << "ID: " << id << " | Name: " << name << " | Author: " << author << endl;
    }
};

// 📗 Derived Class (Inheritance)
class IssuedBook : public Book {
    string issuedTo;

public:
    IssuedBook(int id, string name, string author, string user)
        : Book(id, name, author) {
        issuedTo = user;
    }

    void display() override {
        cout << "ID: " << id << " | Name: " << name
             << " | Author: " << author
             << " | Issued To: " << issuedTo << endl;
    }
};

// 📚 Library Class
class Library {
    vector<Book> books;
    vector<IssuedBook> issuedBooks;

public:
    // ➕ Add Book
    void addBook() {
        int id;
        string name, author;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Name: ";
        getline(cin, name);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, name, author));
        cout << "Book added successfully!\n";
    }

    // 👀 View Books
    void viewBooks() {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }

        for (auto &b : books) {
            b.display();
        }
    }

    // 🔍 Search Book
    void searchBook() {
        int id;
        cout << "Enter Book ID to search: ";
        cin >> id;

        for (auto &b : books) {
            if (b.getId() == id) {
                cout << "Book Found:\n";
                b.display();
                return;
            }
        }
        cout << "Book not found!\n";
    }

    // ❌ Remove Book
    void removeBook() {
        int id;
        cout << "Enter Book ID to delete: ";
        cin >> id;

        for (int i = 0; i < books.size(); i++) {
            if (books[i].getId() == id) {
                books.erase(books.begin() + i);
                cout << "Book deleted!\n";
                return;
            }
        }
        cout << "Book not found!\n";
    }

    // 🔄 Issue Book
    void issueBook() {
        int id;
        string user;

        cout << "Enter Book ID to issue: ";
        cin >> id;
        cin.ignore();

        cout << "Enter User Name: ";
        getline(cin, user);

        for (int i = 0; i < books.size(); i++) {
            if (books[i].getId() == id) {
                issuedBooks.push_back(
                    IssuedBook(books[i].getId(),
                               books[i].getName(),
                               books[i].getAuthor(),
                               user)
                );

                books.erase(books.begin() + i);
                cout << "Book issued successfully!\n";
                return;
            }
        }
        cout << "Book not available!\n";
    }

    // 🔁 Return Book
    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (int i = 0; i < issuedBooks.size(); i++) {
            if (issuedBooks[i].getId() == id) {
                books.push_back(Book(
                    issuedBooks[i].getId(),
                    issuedBooks[i].getName(),
                    issuedBooks[i].getAuthor()
                ));

                issuedBooks.erase(issuedBooks.begin() + i);
                cout << "Book returned successfully!\n";
                return;
            }
        }
        cout << "Invalid ID!\n";
    }

    // 📖 View Issued Books
    void viewIssuedBooks() {
        if (issuedBooks.empty()) {
            cout << "No issued books.\n";
            return;
        }

        for (auto &b : issuedBooks) {
            b.display();
        }
    }
};

// 🚀 Main Function
int main() {
    Library lib;
    int choice;

    while (true) {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Remove Book\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. View Issued Books\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.viewBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.removeBook(); break;
            case 5: lib.issueBook(); break;
            case 6: lib.returnBook(); break;5
            
            case 7: lib.viewIssuedBooks(); break;
            case 8: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}