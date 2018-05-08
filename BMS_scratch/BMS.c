
//---------------------------------------------------------------
//                   Bank Management System				
//---------------------------------------------------------------

/*It provides functions to:
   - open a new account
   - close (delete) an account
   - make a deposit
   - make a withdrawal
   - make an internal transfer from one account to another
     This should be implemented using withdrawal and deposit
   - get the current number of accounts
   - get the total amount of money held by the bank (the sum of the balances)
   - add interest to an account, given an interest rate and amount of time
 */

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>

using namespace std;

//class
class bank_account {
    int account_number;
    char owner_name[100];
    int deposit;

public:
    void open_account(); //- open a new account
    void show_account() const;  //function to show data on screen
    void deposit(int);  //- make a deposit
    void withdraw(int); //- make a withdrawal
    void transfer(int,int); //- make an internal transfer //TODO
    int get_number_of_accounts();//- get the current number of accounts //TODO
    double get_total_money();//- get the total amount of money held by the bank //TODO
    void add_interest(double,int);//-add interest,given rate and amount of time(in sec/hr/day) //TODO
    int return_accountNo() const; //function to return account number
    int return_depositAm() const; //function to return balance amount
};         //class ends here

void bank_account::open_account() {
    cout << "Please input an account number";
    cin >> account_number;
    cout << "Please enter the owner's name: ";
    cin.getline(owner_name, 100);
    cout << "Please enter your first deposit amount to the account: ";
    cin >> deposit;
    cout << "Your bank account is all set..";
}

void bank_account::show_account() const {
    cout << "Your account No. is: " << account_number;
    cout << "Account Owner's Name: ";
    cout << owner_name;
    cout << "Your balance is: " << deposit;
}

void bank_account::deposit(int x) {
    deposit += x;
}

void bank_account::withdraw(int x) {
    deposit -= x;
}

int bank_account::return_accountNo() const {
    return account_number;
}

int bank_account::return_depositAm() const {
    return deposit;
}

//functions
void write_account();   //function to write record in binary file
void display_account(int);  //function to display account details
void delete_account(int);   //function to delete account
void deposit_amount(int);   //-deposit amount
void withdraw_amount(int);  //-withdraw amount

//main
int main() {
    //TODO Demo
    return 0;
}

//write file output
void write_account() {
    bank_account account;
    ofstream outFile;
    outFile.open("bank_account.dat", ios::binary | ios::app);
    account.open_account();
    outFile.write(reinterpret_cast<char *> (&account), sizeof(bank_account));
    outFile.close();
}

//read file
void display_sp(int n) {
    bank_account account;
    bool flag = false;
    ifstream inFile;
    inFile.open("bank_account.dat", ios::binary);
    cout << "nBALANCE DETAILSn";

    while (inFile.read(reinterpret_cast<char *> (&account), sizeof(bank_account))) {
        if (account.return_accountNo() == n) {
            account.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (!flag)
        cout << "Account number is not valid";
}

//delete
void delete_account(int n) {
    bank_account account;
    ifstream inFile;
    ofstream outFile;
    inFile.open("bank_account.dat", ios::binary);
    outFile.open("Temp.dat", ios::binary);
    inFile.seekg(0, ios::beg);
    while (inFile.read(reinterpret_cast<char *> (&account), sizeof(bank_account))) {
        if (account.return_accountNo() != n) {
            outFile.write(reinterpret_cast<char *> (&account), sizeof(bank_account));
        }
    }
    inFile.close();
    outFile.close();
    remove("bank_account.dat");
    rename("Temp.dat", "bank_account.dat");
    cout << "This account is deleted";
}

//deposit
void deposit_amount(int n) {
    int amount;
    bool found = false;
    bank_account account;
    fstream File;
    File.open("bank_account.dat", ios::binary | ios::in | ios::out);
    while (!File.eof() && !found) {
        File.read(reinterpret_cast<char *> (&account), sizeof(bank_account));
        if (account.return_accountNo() == n) {
            account.show_account();
            cout << "Please enter The amount to be deposited";
            cin >> amount;
            account.deposit(amount);

            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&account), sizeof(bank_account));
            cout << "Deposit is completed";
            found = true;
        }
    }
    File.close();
    if (!found)
        cout << "Account number is not valid";

//withdraw
    void withdraw_amount(int n) {
        int amount;
        bool found = false;
        bank_account account;
        fstream File;
        File.open("bank_account.dat", ios::binary | ios::in | ios::out);
        while (!File.eof() && !found) {
            File.read(reinterpret_cast<char *> (&account), sizeof(bank_account));
            if (account.return_accountNo() == n) {
                account.show_account();
                cout << "Please enter The amount to be withdraw";
                cin >> amount;
                int bal = ac.retdeposit() - amount;
                if (bal < 0)
                    cout << "Insufficient balance";
                else
                    account.withdraw(amount);
            }
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&account), sizeof(bank_account));
            cout << "Withdraw is completed";
            found = true;

        }
        File.close();
        if (!found)
            cout << "nn Record Not Found ";
    }
}

