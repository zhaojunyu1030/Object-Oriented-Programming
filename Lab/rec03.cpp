/*
  rec03.cpp
  Zhao Junyu
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account {
     string name;
     int number;
};


// Task 2
// Define an Account class (use a different name than in Task 1)
class AccountC {
     friend ostream& operator<<(ostream& os, const AccountC& rhs);
public:
     AccountC(const string& aName, int aNumber) : name(aName), number(aNumber) { }
     const string& getName() const { return name; }
     int getNumber() const { return number; }
private:
     string name;
     int number;
};

// ostream& operator<<(ostream& os, const AccountC& rhs) {
//      os << rhs.getName() << "\t" << rhs.getNumber() << endl;
//      return os;
// }

ostream& operator<<(ostream& os, const AccountC& rhs) {
     os << rhs.name << "\t" << rhs.number << endl;
     return os;
}


// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".
class Transaction {
     friend ostream& operator<<(ostream& os, const Transaction& rhs);
public:
     Transaction(const string& aOperation, int aAmount) :
     operation(aOperation), amount(aAmount) { }
private:
     string operation;
     int amount;
};

ostream& operator<<(ostream& os, const Transaction& rhs) {
     os << rhs.operation << "\t" << rhs.amount;
     return os;
}

class Account3 {
     friend ostream& operator<<(ostream& os, const Account3& rhs);
public:
     Account3(const string& aName, int aNumber) :
     name(aName), number(aNumber) { }
     const string& getName() const { return name; }
     int getNumber() const { return number; }
     void setHistory(const string& operation, int amount) {
          history.emplace_back(operation, amount);
     }
     void setBalance(int amount) { balance += amount; }
     int getBalance() const { return balance; }
private:
     string name;
     int number;
     vector<Transaction> history;
     int balance;
};

ostream& operator<<(ostream& os, const Account3& rhs) {
     os << rhs.name << "\t" << rhs.number << ": \n";
     for (const Transaction& oneOperation : rhs.history) {
          cout << "\t" << oneOperation << endl;
     }
     cout << endl;
     return os;
}


// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.
class Account4 {
     friend ostream& operator<<(ostream& os, const Account4& rhs);
public:
     Account4(const string& aName, int aNumber) :
     name(aName), number(aNumber) { }
     class Transaction {
          friend ostream& operator<<(ostream& os, const Transaction& rhs);
     public:
          Transaction(const string& aOperation, int aAmount) :
          operation(aOperation), amount(aAmount) { }
     private:
          string operation;
          int amount;
     };
     const string& getName() const { return name; }
     int getNumber() const { return number; }
     void setHistory(const string& operation, int amount) {
          history.emplace_back(operation, amount);
     }
     void setBalance(int amount) { balance += amount; }
     int getBalance() const { return balance; }
private:
     string name;
     int number;
     vector<Transaction> history;
     int balance;
};

ostream& operator<<(ostream& os, const Account4::Transaction& rhs) {
     os << rhs.operation << ' ' << rhs.amount;
     return os;
}

ostream& operator<<(ostream& os, const Account4& rhs) {
     os << rhs.name << "\t" << rhs.number << ": \n";
     for (size_t i=0; i<rhs.history.size(); i++) {
          os << "\t" << rhs.history[i] << endl;
     }
     return os;
}


// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.
class Account5 {

     class Transaction {
          friend ostream& operator<<(ostream& os, const Transaction& rhs);
     public:
          Transaction(const string& aOperation, int aAmount) :
          operation(aOperation), amount(aAmount) { }
     private:
          string operation;
          int amount;
     };

     friend ostream& operator<<(ostream& os, const Account5& rhs);
     friend ostream& operator<<(ostream& os, const Transaction& rhs);

public:
     Account5(const string& aName, int aNumber) :
     name(aName), number(aNumber) { }
     const string& getName() const { return name; }
     int getNumber() const { return number; }
     void setHistory(const string& operation, int amount) {
          history.emplace_back(operation, amount);
     }
     void setBalance(int amount) { balance += amount; }
     int getBalance() const { return balance; }

private:
     string name;
     int number;
     vector<Transaction> history;
     int balance;
};

ostream& operator<<(ostream& os, const Account5::Transaction& rhs) {
     os << rhs.operation << ' ' << rhs.amount;
     return os;
}

ostream& operator<<(ostream& os, const Account5& rhs) {
     os << rhs.name << "\t" << rhs.number << ": \n";
     for (const Account5::Transaction& transaction: rhs.history) {
          os << "\t" << transaction << endl;
     }
     return os;
}


int main()
{

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";
     vector<Account> accounts;
     ifstream ifs;
     ifs.open("accounts.txt");
     if (!ifs) { cerr << "Error opening file" << endl; exit(1); }
     string name;
     int number;
     while (ifs >> name >> number) {
          Account account;
          account.name = name;
          account.number = number;
          accounts.push_back(account);
     }
     ifs.close();
     for (const Account& account : accounts) {
          cout << account.name << "\t" << account.number << endl;
     }

    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";
     accounts.clear();
     ifs.open("accounts.txt");
     if (!ifs) { cerr << "Error opening file" << endl; exit(1); }
     while (ifs >> name >> number) {
          Account account{name, number};
          accounts.push_back(account);
     }
     ifs.close();
     for (const Account& account : accounts) {
          cout << account.name << "\t" << account.number << endl;
     }


    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";
     vector<AccountC> accountsC;
     ifs.open("accounts.txt");
     if (!ifs) { cerr << "Error opening file" << endl; exit(1); }
     while(ifs >> name >> number) {
          AccountC newAccount(name, number);
          accountsC.push_back(newAccount);
     }
     for (const AccountC& account : accountsC) {
          cout << account.getName() << "\t" << account.getNumber() << endl;
     }
     ifs.close();


    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
     for (const AccountC& account : accountsC) {
          cout << account;
     }


    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
     for (const AccountC& account : accountsC) {
          cout << account;
     }


    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
     accountsC.clear();
     ifs.open("accounts.txt");
     if (!ifs) { cerr << "Error opening file" << endl; exit(1); }
     while(ifs >> name >> number) {
          accountsC.push_back(AccountC(name, number));
     }
     for (const AccountC& account : accountsC) {
          cout << account;
     }
     ifs.close();


    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
     accountsC.clear();
     ifs.open("accounts.txt");
     if (!ifs) { cerr << "Error opening file" << endl; exit(1); }
     while(ifs >> name >> number) {
          accountsC.emplace_back(name, number);
     }
     for (const AccountC& account : accountsC) {
          cout << account;
     }
     ifs.close();


    cout << "==============\n"
         << "\nTask 3:\nAccounts and Transaction:\n";
     ifs.open("transactions.txt");
     if (!ifs) { cerr << "Error opening file" << endl; exit(1); }
     vector<Account3> accounts3;
     string token;
     while (ifs >> token) {
          if (token == "Account") {
               string name;
               int number;
               ifs >> name >> number;
               accounts3.emplace_back(name, number);
          } else if (token == "Deposit") {
               int number;
               int amount;
               ifs >> number >> amount;
               for (Account3& account : accounts3) {
                    if (account.getNumber() == number) {
                         account.setBalance(amount);
                         account.setHistory(token, amount);
                         break;
                    }
               }
          } else if (token == "Withdraw") {
               int number;
               int amount;
               ifs >> number >> amount;
               for (Account3& account : accounts3) {
                    if (account.getNumber() == number) {
                         if (account.getBalance() <= amount) {
                              cout << "Account# " << account.getNumber()
                              << " has only " << account.getBalance()
                              << ". Insufficient for withdrawal of "
                              << amount << '.' << endl;
                         } else {
                              account.setBalance(amount);
                              account.setHistory(token, amount);
                         }
                         break;
                    }
               }
          }
     }

     for (const Account3& account : accounts3) {
          cout << account << endl;
     }
     ifs.close();


    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";
     accountsC.clear();
     ifs.open("transactions.txt");
     if (!ifs) { cerr << "Error opening file" << endl; exit(1); }
     vector<Account4> accounts4;
     while (ifs >> token) {
          if (token == "Account") {
               string name;
               int number;
               ifs >> name >> number;
               accounts4.emplace_back(name, number);
          } else if (token == "Deposit") {
               int number;
               int amount;
               ifs >> number >> amount;
               for (Account4& account : accounts4) {
                    if (account.getNumber() == number) {
                         account.setBalance(amount);
                         account.setHistory(token, amount);
                         break;
                    }
               }
          } else if (token == "Withdraw") {
               int number;
               int amount;
               ifs >> number >> amount;
               for (Account4& account : accounts4) {
                    if (account.getNumber() == number) {
                         if (account.getBalance() <= amount) {
                              cout << "Account# " << account.getNumber()
                              << " has only " << account.getBalance()
                              << ". Insufficient for withdrawal of "
                              << amount << '.' << endl;
                         } else {
                              account.setBalance(amount);
                              account.setHistory(token, amount);
                         }
                         break;
                    }
               }
          }
     }

     for (const Account4& account : accounts4) {
          cout << account << endl;
     }
     ifs.close();


    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";
     accountsC.clear();
     ifs.open("transactions.txt");
     if (!ifs) { cerr << "Error opening file" << endl; exit(1); }
     vector<Account5> accounts5;
     while (ifs >> token) {
          if (token == "Account") {
               string name;
               int number;
               ifs >> name >> number;
               accounts5.emplace_back(name, number);
          } else if (token == "Deposit") {
               int number;
               int amount;
               ifs >> number >> amount;
               for (Account5& account : accounts5) {
                    if (account.getNumber() == number) {
                         account.setBalance(amount);
                         account.setHistory(token, amount);
                         break;
                    }
               }
          } else if (token == "Withdraw") {
               int number;
               int amount;
               ifs >> number >> amount;
               for (Account5& account : accounts5) {
                    if (account.getNumber() == number) {
                         if (account.getBalance() <= amount) {
                              cout << "Account# " << account.getNumber()
                              << " has only " << account.getBalance()
                              << ". Insufficient for withdrawal of "
                              << amount << '.' << endl;
                         } else {
                              account.setBalance(amount);
                              account.setHistory(token, amount);
                         }
                         break;
                    }
               }
          }
     }

     for (const Account5& account : accounts5) {
          cout << account << endl;
     }
     ifs.close();


} // main
