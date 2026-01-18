#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

// CONSTANTS 
const int MAX_ITEMS = 10;
const double TAX_RATE = 0.15;
const string ADMIN_PASSWORD = "1111";

// DAILY SALES 
double dailySubtotal = 0.0;
double dailyDiscount = 0.0;
double dailyTax = 0.0;
double dailyTotal = 0.0;

// PROTOTYPES
void clearInput();
int readInt(const string &prompt);
int readIntInRange(const string &prompt, int minVal, int maxVal);
double readDoubleGreaterThan(const string &prompt, double minVal);

void printHeader(const string &title);
void printDivider();

void displayMenu(const string food[], const double price[], int itemCount);
void takeOrder(int qty[], const string food[], int itemCount);
void clearOrder(int qty[], int itemCount);

double calculateSubtotal(const int qty[], const double price[], int itemCount);
double calculateDiscount(double subtotal);
void printBill(const string food[], const int qty[], const double price[], int itemCount, bool finalize);

void adminPanel(string food[], double price[], int &itemCount);
void cashierPanel(string food[], double price[], int itemCount);

// INPUT HELPERS
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail()) {
            clearInput();
            return value;
        }
        clearInput();
        cout << "Invalid input. Enter a number.\n";
    }
}

int readIntInRange(const string &prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        value = readInt(prompt);
        if (value >= minVal && value <= maxVal)
            return value;
        cout << "Out of range. Try again.\n";
    }
}

double readDoubleGreaterThan(const string &prompt, double minVal) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && value > minVal) {
            clearInput();
            return value;
        }
        clearInput();
        cout << "Invalid amount. Must be greater than " << minVal << ".\n";
    }
}

// ---------------- UI ----------------
void printHeader(const string &title) {
    cout << "\n====================================\n";
    cout << "  " << title << "\n";
    cout << "====================================\n";
}

void printDivider() {
    cout << "------------------------------------\n";
}

// CORE LOGIC
void displayMenu(const string food[], const double price[], int itemCount) {
    printHeader("MENU");
    cout << left << setw(5) << "No"
         << setw(15) << "Item"
         << right << setw(10) << "Price\n";
    printDivider();

    cout << fixed << setprecision(2);
    for (int i = 0; i < itemCount; i++) {
        cout << left << setw(5) << (i + 1)
             << setw(15) << food[i]
             << right << setw(10) << price[i] << "\n";
    }
}

void takeOrder(int qty[], const string food[], int itemCount) {
    cout << "\nEnter item number (0 to stop)\n";
    while (true) {
        int item = readIntInRange("Item: ", 0, itemCount);
        if (item == 0) break;

        int amount = readIntInRange("Quantity: ", 1, 100);
        qty[item - 1] += amount;

        cout << "Added " << amount << " x " << food[item - 1] << "\n";
    }
}

void clearOrder(int qty[], int itemCount) {
    for (int i = 0; i < itemCount; i++)
        qty[i] = 0;
}

double calculateSubtotal(const int qty[], const double price[], int itemCount) {
    double sum = 0.0;
    for (int i = 0; i < itemCount; i++)
        sum += qty[i] * price[i];
    return sum;
}

double calculateDiscount(double subtotal) {
    if (subtotal >= 1000.0)
        return subtotal * 0.10;
    return 0.0;
}

// RECEIPT 
void printBill(const string food[], const int qty[], const double price[], int itemCount, bool finalize) {
    double subtotal = calculateSubtotal(qty, price, itemCount);
    if (subtotal == 0.0) {
        cout << "No items ordered.\n";
        return;
    }

    double discount = calculateDiscount(subtotal);
    double tax = (subtotal - discount) * TAX_RATE;
    double total = subtotal - discount + tax;

    // Only add to daily totals if it's a finalized checkout
    if (finalize) {
        dailySubtotal += subtotal;
        dailyDiscount += discount;
        dailyTax += tax;
        dailyTotal += total;
    }

    printHeader("RECEIPT");
    cout << left << setw(15) << "Item"
         << right << setw(6) << "Qty"
         << setw(10) << "Price"
         << setw(12) << "Total\n";
    printDivider();

    cout << fixed << setprecision(2);
    for (int i = 0; i < itemCount; i++) {
        if (qty[i] > 0) {
            cout << left << setw(15) << food[i]
                 << right << setw(6) << qty[i]
                 << setw(10) << price[i]
                 << setw(12) << qty[i] * price[i] << "\n";
        }
    }

    printDivider();
    cout << right << setw(20) << "Subtotal: " << setw(10) << subtotal << "\n";
    cout << right << setw(20) << "Discount: " << setw(10) << discount << "\n";
    cout << right << setw(20) << "Tax: " << setw(10) << tax << "\n";
    printDivider();
    cout << right << setw(20) << "Total: " << setw(10) << total << "\n";
}

