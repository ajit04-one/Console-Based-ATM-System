#include <iostream> //input/output headerfile
#include <string>   //for string
#include <limits>   // headerfile to determine the limit
#include <fstream>  // for file handling

using namespace std;

class AtmAccount
{
private:
    double balance;

public:
    AtmAccount(double initialBalance = 0.0) // constructor that sets balance to 0 to prevent any garbage value
    {
        balance = initialBalance;
    }

    void depositMoney() // function that takes deposit :: input only numbers
    {
        double deposit_amount = 0;
        cout << "How much would you like to deposit?:: \n";
        if (!(cin >> deposit_amount))
        {
            cout << "Please enter numbers only\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (deposit_amount < 0)
        {
            cout << "Sorry You can't deposit\n";
        }
        else
        {
            balance += deposit_amount;
            cout << "Your deposited amount is: " << balance << '\n';
            saveBalance();
        }
    }

    void withdrawMoney() // function to withdraw :: input only numbers
    {
        double withdraw_amount = 0;
        cout << "How much would you like to withdraw?:: \n";
        if (!(cin >> withdraw_amount))
        {
            cout << "Please enter numbers only\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (withdraw_amount < 0)
        {
            cout << "Sorry for the inconvenience but you can't withdraw!! \n";
        }
        else if (withdraw_amount > balance)
        {
            cout << "You don't have enough balance!!\n ";
        }
        else
        {
            balance -= withdraw_amount;
            cout << "Your balance after withdrawing is :: " << balance << '\n';
            saveBalance();
        };
        // Append Transaction History
        fstream logfile("transactions.txt", ios::app);
        logfile << "Withdraw: " << withdraw_amount
                << " | Balance: " << balance << '\n';
        logfile.close();
    }
    double seeBalance() // function to see the balance of your account
    {

        cout << "Your current balance is :: " << balance << '\n';
        return balance;
    }

    void saveBalance()
    {
        fstream outfile("account.txt", ios::out);
        outfile << balance;
        outfile.close();
    }
};

int main()
{

    fstream myfile;
    myfile.open("account.txt", ios::in); // open a file to read
    double stored_balance = 0.0;
    if (myfile.is_open())
    {
        myfile >> stored_balance; // read balance
        myfile.close();
    }

    AtmAccount account(stored_balance);
    //  --PIN AUTHENTICATION--
    const int CORRECT_PIN = 7530; // constant pin
    int userInput_pin = 0;        // takes pin from user
    int attempts = 0;             // number of attempts
    const int MAXIMUM_ATTEMPT = 3;
    char choice;  // shows the menu
    char options; // options to repeat the menu

    while (userInput_pin != CORRECT_PIN) // loop repeat until the pin is entered correctly
    {
        cout << "Enter your PIN :: ";
        if (!(cin >> userInput_pin))
        {
            cout << "Please enter numbers only\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (userInput_pin < 1000 || userInput_pin > 9999)
        {
            cout << "Pin must be 4 digit\n";
            cout << "TRY AGAIN\n";
            continue;
        }

        if (userInput_pin != CORRECT_PIN)
        {
            attempts++;
            cout << "The number of attempts left is " << MAXIMUM_ATTEMPT - attempts << '\n';
        }
        if (attempts == MAXIMUM_ATTEMPT)
        {
            cout << "Too many attempts!!! \n";
            cout << "Card Blocked";
            return 0;
        }
    }

    do // loop to repeat after taking "yes" from the user
    {

        if (userInput_pin == CORRECT_PIN)
        {
            cout << "What would you like to do?: \n";
            cout << "1. Deposit Money\n";
            cout << "2. Withdraw Money\n";
            cout << "3. See Balance\n";
            cout << "4. Save Balance\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case '1':
                account.depositMoney();
                break;
            case '2':
                account.withdrawMoney();
                break;
            case '3':
                account.seeBalance();
                break;
            case '4':
                account.saveBalance();
                break;
            case '5':
                exit(0);
                break;

            default:
                cout << "Invalid Number\n";
                break;
            }
        }
        else
        {
            cout << "Invalid choice\n";
            return 1;
        }
        cout << "Would you like to do it again?? :: ";
        cin >> options;

    } while (options == 'y' || options == 'Y');
    cout << "Thank your for choosing my atm\n";

    return 0;
}