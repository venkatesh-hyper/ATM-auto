#include <iostream>
#include <fstream>
#include <limits>

class ATM {
private:
    char username[30];
    int accountNumber;  // Added account number
    int password;
    int balance;

public:
    char* getUsernames() {
        return username;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    int getPasswords() {
        return password;
    }

    void getData() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEnter bankers name:";
        std::cin.getline(username, 30);
        std::cout << "\nEnter 4-digit password:";
        std::cin >> password;
        std::cout << "\nEnter initial balance:";
        std::cin >> balance;
        // Assign a unique account number (you may want to implement a more sophisticated logic)
        accountNumber = generateAccountNumber();
    }

    void showData() {
        std::cout << "Account Number: " << accountNumber
                  << ", \n  Username: " << username
                  << ", \n  Password: " << password
                  << ", \n  Balance: " << balance
                  << std::endl;
    }

    int addUser();
    int viewAllUsers();
    int deleteUser(char*);
    void updateUserAsDeposit(char*);
    void updateUserAsWithdraw(char*);
    int searchSpecificUser(char*, int);
    int searchAllUsersToDisplay(char*);
    int generateAccountNumber();
};

int ATM::addUser() {
    ATM a;
    std::ofstream file;
    file.open("users.txt", std::ios::out | std::ios::app);
    if (!file) {
        std::cout << "Error in creating file.." << std::endl;
        return 0;
    }
    a.getData();
    file.write((char*)&a, sizeof(a));
    file.close();
    return 0;
}

int ATM::viewAllUsers() {
    ATM a;
    std::ifstream file1;
    file1.open("users.txt", std::ios::in);
    if (!file1) {
        std::cout << "Error in opening file.." << std::endl;
        return 0;
    }
    file1.read((char*)&a, sizeof(a));
    while (!file1.eof()) {
        a.showData();
        file1.read((char*)&a, sizeof(a));
    }
    file1.close();
    return 0;
}

int ATM::deleteUser(char* uname) {
    ATM a;
    std::fstream original, temp;
    original.open("users.txt", std::ios::in);
    if (!original) {
        std::cout << "\nfile not found" << std::endl;
        return 0;
    } else {
        temp.open("temp.txt", std::ios::out | std::ios::app);
        original.read((char*)&a, sizeof(a));
        while (!original.eof()) {
            if (!strcmp(a.getUsernames(), uname)) {
                std::cout << "data found and deleted\n"
                          << a.getUsernames() << std::endl;
            } else {
                temp.write((char*)&a, sizeof(a));
            }
            original.read((char*)&a, sizeof(a));
        }
        original.close();
        temp.close();
        remove("users.txt");
        rename("temp.txt", "users.txt");
        a.viewAllUsers();
    }
    return 0;
}

void ATM::updateUserAsDeposit(char* uname) {
    ATM a;
    std::fstream file, temp;
    file.open("users.txt", std::ios::in | std::ios::out | std::ios::ate);
    temp.open("temp.txt", std::ios::out | std::ios::app);
    file.seekg(0);
    file.read((char*)&a, sizeof(a));
    while (!file.eof()) {
        if (!strcmp(a.getUsernames(), uname)) {
            int b;
            std::cout << "\nEnter amount to deposit:";
            std::cin >> b;
            a.balance = a.balance + b;
            std::cout << "\nBalance is:" << a.balance << std::endl;
            temp.write((char*)&a, sizeof(a));
        } else {
            temp.write((char*)&a, sizeof(a));
        }
        file.read((char*)&a, sizeof(a));
    }
    file.close();
    temp.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
}

void ATM::updateUserAsWithdraw(char* uname) {
    ATM a;
    std::fstream file, temp;
    file.open("users.txt", std::ios::in | std::ios::out | std::ios::ate);
    temp.open("temp.txt", std::ios::out | std::ios::app);
    file.seekg(0);
    file.read((char*)&a, sizeof(a));
    while (!file.eof()) {
        if (!strcmp(a.getUsernames(), uname)) {
            int b;
            std::cout << "\nEnter amount to withdraw:";
            std::cin >> b;
            if (a.balance < b) {
                std::cout << "\nInsufficient balance to withdraw" << std::endl;
            } else {
                a.balance = a.balance - b;
                temp.write((char*)&a, sizeof(a));
                std::cout << "\nBalance is:" << a.balance << std::endl;
            }
        } else {
            temp.write((char*)&a, sizeof(a));
        }
        file.read((char*)&a, sizeof(a));
    }
    file.close();
    temp.close();
    remove("users.txt");
    rename("temp.txt", "users.txt");
}

