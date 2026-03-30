#include <iostream>
#include <vector>
using namespace std;

// 🎓 Base Class (Abstraction)
class Student {
protected:
    int id;
    string name;
    int age;

public:
    Student() {}

    Student(int id, string name, int age) {
        this->id = id;
        this->name = name;
        this->age = age;
    }

    // Encapsulation (getters)
    int getId() { return id; }
    string getName() { return name; }
    int getAge() { return age; }

    // Polymorphism
    virtual void display() {
        cout << "ID: " << id << " | Name: " << name << " | Age: " << age << endl;
    }
};

// 📘 Derived Class (Inheritance)
class ResultStudent : public Student {
    float marks;

public:
    ResultStudent(int id, string name, int age, float marks)
        : Student(id, name, age) {
        this->marks = marks;
    }

    void display() override {
        cout << "ID: " << id << " | Name: " << name
             << " | Age: " << age
             << " | Marks: " << marks << endl;
    }
};

// 🏫 Student Management Class
class StudentManager {
    vector<Student> students;
    vector<ResultStudent> results;

public:
    // ➕ Add Student
    void addStudent() {
        int id, age;
        string name;

        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        students.push_back(Student(id, name, age));
        cout << "Student added successfully!\n";
    }

    // 👀 View Students
    void viewStudents() {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }

        for (auto &s : students) {
            s.display();
        }
    }

    // 🔍 Search Student
    void searchStudent() {
        int id;
        cout << "Enter Student ID to search: ";
        cin >> id;

        for (auto &s : students) {
            if (s.getId() == id) {
                cout << "Student Found:\n";
                s.display();
                return;
            }
        }
        cout << "Student not found!\n";
    }

    // ❌ Remove Student
    void removeStudent() {
        int id;
        cout << "Enter Student ID to delete: ";
        cin >> id;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                students.erase(students.begin() + i);
                cout << "Student removed!\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    // 📝 Add Result
    void addResult() {
        int id, age;
        string name;
        float marks;

        cout << "Enter Student ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Marks: ";
        cin >> marks;

        results.push_back(ResultStudent(id, name, age, marks));
        cout << "Result added successfully!\n";
    }

    // 📊 View Results
    void viewResults() {
        if (results.empty()) {
            cout << "No results available.\n";
            return;
        }

        for (auto &r : results) {
            r.display();
        }
    }
};

// 🚀 Main Function
int main() {
    StudentManager sm;
    int choice;

    while (true) {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Remove Student\n";
        cout << "5. Add Result\n";
        cout << "6. View Results\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sm.addStudent(); break;
            case 2: sm.viewStudents(); break;
            case 3: sm.searchStudent(); break;
            case 4: sm.removeStudent(); break;
            case 5: sm.addResult(); break;
            case 6: sm.viewResults(); break;
            case 7: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}