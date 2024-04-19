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

//Global Constants
const int SIZE = 5;

//Introduction to the Game (Beginning Format)
void introduction(){
    cout << setfill('-') << setw(52) << left << "+" << right << "+" << "" << endl;
    cout << "|         Computer Science and Engineering          |" << endl;
    cout << "|          CSCE 1030 - Computer Science I           |" << endl;
    cout << "|     Jose Valdez jov0006 josevaldez6@my.unt.edu    |" << endl;
    cout << "|    Ronni Wachira rww0095 ronniwachira@my.unt.edu  |" << endl;
    cout << "|     Tanza Mahmud tsm0181 tanazmahmud@my.unt.edu   |" << endl;
    cout << setfill('-') << setw(52) << left << "+" << right << "+" << "" << endl; 
}

//Function for Players Name
string getName(string usersName) {
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

     //Statements for upper into lowercase & vice-versa
    for (int t = 0; t < usersName.size(); ++t) {
        if (t != 0 || t > 0 && usersName.at(t - 1) != ' ') {
            usersName.at(t) = tolower(usersName.at(t));
        }
    }

    for (int t = 0; t < usersName.size(); ++t) {
        if (t == 0 || t > 0 && usersName.at(t - 1) == ' ') {
            usersName.at(t) = toupper(usersName.at(t));
        }
    }

    //If-Statement for senior or junior
    int targetSenior = usersName.find(" Senior");
    if (targetSenior != string::npos) {
        usersName.erase(targetSenior, 7);
        usersName.append(", Sr.");
    }

    int targetJunior = usersName.find(" Junior");
    if (targetJunior != string::npos) {
        usersName.erase(targetJunior, 7);
        usersName.append(", Jr.");
    }
    return usersName;
}

//Showcasing the Array
void genShowMatrix(int randomNumbers[SIZE][SIZE]) {
    //Loop to initialize all values within the array to "-1"
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j) {
            randomNumbers[i][j] = -1;
        }
    }
}

//Initialize the Hidden Array
void genHideMatrix(int hiddenMatrix[SIZE][SIZE]) {
    srand(time(NULL));
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            hiddenMatrix[i][j] = rand () % (349 - 150 + 1) + 150;
        }
    }
}

//Used to display the corressponding 2D array
void showMatrix(int shownMatrix[SIZE][SIZE]){
    //Print Array
    for(int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
        cout << shownMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

//Showcase the Left Number if Prompted
int setDisplayLeft(int &lowerBound, int &upperBound, int randomNumber1) {
     if (lowerBound == -1 && upperBound == -1){
                    cout << "You will only get 1 point for guessing correctly and lose 10 points " << endl;
                    cout << "for guessing incorrectly, now." << endl;
                    lowerBound = randomNumber1;
                    cout << lowerBound << "      " << upperBound << endl;
                } else {
                    cout << "You have already displayed the right boundary, you cannot display both." << endl;
                    cout << lowerBound << "      " << upperBound << endl;
                }
    return lowerBound;
}

//Showcase the Right Number if Prompted
int setDisplayRight(int &lowerBound, int &upperBound, int randomNumber2){
    if (lowerBound == -1 && upperBound == -1) {
                    cout << "You will only get 1 point for guessing correctly and lose 10 points " << endl;
                    cout << "for guessing incorrectly, now." << endl;
                    upperBound = randomNumber2;
                    cout << lowerBound << "      " << upperBound << endl;
                } else {
                    cout << "You have already displayed the left boundary, you cannot display both." << endl;
                    cout << lowerBound << "      " << upperBound << endl;
                }
    return upperBound;
}

//Eliminate
void eliminate(int rowIndex, int columnIndex, int shownArray[SIZE][SIZE]){
    //Set all values within the column to zero
    for(int i = 0; i < SIZE; ++i){
        shownArray[i][columnIndex] = 0;
    }
    //Set all values within the row to zero
    for(int j = 0; j < SIZE; ++j){
        shownArray[rowIndex][j] = 0;
    }
}

//Checks if all values in the array are 0
bool allZeros(int randomArray[SIZE][SIZE]){
    bool resultOfStatement;
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            if(randomArray[i][j] != 0){
                return false;
            } 
        }
    }
    return true;
}