// ADMIN
void adminPanel(string food[], double price[], int &itemCount) {
    string pass;
    cout << "Enter admin password: ";
    getline(cin, pass);

    if (pass != ADMIN_PASSWORD) {
        cout << "Access denied.\n";
        return;
    }

    int choice;
    do {
        printHeader("ADMIN PANEL");
        cout << "1. View Menu\n";
        cout << "2. Change Price\n";
        cout << "3. Add New Item\n";
        cout << "4. View Daily Sales Report\n";
        cout << "5. Back\n";

        choice = readIntInRange("Choose: ", 1, 5);

        if (choice == 1) {
            displayMenu(food, price, itemCount);
        }
        else if (choice == 2) {
            displayMenu(food, price, itemCount);
            int item = readIntInRange("Item number: ", 1, itemCount);
            price[item - 1] = readDoubleGreaterThan("New price: ", 0.0);
            cout << "Price updated.\n";
        }
        else if (choice == 3) {
            if (itemCount >= MAX_ITEMS) {
                cout << "Menu full.\n";
            } else {
                do {
                    cout << "Item name: ";
                    getline(cin, food[itemCount]);
                } while (food[itemCount].empty());

                price[itemCount] = readDoubleGreaterThan("Price: ", 0.0);
                itemCount++;
                cout << "Item added.\n";
            }
        }
        else if (choice == 4) {
            printHeader("DAILY SALES REPORT");
            cout << fixed << setprecision(2);
            cout << "Subtotal: " << dailySubtotal << "\n";
            cout << "Discount: " << dailyDiscount << "\n";
            cout << "Tax: " << dailyTax << "\n";
            printDivider();
            cout << "Total Revenue (after tax & discount): " << dailyTotal << "\n";
        }

    } while (choice != 5);
}

// CASHIER 
void cashierPanel(string food[], double price[], int itemCount) {
    int qty[MAX_ITEMS] = {0};
    int choice;

    do {
        printHeader("CASHIER PANEL");
        cout << "1. Show Menu\n";
        cout << "2. Add Items\n";
        cout << "3. View Current Bill\n";
        cout << "4. Checkout & Clear Order\n";
        cout << "5. Cancel / Exit\n";

        choice = readIntInRange("Choose: ", 1, 5);

        if (choice == 1) {
            displayMenu(food, price, itemCount);
        }
        else if (choice == 2) {
            displayMenu(food, price, itemCount);
            takeOrder(qty, food, itemCount);
        }
        else if (choice == 3) {
            printBill(food, qty, price, itemCount, false);  // preview, no daily totals
        }
        else if (choice == 4) {
            printBill(food, qty, price, itemCount, true);   // finalize checkout
            clearOrder(qty, itemCount);
            cout << "Order cleared. Ready for next customer.\n";
        }
        else if (choice == 5) {
            clearOrder(qty, itemCount);                     // cancel order
            cout << "Order canceled. Exiting cashier panel.\n";
        }

    } while (choice != 5);
}

// MAIN
int main() {
    string food[MAX_ITEMS] = {"Burger", "Pizza", "Pasta", "Juice", "Coffee"};
    double price[MAX_ITEMS] = {120, 200, 150, 60, 80};
    int itemCount = 5;

    int choice;
    do {
        printHeader("COLLEGE CAFE SYSTEM");
        cout << "1. Cashier Mode\n";
        cout << "2. Admin Mode\n";
        cout << "3. Exit\n";

        choice = readIntInRange("Choose: ", 1, 3);

        if (choice == 1) {
            cashierPanel(food, price, itemCount);
        }
        else if (choice == 2) {
            adminPanel(food, price, itemCount);
        }

    } while (choice != 3);

    cout << "System closed.\n";
    return 0;
}
