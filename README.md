# 📞 Telephone Directory System (C++)

A simple console-based telephone directory system implemented in C++.

It allows users to:
- Add new contacts
- Display all saved contacts
- Search contacts by name
- Modify existing contact details
- Delete contacts
- Secure access via password login

All contact information is stored in a binary file to preserve data between sessions.

---

## 🛠 Features

- ✅ Object-Oriented Programming using C++ classes
- ✅ File handling using binary files (`fstream`)
- ✅ Password-protected login system
- ✅ Menu-driven console interface
- ✅ Modular functions for each operation

---

## 📂 Project Structure

TelephoneDirectory/
├── main.cpp // Core C++ program
├── README.md // Project overview (this file)
├── .gitignore // Ignored files like .exe, .dat

### ▶️ Compile & Run
If you have `g++` installed:

```bash
g++ main.cpp -o directory
./directory

🔐 Default Password
admin123
You can change it in main.cpp where ADMIN_PASSWORD is defined.

