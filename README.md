# College Cafe Management System ☕🍔

## 📌 Project Description
The **College Cafe Management System** is a console-based C++ application designed to simulate the basic operations of a small college cafeteria. The system allows users to manage food items, take customer orders, calculate bills, and track daily sales in a structured and efficient way.

This project demonstrates fundamental C++ programming concepts applied to a real-world scenario.

---

## 🎯 Purpose of the Project
The main goal of this project is to:
- Practice modular programming using functions
- Apply input validation techniques
- Use arrays and constants effectively
- Simulate a real-life management system using C++

---

## 🧩 System Overview 
The system is divided into two main modes:

### 1️⃣ Cashier Mode
Cashier Mode is used to handle customer orders. The cashier can:
- View the menu
- Add items and quantities to an order
- Preview the current bill
- Finalize checkout and print a receipt
- Clear or cancel an order for the next customer

---

### 2️⃣ Admin Mode
Admin Mode is password-protected to prevent unauthorized access. The administrator can:
- View the menu
- Change prices of existing items
- Add new food items (up to a fixed limit)
- View daily sales reports (subtotal, discount, tax, total revenue)

---

## ⚙️ Key Features
- Input validation to prevent invalid user input
- Formatted menu and receipt display
- Automatic calculation of:
  - Subtotal
  - Discount
  - Tax
  - Total amount
- Password-protected admin panel
- Daily sales tracking for management purposes

---

## 🛠️ Technologies Used
- **Language:** C++
- **Libraries:** iostream, iomanip, string, limits
- **Platform:** Console application

---

## ▶️ How to Run the Program
### 1️⃣ Clone the Repository

```bash
git clone https://github.com/josi1219/cpp-assignment.git
```
### 2️⃣ Then move into the project directory:
```bash
cd cpp-assignment
```
### 3️⃣ Compile the Program
   ```bash
   g++ cafe.cpp -o cafe
   ```
### 4️⃣ Run the executable:
   ```bash
   ./cafe
   ```