int ATM::searchSpecificUser(char* uname, int pass) {
    ATM a;
    std::fstream f;
    f.open("users.txt", std::ios::in);
    if (!f) {
        std::cout << "Error in opening file.." << std::endl;
        return 0;
    }
    f.read((char*)&a, sizeof(a));
    while (!f.eof()) {
        if (!strcmp(a.getUsernames(), uname)) {
            if (a.getPasswords() == pass) {
                return 1;
            }
        }
        f.read((char*)&a, sizeof(a));
    }
    f.close();
    return 0;
}

int ATM::searchAllUsersToDisplay(char* uname) {
    ATM a;
    std::ifstream file1;
    file1.open("users.txt", std::ios::in);
    if (!file1) {
        std::cout << "Error in opening file.." << std::endl;
        return 0;
    }
    file1.read((char*)&a, sizeof(a));
    while (!file1.eof()) {
        if (!strcmp(a.getUsernames(), uname)) {
            a.showData();
            return 0;
        }
        file1.read((char*)&a, sizeof(a));
    }
    file1.close();
    return 0;
}

int ATM::generateAccountNumber() {
    // Simple account number generation (you may want to implement a more sophisticated logic)
    static int accountNumberCounter = 1000;
    return accountNumberCounter++;
}

void atmUser() {
    ATM a;
    char uname[30];
    int pass, ch, ch1, ch2, found = 0;

mainmenu:
    std::cout << "\n                Welcome to MARI AMMAN INDIAN BANK ATM\n\n";
    std::cout << "\n----------------PLEASE INSERT YOUR CARD -||-------------------- \n \n\n        (after insert card press \"2\" to continue.. )\n        (press \"3\" to exit)";
    std::cin  >> ch ;
    switch (ch) {
        case 1:
        rerun:
            std::cout << "\nEnter details to login as Admin\n";
            std::cout << "\nEnter password:";
            std::cin >> pass;
            if (pass == 1234) {
            admin:
                std::cout << "\nWelcome to Admin Menu";
                std::cout << "\n1. Add User\n2. Delete User\n3. View All User\n4. Exit";
                std::cout << "\nSelect one : ";
                std::cin >> ch1;
                switch (ch1) {
                    case 1:
                        a.addUser();
                        goto admin;

                    case 2:
                        std::cout << "\nEnter the Username to be deleted : ";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.getline(uname, 30);
                        a.deleteUser(uname);
                        goto admin;

                    case 3:
                        a.viewAllUsers();
                        goto admin;

                    case 4:
                        break;
                }
            } else {
                std::cout << "\nDetails are incorrect! Please try again";
                std::cin.get();
                goto rerun;
            }
            goto mainmenu;

        case 2:
            std::cout << "\nEnter details to login as User\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter CUSTOMER name:";
            std::cin.getline(uname, 30);
            std::cout << "\nEnter PIN:";
            std::cin >> pass;
            found = a.searchSpecificUser(uname, pass);
            if (found) {
            user:
                std::cout << "\nWelcome " << uname;
                std::cout << "\nWelcome to CUSTOMER Menu";
                std::cout << "\n1. Deposit\n2. Withdraw\n3. View Account\n4. Exit\nEnter your choice:";
                std::cin >> ch2;
                switch (ch2) {
                    case 1:
                        a.updateUserAsDeposit(uname);
                        goto user;
                    case 2:
                        a.updateUserAsWithdraw(uname);
                        goto user;
                    case 3:
                        a.searchAllUsersToDisplay(uname);
                        goto user;
                    case 4:
                        std::cout << "Thank you";
                        break;
                }
            } else {
                std::cout << "\nNo account found with the username :(\n\nHit ENTER to continue " << uname;
                std::cin.get();
            }
            goto mainmenu;

        case 3:
            std::cout << "\nThank you for USING OUR OUR ATM";
            std::cout << "\n MARI AMMAN INDIAN BANK THANKING YOU";
            std::cin.get();
            break;
    }
}

int main() {
    atmUser();
    return 0;
}


