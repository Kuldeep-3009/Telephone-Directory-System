#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

class Contact {
public:
    char name[30];
    char address[50];
    unsigned long long phone;

    void get() {
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 30);
        cout << "Enter Address: ";
        cin.getline(address, 50);
        cout << "Enter Phone Number: ";
        cin >> phone;
    }

    void show() const {
        cout << "\nName    : " << name;
        cout << "\nAddress : " << address;
        cout << "\nPhone   : " << phone << "\n";
    }
};

// 🔐 Password protection function
bool login() {
    const string ADMIN_PASSWORD = "admin123"; // Change this as needed
    string input;
    int attempts = 3;

    while (attempts--) {
        cout << "\nEnter password to access Telephone Directory: ";
        cin >> input;

        if (input == ADMIN_PASSWORD) {
            cout << "Access granted.\n";
            return true;
        } else {
            cout << "Incorrect password. Attempts left: " << attempts << "\n";
        }
    }

    cout << "Too many failed attempts. Exiting program.\n";
    return false;
}

void addContact() {
    Contact c;
    fstream file("contacts.dat", ios::binary | ios::app);
    cout << "\n--- Add Contact ---\n";
    c.get();
    file.write(reinterpret_cast<char*>(&c), sizeof(c));
    file.close();
    cout << "\nContact added successfully!\n";
}

void showAllContacts() {
    Contact c;
    ifstream file("contacts.dat", ios::binary);
    cout << "\n--- All Contacts ---\n";
    while (file.read(reinterpret_cast<char*>(&c), sizeof(c))) {
        c.show();
        cout << "-------------------------\n";
    }
    file.close();
}

void searchContact() {
    char searchName[30];
    Contact c;
    bool found = false;
    ifstream file("contacts.dat", ios::binary);
    cout << "\nEnter Name to Search: ";
    cin.ignore();
    cin.getline(searchName, 30);
    while (file.read(reinterpret_cast<char*>(&c), sizeof(c))) {
        if (strcmpi(c.name, searchName) == 0) {
            cout << "\nContact Found:\n";
            c.show();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\nContact not found.\n";
    }
    file.close();
}

void modifyContact() {
    unsigned long long ph;
    Contact c;
    bool found = false;
    fstream file("contacts.dat", ios::in | ios::out | ios::binary);
    cout << "\nEnter Phone Number to Modify: ";
    cin >> ph;
    while (file.read(reinterpret_cast<char*>(&c), sizeof(c))) {
        if (c.phone == ph) {
            cout << "\nExisting Contact:\n";
            c.show();
            cout << "\nEnter New Details:\n";
            c.get();
            file.seekp(-static_cast<int>(sizeof(c)), ios::cur);
            file.write(reinterpret_cast<char*>(&c), sizeof(c));
            cout << "\nContact modified successfully!\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\nContact not found.\n";
    }
    file.close();
}

void deleteContact() {
    char delName[30];
    Contact c;
    bool found = false;
    ifstream fin("contacts.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);
    cout << "\nEnter Name to Delete: ";
    cin.ignore();
    cin.getline(delName, 30);
    while (fin.read(reinterpret_cast<char*>(&c), sizeof(c))) {
        if (strcmpi(c.name, delName) != 0) {
            fout.write(reinterpret_cast<char*>(&c), sizeof(c));
        } else {
            found = true;
        }
    }
    fin.close();
    fout.close();
    remove("contacts.dat");
    rename("temp.dat", "contacts.dat");

    if (found) {
        cout << "\nContact deleted successfully!\n";
    } else {
        cout << "\nContact not found.\n";
    }
}

int main() {
    if (!login()) return 0;

    int choice;
    do {
        cout << "\n\n==== Telephone Directory ====\n";
        cout << "1. Add Contact\n";
        cout << "2. Show All Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Modify Contact\n";
        cout << "5. Delete Contact\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addContact();
            break;
        case 2:
            showAllContacts();
            break;
        case 3:
            searchContact();
            break;
        case 4:
            modifyContact();
            break;
        case 5:
            deleteContact();
            break;
        case 6:
            cout << "\nExiting the program.\n";
            break;
        default:
            cout << "\nInvalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
