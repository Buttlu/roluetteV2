#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

//gets random number and announces it
int randomNum() {
    srand(time(0));
    int random_number = rand() % 36 + 1;
    //writes out the "spinning..." part with delays
    for (int i = 0; i < 6; i++) {
        cout << "spinning..." << endl;
        this_thread::sleep_for(chrono::milliseconds(700));
    }

    //gets the color using modulo and a ternary operation
    //red == 0 and black == 1 in this case
    string randColor = random_number % 2 == 0 ? "red" : "black";
    cout << "\nNumber was " << random_number << "\nColor was " << randColor << endl;
    return random_number;
}

//writes out and calculates the playters winnings
int won(int betAmount, int winMultiplier) {
    cout << "You won! You got " << betAmount * winMultiplier << "kr" << endl;
    return betAmount * winMultiplier;
}


//writes out and calculates the playters losses
int lost(int betAmount) {
    cout << "You lost. You lost " << betAmount << "kr" << endl;
    return betAmount * (-1);
}

int loan() {
    int loanAmount = 0;
    string agree;

    system("cls");
    cout << "-----------------------------------\nWelcome to the bank\n-----------------------------------" << endl;
    
    //get's loan amount
    cout << "Type how much you want your loan to be: ";
    cin.clear();
    cin.ignore();
    cin >> loanAmount;
    cout << "\nYou want to loan " << loanAmount << "kr" << endl;
    cout << "Interest on loans are 0.6%. It will apply after every turn you play" << endl; //TOS
    while (true) {
        //gets if user wants to take or cancel loan
        cout << "Type 'agree' to complete loan \nType 'cancel' to cancel" << endl;
        cin >> agree;
        if (agree == "agree")
            return loanAmount;
        else if (agree == "cancel")
            return 0;
        else
            cout << "Invalid option";
    }
    return 0; //needed to make the funtction stop yelling at me (throws 'not all paths return value' error otherwise), this won't be used.
}

int colorBet(int betAmount) {
    int random_number, betColor;
    while (true) {
        cin.ignore();
        //gets color bet
        cout << "\nType 1 to bet on red, type 2 to bet on black: ";
        cin >> betColor;
        if (betColor == 1 || betColor == 2)
            break;
        else
            cout << "invalid color, please try again" << endl;
    }
    
    //gets random number and check if it won
    random_number = randomNum();
    //% 2 gives 0 or 1 and betColor is 1 or 2, so 1 is added onto the modulo part
    if ((random_number % 2) + 1 == betColor)
        return won(betAmount, 2);
    else
        return lost(betAmount);
}

//handles betting a number
int numberBet(int betAmount) {
    int random_number, bet_number;
    while (true) {
        cin.ignore();
        //get's what the user wants to bet on
        cout << "\nType the number you want to bet on (1 - 36): ";
        cin >> bet_number;
        if (bet_number < 1 || bet_number > 36)
            cout << "Invalid number, please choose another" << endl;
        else
            break;
    }

    //gets rendom number and checks if it matches the betting number
    random_number = randomNum();
    if (random_number == bet_number)
        return won(betAmount, 10);
    else 
        return lost(betAmount);
}


int main() {
    //variable creation. Variables on same line are used in related fields. 1st line is age, 2nd is for betting, 
    //and 3rd (and 4th) is for when the player is out of money and need more.
    int age;
    int balance = 1000, betAmount = 0, betType, amountWon = 0, totalAmountWon = 0;
    int amountLoaned = 0, noMoney;
    double debt = 0.0;
    string continued;

    cout << "How old are you? ";
    cin >> age;
    //skips if age is less than 18
    if (age < 18) {
        cout << "Too young to play" << endl;
        return 0;
    }

    while (true) {
        debt *= 1.006;
        system("cls"); //clears screen
        cout << "\nCurrent balance: " << balance << "kr" << endl;
        if (debt > 0) cout << "Current debt: " << debt << "kr" << endl;
        else {}
        //asks for bet amount until a valid value is given
        while (true) {
            cin.clear();
            cin.ignore();
            cout << "\nHow much do you want to bet (100kr, 300kr, or 500kr)? ";
            cin >> betAmount;
            if (betAmount > balance)
                cout << "\nNot enough money for that alternative" << endl;
            else if (betAmount == 100 || betAmount == 300 || betAmount == 500)
                break;
            else
                cout << "\nInvalid bet amount. Please choose one of the alternatives provided" << endl;
        }
        //asks for what to bet on until valid input is given
        while (true) {
            cin.clear();
            cin.ignore();
            cout << "\nWhat do you want to bet on (type 1 for color or 2 for number): ";
            cin >> betType;
            //gets and calculates winnings/losses
            if (betType == 1) {
                amountWon = colorBet(betAmount);
                balance += amountWon;
                totalAmountWon += amountWon;
                break;
            }
            //gets and calculates winnings/losses
            else if (betType == 2) {
                amountWon = numberBet(betAmount);
                balance += amountWon;
                totalAmountWon += amountWon;
                break;
            }
            else
                cout << "Invalid bet type. Please choose one of the alternatives provided" << endl;
        }
        cout << "\nCurrent balance: " << balance << "kr" << endl;
        cout << "Total winnings: " << totalAmountWon << "kr" << endl;
        if (debt > 0) cout << "Current debt: " << debt << "kr" << endl;

        //ends if balance is below 100
        if (balance < 100) {
            cout << "Too little money left" << endl;
            while (true) {
                cout << "Type 1 to stop playing \nType 2 to add another 1000kr \nType 3 to take a loan" << endl;
                cin >> noMoney;
                if (noMoney == 1)
                    return 0;
                //gets and calculates all money differences from the deposit
                else if (noMoney == 2) {
                    balance += 1000;
                    totalAmountWon -= 1000;
                    cout << "1000kr was added to your balance" << endl;
                    break;
                }
                //gets and calculates all money differences from the loan
                else if (noMoney == 3) {
                    amountLoaned = loan();
                    balance += amountLoaned;
                    debt += amountLoaned;
                    cout << "You loaned " << amountLoaned << "kr";
                    break;
                }
                else
                    cout << "Invalid choice, try again" << endl;
            }
        }
        else {}
        //gets if the user wants to quit
        cout << "\nType 'stop' to stop, type anything else to continue" << endl;
        cin >> continued;
        if (continued == "stop")
            break;
        else {}
    }
    //thanks for playing and displays total winnings and balance
    if (debt > 0) {
        cout << "Removing debt from total winings...";
        totalAmountWon -= debt;
    }
    cout << "Thanks for playing!" << endl;
    cout << "Total earnings: " << totalAmountWon << "kr" << endl;
    cout << "Final balance: " << balance << "kr" << endl;
}