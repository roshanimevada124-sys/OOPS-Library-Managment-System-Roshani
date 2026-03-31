#include <iostream>
#include <vector>
#include <fstream>   // 🔥 file handling
#include <limits>
using namespace std;

// 🔹 Product Class (Encapsulation)
class Product {
private:
    int id;
    string name;
    float price;

public:
    Product() {} // default constructor (needed for file read)

    Product(int i, string n, float p) {
        id = i;
        name = n;
        price = p;
    }

    int getId() { return id; }
    string getName() { return name; }
    float getPrice() { return price; }

    void display() {
        cout << id << "\t" << name << "\t" << price << endl;
    }

    // 🔥 Save to file
    string toFile() {
        return to_string(id) + "," + name + "," + to_string(price);
    }

    // 🔥 Load from file
    void fromFile(string line) {
        int pos1 = line.find(',');
        int pos2 = line.find(',', pos1 + 1);

        id = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        price = stof(line.substr(pos2 + 1));
    }
};

// 🔹 Cart Item
class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product p, int q) : product(p), quantity(q) {}

    float getTotal() {
        return product.getPrice() * quantity;
    }

    void display() {
        cout << product.getName() << "\t"
             << product.getPrice() << "\t"
             << quantity << "\t"
             << getTotal() << endl;
    }
};

// 🔹 Abstract User
class User {
public:
    virtual void menu() = 0;
};

// 🔹 Shopping System
class ShoppingSystem {
private:
    vector<Product> products;
    vector<CartItem> cart;

public:
    // 🔥 Load products from file
    void loadProducts() {
        ifstream file("products.txt");
        string line;

        while (getline(file, line)) {
            Product p;
            p.fromFile(line);
            products.push_back(p);
        }

        file.close();
    }

    // 🔥 Save products to file
    void saveProducts() {
        ofstream file("products.txt");

        for (auto &p : products) {
            file << p.toFile() << endl;
        }

        file.close();
    }

    void addProduct() {
        int id;
        string name;
        float price;

        cout << "Enter Product ID: ";
        cin >> id;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Product Name: ";
        getline(cin, name);

        cout << "Enter Price: ";
        cin >> price;

        // check duplicate
        for (auto &p : products) {
            if (p.getId() == id) {
                cout << "Product ID already exists!\n";
                return;
            }
        }

        products.push_back(Product(id, name, price));
        saveProducts(); // 🔥 auto save

        cout << "Product Added & Saved!\n";
    }

    void displayProducts() {
        if (products.empty()) {
            cout << "No products available!\n";
            return;
        }

        cout << "\nID\tName\tPrice\n";
        for (auto &p : products) {
            p.display();
        }
    }

    void addToCart() {
        int id, qty;

        cout << "Enter Product ID: ";
        cin >> id;

        for (auto &p : products) {
            if (p.getId() == id) {
                cout << "Enter Quantity: ";
                cin >> qty;

                cart.push_back(CartItem(p, qty));
                cout << "Added to Cart!\n";
                return;
            }
        }
        cout << "Product Not Found!\n";
    }

    void viewCart() {
        if (cart.empty()) {
            cout << "Cart is empty!\n";
            return;
        }

        cout << "\nName\tPrice\tQty\tTotal\n";
        for (auto &c : cart) {
            c.display();
        }
    }

    void generateBill() {
        if (cart.empty()) {
            cout << "Cart is empty!\n";
            return;
        }

        float total = 0;
        cout << "\n----- BILL -----\n";

        for (auto &c : cart) {
            c.display();
            total += c.getTotal();
        }

        cout << "-----------------\n";
        cout << "Total Amount: " << total << endl;
    }
};

// 🔹 Admin
class Admin : public User {
private:
    ShoppingSystem &system;

public:
    Admin(ShoppingSystem &s) : system(s) {}

    void menu() {
        int choice;
        while (true) {
            cout << "\n--- Admin Menu ---\n";
            cout << "1. Add Product\n2. View Products\n3. Back\nChoice: ";
            cin >> choice;

            switch (choice) {
            case 1: system.addProduct(); break;
            case 2: system.displayProducts(); break;
            case 3: return;
            default: cout << "Invalid!\n";
            }
        }
    }
};

// 🔹 Customer
class Customer : public User {
private:
    ShoppingSystem &system;

public:
    Customer(ShoppingSystem &s) : system(s) {}

    void menu() {
        int choice;
        while (true) {
            cout << "\n--- Customer Menu ---\n";
            cout << "1. View Products\n2. Add to Cart\n3. View Cart\n4. Generate Bill\n5. Back\nChoice: ";
            cin >> choice;

            switch (choice) {
            case 1: system.displayProducts(); break;
            case 2: system.addToCart(); break;
            case 3: system.viewCart(); break;
            case 4: system.generateBill(); break;
            case 5: return;
            default: cout << "Invalid!\n";
            }
        }
    }
};

// 🔹 Main
int main() {
    ShoppingSystem system;

    system.loadProducts(); // 🔥 load existing data

    Admin admin(system);
    Customer customer(system);

    int choice;

    while (true) {
        cout << "\n===== ONLINE SHOPPING SYSTEM =====\n";
        cout << "1. Admin\n2. Customer\n3. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: admin.menu(); break;
        case 2: customer.menu(); break;
        case 3: cout << "Thank you!\n"; return 0;
        default: cout << "Invalid Choice!\n";
        }
    }
}