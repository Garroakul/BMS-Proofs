class BankAccount {

    /* Simple container class.
       Holds owner name, balance, and an arbitrary ID.
       Data is currently open, can also be set private as needed.
     */

    string owner;
    int acctID;
    double balance;

    BankAccount(string opener, int thisID, double startBalance) {
        owner = opener;
        acctID = thisID;
        balance = startBalance;
    }
};

class BigBank {

    /* Overall managing class for the bank accounts.
       Max sets the maximum accounts for alloc purposes.
       Total should be lock-stepped with accountList's allocation.
       List is the collection of accounts in the bank.
     */

    //BankAccount[] accountList;
    BankAccount acccountList[100];

    int accountMax;
    int accountTotal;

    // Standard assignment constructor.

    BigBank(int max) {
        accountMax = max;
        accountList = new BankAccount[max];
        accountTotal = 0;
    }

    /* Next two methods are account grabbers.
       Feed either an ID or an owner string and it'll return the account.
       Or null if there's no account.
     */

    BankAccount accountByOwner(string input) {
        for (int i = 0; i < accountTotal; i++) {
            BankAccount thisAcct = accountList[i];
            if (thisAcct.owner == input) return thisAcct;
        }
        return null;
    }

    BankAccount accountByID(int ID) {
        if (ID > accountTotal) return null;
        else return accountList[ID - 1];
    }

    // Index from account is also handy.

    int indexFromAccount(BankAccount thisAccount) {
        for (int i = 0; i < accountTotal; i++) {
            if (accountList[i] == thisAccount) return i;
        }
        return null;
    }

    // Next up is opening and closing accounts.

    bool createAccount(string person, double startBal) {
        accountList[accountTotal] = new BankAccount(person, accountTotal + 1, startBal);
        accountTotal++;
        return true;
    }

    bool deleteAccountOwner(string owner) {
        BankAccount toDelete = accountByOwner(owner);
        if (toDelete != null) {
            int indDel = indexFromAccount(toDelete);
            free(toDelete);
            accountList[indDel] = null;
            return true;
        } else return false;
    }

    bool deleteAccountID(int ID) {
        BankAccount toDelete = accountByID(ID);
        if (toDelete != null) {
            int indDel = indexFromAccount(toDelete);
            free(toDelete);
            accountList[indDel] = null;
            return true;
        } else return false;
    }

    // Input owner name, get ID out. Easy.

    int findIDByOwner(string owner) {
        BankAccount thisAcct = accountByOwner(owner);
        return thisAcct.acctID;
    }

    // Deposits and Withdrawals. Withdraw has a bool check for sufficient funds.

    void makeDeposit(BankAccount thisAcct, double amt) {
        thisAcct.balance += amt;
    }

    void makeDeposit(string owner, double amt) {
        BankAccount thisAcct = accountByOwner(owner);
        makeDeposit(thisAcct, amt);
    }

    void makeDeposit(int ID, double amt) {
        BankAccount thisAcct = accountByID(ID);
        makeDeposit(thisAcct, amt);
    }

    bool makeWithdraw(BankAccount thisAcct, double amt) {
        if (thisAcct.balance < amt) return false;
        thisAcct.balance -= amt;
        return true;
    }

    bool makeWithdraw(string owner, double amt) {
        BankAccount thisAcct = accountByOwner(owner);
        return makeWithdraw(thisAcct, amt);
    }

    bool makeWithdraw(int ID, double amt) {
        BankAccount thisAcct = accountByID(ID);
        return makeWithdraw(thisAcct, amt);
    }

    // Transfer implemented as paired withdrawal/deposit.

    bool makeTransfer(BankAccount accFrom, BankAccount accTo, double amt) {
        bool active = true;
        active = makeWithdraw(accFrom, amt);
        if (!active) return active;
        makeDeposit(accTo, amt);
        return active;
    }

    bool makeTransfer(string ownerFrom, string ownerTo, double amt) {
        BankAccount accFrom = accountByOwner(ownerFrom);
        BankAccount accTo = accountByOwner(ownerTo);
        return makeTransfer(accFrom, accTo, amt);
    }

    bool makeTransfer(int IDFrom, int IDTo, double amt) {
        BankAccount accFrom = accountByID(IDFrom);
        BankAccount accTo = accountByID(IDTo);
        return makeTransfer(accFrom, accTo, amt);
    }

    void addInterest(BankAccount thisAcct, double rate, double years) {
        if (rate < 0) return;
        thisAcct.balance *= ((1 + rate) * years);
    }

    void addInterest(string owner, double rate, double years) {
        BankAccount thisAcct = accountByOwner(owner);
        return addInterest(thisAcct, rate, years);
    }

    void addInterest(int ID, double rate, double years) {
        BankAccount thisAcct = accountByID(ID);
        return addInterest(thisAcct, rate, years);
    }

    // Getters for total account number and total balance.

    int accountNumber() {
        int accCount = 0;
        for (int i = 0; i < accountTotal; i++) {
            if (accountList[i] != null) accCount++;
        }
        return accCount;
    }

    double totalMoney() {
        double money = 0;
        for (int i = 0; i < accountTotal; i++) {
            if (accountList[i] != null) money += accountList[i].balance;
        }
        return money;
    }

    // Maintenance functions.

    bool expandSize(int newSize) {
        if (newSize < accountMax) return false;
        else {
            accountMax = newSize;
            return true;
        }
    }

    /* This warrants some explanation.
       This function fixes the annoying issue with arrays -
       - that as you add/remove entries it looks more and more like Swiss Cheese.
       The account list is copied over to a list.
       It is then consolidated as it is copied over to the old list.
     */

    void resizeSet() {
        BigBank tempList = BankAccount[accountMax];
        for (int i = 0; i < accountTotal; i++) {
            tempList[i] = accountList[i];
            accountList[i] = null;
        }
        int slot = 0;
        for (int i = 0; i < accountTotal; i++) {
            if (tempList[i] != null) {
                accountList[slot] = tempList[i];
                slot++;
            }
        }
        int newCount = 0;
        for (int i = 0; i < accountTotal; i++) {
            if (accountList[i] != null) newCount++;
        }
        accountTotal = newCount;
    }
};

int main() {
    BigBank thisBank = new BigBank(100);

    // Display options
    char input;
    do {
        cout << "BIG BANK";
        cin.get();
        cout << "nnt1. create account";
        cout << "nnt2. deposit";
        cout << "nnt3. withdraw";
        cout << "nnt4. close account";
        //...etc
        cout << "nnt10. exit";
        cout << "nntSelect a function ";
        cin >> input;

        system(cls); //clear screen
        switch (input) {
            case '1':
                createAccount("test", 100);
                break;

                //case '2': ... ; break;

        }
        cin.ignore();
        cin.get();
    }while(input!='10');

    return 0;
}