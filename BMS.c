
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

class bank_account
{
	int account_number;
	char owner_name[40];
	int debit_amount;

public:
    void open_account();  //- open a new account
    void close_account(int); //- close (delete) an account
    void deposit(int);//- make a deposit
    void withdrawal(int);//- make a withdrawal
    void transfer(int,int); //- make an internal transfer
    int get_number_of_accounts();//- get the current number of accounts
    double get_total_money();//- get the total amount of money held by the bank
    void add_interest(double,int);//-add interest,given rate and amount of time(in sec/hr/day)
    void show_account_details();
    void modify_account();

}

void account_number::open_account()
{
    cout<<"nEnter The account No. :";
    cin>>account_number;
    cout<<"nnEnter The Name of The account Owner : ";
    cin.ignore();
    cin.getline(owner_name,40);
    cout<<"nEnter Your Debit Amount of Money: ";
    cin>>debit_amount;
    cout<<"nnnYour Account is All Set";
}

void account_number::close_account()
{
	cout<<"nEnter The account No. :";
    cin>>account_number;
    cout<<"nAre you sure to close your account? This is not revertable ";
    cin>>close_account(account_number);
    cout<<"nnnYour Account is closed";
}

void account_number::deposit(int amount)
{
    debit_amount+=amount;
}

int main()
{

}


