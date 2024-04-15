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
string getName (string usersName) {
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
int genShowMatrix(int randomNumbers[SIZE][SIZE]) {
    //Loop to initialize all values within the array to "-1"
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j) {
            randomNumbers[i][j] = -1;
        }
    }
    return randomNumbers[SIZE][SIZE];
}

//Initialize the Hidden Array
int genHideMatrix(int hiddenNumbers[SIZE][SIZE]) {
    srand(time(NULL));
    for (int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
            hiddenNumbers[i][j] = rand () % 101 + 100;
        }
    }
    return hiddenNumbers[SIZE][SIZE];
}

//Used to display the corressponding 2D array
int showMatrix(int displayedMatrix[SIZE][SIZE]){
    genHideMatrix(displayedMatrix);
    cout << displayedMatrix;
    return displayedMatrix[SIZE][SIZE];
}

//Showcase the Left Number if Prompted
int setDisplayLeft(int leftBound, int rightBound, int randomNumber1) {
     if (leftBound == -1 && rightBound == -1){
                    cout << "You will only get 1 point for guessing correctly and lose 10 points " << endl;
                    cout << "for guessing incorrectly, now." << endl;
                    leftBound = randomNumber1;
                    cout << leftBound << "      " << rightBound << endl;
                } else {
                    cout << "You have already displayed the right boundary, you cannot display both." << endl;
                    cout << leftBound << "      " << rightBound << endl;
                }
    return leftBound;
}

//Showcase the Right Number if Prompted
int setDisplayRight(int leftBound, int rightBound, int randomNumber2){
    if (leftBound == -1 && rightBound == -1) {
                    cout << "You will only get 1 point for guessing correctly and lose 10 points " << endl;
                    cout << "for guessing incorrectly, now." << endl;
                    rightBound = randomNumber2;
                    cout << leftBound << "      " << rightBound << endl;
                } else {
                    cout << "You have already displayed the left boundary, you cannot display both." << endl;
                    cout << leftBound << "      " << rightBound << endl;
                }
    return rightBound;
}

//Eliminate
int eliminate(int randomArray[SIZE][SIZE], int rowIndex, int columnIndex){
    //Set all values within the column to zero
    for(int i = 0; i < SIZE; ++i){
        randomArray[i][columnIndex + 1] = 0;
    }
    //Set all values within the row to zero
    for(int j = 0; j < SIZE; ++j){
        randomArray[rowIndex + 1][j] = 0;
    }
    return randomArray[SIZE][SIZE];
}

//Checks if all values in the array are 0
int allZeros(int randomArray[SIZE][SIZE]){
    bool resultOfStatement;
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; ++j){
            if(randomArray[i][j] == 0){
                resultOfStatement = true;
            } else {
                resultOfStatement = false;
            }
        }
    }
return resultOfStatement;
}

//Allows user to guess the array values
void guess(int randomArray[SIZE][SIZE], int usersGuess, int numPoints, int leftBound, int rightBound, int randomNumber1, int randomNumber2){
    //No Bound Right Guess
     if (leftBound == -1 && rightBound == -1){
        for(int i = 0; i < SIZE; ++i){
            for(int j = 0; j < SIZE; ++j){
                if(randomArray[i][j] == usersGuess){
                    eliminate(randomArray, i, j);
                    numPoints += 5;
                    cout << "You guessed correctly. You get 5 points." << endl;
                }
            }
        }
     }

    //No Bounds Wrong Guess
    if (leftBound == -1 && rightBound == -1) {
        numPoints -= 5;
       cout << "You gussed incorrectly. You lost 5 points" << endl;
    }

    //Bound Displayed Right Guess
    if (leftBound != -1 || rightBound != -1) {
        for(int i = 0; i < SIZE; ++i){
            for(int j = 0; j < SIZE; ++j){
                if(randomArray[i][j] == usersGuess){
                    eliminate(randomArray, i, j);
                    numPoints += 1;
                    cout << "You guessed correctly. You get 1 point." << endl;
                }
            }
        }
    }

    //Bound Displayed Wrong Guess
    if (leftBound != -1 || rightBound != -1) {
       numPoints -= 10;
       cout << "You guessed incorrectly. You lost 10 points" << endl;
    }
}

//Sets the starting parameters of the game
void initialize(int randomNumber1, int randomNumber2, int lowerBound, int upperBound, int hiddenMatrix[SIZE][SIZE], int shownMatrix[SIZE][SIZE]){
    //Generate lower bound and upper bound
    srand(time(NULL));
    randomNumber1 = rand () % (250 - 151 + 1) + 151; // the smaller number (lower bound)
    randomNumber2 = rand () % (250 - 151 + 1) + 151; // the larger number
     while (randomNumber1 > randomNumber2) {
        randomNumber2 = rand () % 101 + 100; //Generate lower bound
    }

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
    int hiddenArray[SIZE][SIZE];
    int shownArray[SIZE][SIZE];

    //Call Initialize Function to Set Game Parameters
    initialize(randomNumber1, randomNumber2, lowerBound, upperBound, hiddenArray, shownArray);

    //Ask for Players Name & Call getName function & show usersName
    string userName;
    cout << "Enter your name: ";
    getline(cin, userName);
    string playersName = getName(userName);
    cout << "Welcome to the game " << playersName << endl; 

    //Display Menu & Give User an Option
    int menuChoice;
    cout << endl;
    cout << "Menu: " << endl;
    cout << "1. Display Left Number" <<endl;
    cout << "2. Display Right Number" << endl;
    cout << "3. Guess a number in the range (inclusive)" << endl;
    cout << "4. Change numbers" << endl;
    cout << "5. Exit" << endl; 
    cout << "Your choice: ";
    cin >> menuChoice;

    //Switch Statement Based Off of Users Choice Above

    //Showcase Rows & Columns of Random Numbers
    int randomNumbers[SIZE][SIZE];
    genShowMatrix(randomNumbers);
    //Print Array
    for(int i = 0; i < SIZE; ++i){
        for (int j = 0; j < SIZE; ++j){
        cout << randomNumbers[i][j] << " ";
        }
        cout << endl;
    }




    return 0; 
}