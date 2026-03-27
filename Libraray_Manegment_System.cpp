// #include <iostream>
// using namespace std;

// class Library {
//     string books[100];
//     int count = 0;

// public:
//     void addBook() {
//         if (count < 100) {
//             cout << "Enter book name: ";
//             cin.ignore(); // This will only take first word
//             getline(cin, books[count]); // This will take whole sentance with space
//             count++;
//             cout << "Book added successfully!\n";
//         } else {
//             cout << "Library is full!\n";
//         }
//     }

//     void viewBooks() {
//         if (count == 0) {
//             cout << "No books available.\n";
//         } else {
//             cout << "\nList of Books:\n";
//             for (int i = 0; i < count; i++) {
//                 cout << i + 1 << ". " << books[i] << endl;
//             }
//         }
//     }

//     void removeBook() {
//         int index;
//         viewBooks();
//         if (count == 0) return;

//         cout << "Enter book number to remove: ";
//         cin >> index;

//         if (index > 0 && index <= count) {
//             for (int i = index - 1; i < count - 1; i++) {
//                 books[i] = books[i + 1];
//             }
//             count--;
//             cout << "Book removed successfully!\n";
//         } else {
//             cout << "Invalid choice!\n";
//         }
//     }
// };

// int main() {
//     Library lib;
//     int choice;

//     while (true) {
//         cout << "\n===== Library Management System =====\n";
//         cout << "1. Add Book\n";
//         cout << "2. View Books\n";
//         cout << "3. Remove Book\n";
//         cout << "4. Exit\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch (choice) {
//             case 1: lib.addBook(); break;
//             case 2: lib.viewBooks(); break;
//             case 3: lib.removeBook(); break;
//             case 4: return 0;
//             default: cout << "Invalid choice!\n";
//         }
//     }
// }

