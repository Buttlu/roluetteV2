#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

//<heads up>
//if a letter is inputed when asked for a number, an infinite loop will occur
//using cin.ignore() prevents this by removing the letters and cin.clear() clears the error flag so future inputs work
//</heads up>

//gets random number and announces it
int randomNum() {
    srand(time(0));
    int randn = rand() % 36 + 1;
    //writes out the "spinning..." part with delays
    for (int i = 0; i < 6; i++) {
        cout << "spinning..." << endl;
        this_thread::sleep_for(chrono::milliseconds(700));
    }

    //gets the color using modulo and a ternary operation
    //red == 0 and black == 1 in this case
    string randColor = randn % 2 == 0 ? "red" : "black";
    cout << "\nNumber was " << randn << "\nColor was " << randColor << endl;
    return randn;
}

//writes out and calculates the playters winnings
int won(int betAmount, int winMultiplier) {
    cout << "You won! You got " << betAmount * 2 << "kr" << endl;
    return betAmount * winMultiplier;
}


//writes out and calculates the playters losses
int lost(int betAmount) {
    cout << "You lost. You lost " << betAmount << "kr" << endl;
    return betAmount * (-1);
}

int colorBet(int betAmount) {
    int randn, betColor;
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
    randn = randomNum();
    //% 2 gives 0 or 1 and betColor is 1 or 2, so 1 is added onto the modulo part
    if ((randn % 2) + 1 == betColor)
        return won(betAmount, 2);
    else
        return lost(betAmount);
}

int numberBet(int betAmount) {
    int randn, betn;
    while (true) {
        cin.ignore();
        cout << "\nType the number you want to bet on (1 - 36): ";
        cin >> betn;
        if (betn < 1 || betn > 36)
            cout << "Invalid number, please choose another" << endl;
        else
            break;
    }

    randn = randomNum();
    if (randn == betn)
        return won(betAmount, 10);
    else 
        return lost(betAmount);
}


int main() {
    int balance = 1000, betAmount = 0, betType, age;
    string continued;

    cout << "How old are you? ";
    cin >> age;
    //skips if age is less than 18
    while (age >= 18) {
        system("cls"); //clears screen
        cout << "\nCurrent balance: " << balance << "kr" << endl;
        //asks for bet amount until a valid value is given
        while (true) {
            cin.clear();
            cin.ignore();
            cout << "\nHow much do you want to bet (100kr, 300kr, or 500kr)? ";
            cin >> betAmount;
            if (betAmount == 100 || betAmount == 300 || betAmount == 500)
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
            if (betType == 1) {
                balance += colorBet(betAmount);
                break;
            }
            else if (betType == 2) {
                balance += numberBet(betAmount);
                break;
            }
            else
                cout << "Invalid bet type. Please choose one of the alternatives provided" << endl;
        }
        cout << "\nCurrent balance: " << balance << endl;

        //ends if balance is below 100
        if (balance < 100) {
            cout << "Too little money left" << endl;
            break;
        }
        
        cout << "\nType 'stop' to stop, type anything else to continue" << endl;
        cin >> continued;
        if (continued == "stop")
            break;
    }
    cout << "Thanks for playing!" << "\nTotal earnings: " << balance - 1000 << "kr" << endl;
}