//Allows user to guess the array values
void guess(int hiddenArray[SIZE][SIZE], int shownArray[SIZE][SIZE], int &numPoints, int lowerBound, int upperBound, int randomNumber1, int randomNumber2){
    int usersGuess;
    cout << "Enter your guess: ";
    cin >> usersGuess;

    //No Bound Right Guess
     if (lowerBound == -1 && upperBound == -1){
        bool found = false;
        for(int i = 0; i < SIZE; ++i){
            for(int j = 0; j < SIZE; ++j){
                if(hiddenArray[i][j] == usersGuess){
                    eliminate(i, j, shownArray);
                    numPoints += 5;
                    cout << "You guessed correctly. You get 5 points." << endl;
                    showMatrix(shownArray);
                    cout << "Your remaining points = " << numPoints << endl;
                    cout << lowerBound << "      " << upperBound << endl;
                    found = true;
                }
            }             
        }
        if(!found) {
            numPoints -= 5;
            cout << "You guessed incorrectly. You lost 5 points" << endl;
            showMatrix(shownArray);
            cout << "Your remaining points = " << numPoints << endl;
            cout << lowerBound << "      " << upperBound << endl;
        }
     }
    
    if (lowerBound != -1 || upperBound != -1){
        bool found = false;
        for(int i = 0; i < SIZE; ++i){
            for(int j = 0; j < SIZE; ++j){
                if(hiddenArray[i][j] == usersGuess){
                    eliminate(i, j, shownArray);
                    numPoints += 1;
                    cout << "You guessed correctly. You get 1 point" << endl;
                    showMatrix(shownArray);
                    cout << "Your remaining points = " << numPoints << endl;
                    cout << lowerBound << "      " << upperBound << endl;
                    found = true;
                    break;
                }
            }
        }
        if(!found) {
            numPoints -= 10;
            cout << "You guessed incorrectly. You lost 10 points" << endl;
            showMatrix(shownArray);
            cout << "Your remaining points = " << numPoints << endl;
            cout << lowerBound << "      " << upperBound << endl;
        }
     }
}

//Sets the starting parameters of the game
void initialize(int &randomNumber1, int &randomNumber2, int &lowerBound, int &upperBound, int hiddenMatrix[SIZE][SIZE], int shownMatrix[SIZE][SIZE]){
    //Generate lower bound and upper bound
    srand(time(NULL));
    randomNumber1 = rand () % (249 - 150 + 1) + 150; // the smaller number (lower bound)
    randomNumber2 = rand () % (349 - 250 + 1) + 250; // the larger number

     //Two integers with -1 (showcaseing potential left bound and right bound)
    lowerBound = -1;
    upperBound = -1;

    //Call function genHideMatrix to generate hidden array
    genHideMatrix(hiddenMatrix);

    //Call function genShowMatrix to generate displayed array
    genShowMatrix(shownMatrix);
}

int main() 
{
    //Call Introduction function to Begin format of the Game
    introduction();

    //Declare Number of Starting Points
    int numPoints = 100;

    //Declare Lower and Upper Bound (numbers and displayed), create arrays
    int lowerBound;
    int upperBound;
    int randomNumber1;
    int randomNumber2;
    int hiddenMatrix[SIZE][SIZE];
    int shownMatrix[SIZE][SIZE];

    //Call Initialize Function to Set Game Parameters
    initialize(randomNumber1, randomNumber2, lowerBound, upperBound, hiddenMatrix, shownMatrix);

    //Ask for Players Name & Call getName function & show usersName
    string userName;
    cout << "Enter your name: ";
    getline(cin, userName);
    string playersName = getName(userName);
    cout << "Welcome to the game " << playersName << endl; 
    cout << lowerBound << "      " << upperBound << endl;

    //Display Menu & Give User an Option
    int menuChoice;
    while(menuChoice != 5){
        cout << endl;
        cout << "Menu: " << endl;
        cout << "1. Display Left Number" <<endl;
        cout << "2. Display Right Number" << endl;
        cout << "3. Guess a number in between" << endl;
        cout << "4. Change numbers" << endl;
        cout << "5. Exit" << endl; 
        cout << "What do you want to do? ";
        cin >> menuChoice;

        //Switch Statement Based Off of Users Choice Above
        switch(menuChoice){
            case DisplayLeft:
                setDisplayLeft(lowerBound, upperBound, randomNumber1);
                break;
            
            case DisplayRight:
                setDisplayRight(lowerBound, upperBound, randomNumber2);
                break;

            case Guess:
                showMatrix(shownMatrix);
                guess(hiddenMatrix, shownMatrix, numPoints, lowerBound, upperBound, randomNumber1, randomNumber2);
                //Check to see if the user has won
                char continueGame;
                if(allZeros(shownMatrix) == true) {
                    cout << "You Won!!!" << endl;
                    cout << "Do you want to play another game? Y/N: " << endl;
                    cin >> continueGame;
                    if(continueGame == 'Y'){
                        initialize(randomNumber1, randomNumber2, lowerBound, upperBound, hiddenMatrix, shownMatrix);
                    } else {
                        cout << "Bye " << playersName << endl;
                        cout << "Your final points balance = " << numPoints << endl;
                    }
                }
                break;

            case Change:
                numPoints -= 1;
                cout << "You lose 1 point for changing the boundaries." << endl;
                cout << "Your remaining points = " << numPoints << endl;
                initialize(randomNumber1, randomNumber2, lowerBound, upperBound, hiddenMatrix, shownMatrix);
                break;

            case Exit:
                cout << "Bye " << playersName << "!!!" << endl;
                    cout << "Your final points balance = " << numPoints;
                break;

            default:
                cout << "Wrong choice. Enter again." << endl;
                cout << lowerBound << "      " << upperBound << endl;
                break;
        }
    }
return 0; 
}