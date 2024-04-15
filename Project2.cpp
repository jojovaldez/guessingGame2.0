#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

//Declare Global Enumeration Constant
enum menuOptions {
        DisplayLeft = 1, 
        DisplayRight,
        Guess,
        Change,
        Exit,
    };

string getName () {
    //Ask for Players Name
    string usersName;
    cout << "Enter your name: ";
    getline(cin, usersName);

    //Allows only whitespaces and alphabets only
    for (int i = 0; i < usersName.size(); i++) {
        char c = usersName.at(i);
        if ((isalpha(c) || isspace(c)) == false) {
                cout << "Your name can only have alphabets or spaces. Enter again." << endl;
                cout << "Enter your name: ";
                getline(cin, usersName);
                i = 0;
        }
    }

    return usersName;
}


int main() {
    //Beginning Format for Introduction and Credit
    cout << setfill('-') << setw(52) << left << "+" << right << "+" << "" << endl;
    cout << "|         Computer Science and Engineering          |" << endl;
    cout << "|          CSCE 1030 - Computer Science I           |" << endl;
    cout << "|     Jose Valdez jov0006 josevaldez6@my.unt.edu    |" << endl;
    cout << "|    Ronni Wachira rww0095 ronniwachira@my.unt.edu  |" << endl;
    cout << "|     Tanza Mahmud tsm0181 tanazmahmud@my.unt.edu   |" << endl;
    cout << setfill('-') << setw(52) << left << "+" << right << "+" << "" << endl; 




    return 0; 
}