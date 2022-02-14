/*
 * The Monty Hall Problem Game
 * Created on May 10, 2015, approx. 3 hours.
 *
 * Note: There may have been better ways to do some of these things, but I just
 * learned C++ as far as arrays go and that's it. I'm not advanced in it yet.
 *
 * I only designed this program so I could test it out if switching
 * doors will make you win more than not switching, which is true.
 */

#include <iostream>
#include <string>       //used for the strings
#include <ctime>        //used for the time() function
#include <cstdlib>      //used for the rand() and sran() functions
using namespace std;

//Function Prototypes
void printDoors();
void randomizeDoors(int &door1, int &door2, int &door3, const int MAXPRIZE, const int MINPRIZE);
void chooseDoor(int &doorChoice);
void getDoors(int doorChoice, int door1, int door2, int door3, int &openedDoor, const int MAXPRIZE, const int MINPRIZE, int &winningDoor, int &unopenedDoor);
void doSwitchDoors(int unopenedDoor, int doorChoice, char &choice);
void didWin(string name, char choice, int doorChoice, int winningDoor, int unopenedDoor, int &switched, int &wins, int &losses);

int main() {
    
    //Start of the Variables
    int game = 1, gamesToPlay = 0, wins = 0, losses = 0, switched = 0;
    //A 1 and 2 is a goat, a 3 is a car
    int door1 = 0, door2 = 0, door3 = 0;
    int doorChoice = 0, openedDoor = 0, winningDoor = 0, unopenedDoor = 0;
    char choice;
    string name;
    //Random Variables
    const int MAXPRIZE = 3; //3 = car
    const int MINPRIZE = 1; //1, 2 = goat
    unsigned long seed = time(0);
    srand(seed);
    
    
    /////******************* INTRO BEGINS HERE *******************/////
    cout << "\t\t\tLet's Make a Deal Game Show\n\n";
    
    //Asks the user how many games they want to play
    do {
        cout << "How many games do you want to play (1-100)? ";
        cin >> gamesToPlay;
        if (gamesToPlay < 1 || gamesToPlay > 100)
            cout << "Invalid Input.\n\n";
    } while (gamesToPlay < 1 || gamesToPlay > 100);
    cin.ignore();   //to ignore the enter
    
    cout << "\nHello contestant! Welcome to Let's Make a Deal!\n";
    cout << "Before we begin, what is your name? ";
    getline(cin, name);
    
    //Check if the User Knows How to Play
    do {
        cout << "\nWell " << name << ", do you know how to play (Y/N)? ";
        cin >> choice; cin.ignore();
        if ((choice != 'Y' && choice != 'y') && (choice != 'N' && choice != 'n'))
            cout << "Invalid input.\n";
    } while ((choice != 'Y' && choice != 'y') && (choice != 'N' && choice != 'n'));
    
    //Shows the Instructions if user chose no
    if (choice == 'n' || choice == 'N') {
        cout << "\nHere's how you play. I'm going to show you three doors. 1 has a new car and 2 have goats. You have to\n";
        cout << "guess which door has the car. After you choose, I'm going to open a door that has a goat. Then, I'll ask\n";
        cout << "you if you want to switch to the other unopened door. Got it? Alright, let's get ready to play!\n\n";
    }
    /////******************* INTRO ENDS HERE *******************/////
    
    
    //////////******************* GAME BEGINS HERE *******************//////////
    do {
        //Introduction of the Game and what game number
        cout << "\nGame " << game << ": 2 doors have a goat and 1 door has a car.\n";
        
        //Calls the printDoors Function to print the doors
        printDoors();
        
        //Calls the randomizeDoors Function to assigns random numbers to the doors
        randomizeDoors(door1, door2, door3, MAXPRIZE, MINPRIZE);
        
        //Calls the chooseDoor Function to ask the user what door they want
        chooseDoor(doorChoice);
        
        //Show what door the user selected
        cout << name << " has chosen door number " << doorChoice << "!\n";
        
        //Calls the openDoor Function to determine what is opened and not opened
        getDoors(doorChoice, door1, door2, door3, openedDoor, MAXPRIZE, MINPRIZE, winningDoor, unopenedDoor);
        
        //Show the door that the host has opened
        cout << "Well " << name << ", I'm going to open door number " << openedDoor << ", which has a goat.\n";
        
        //Calls the doSwitchDoors Fnction to check if the user wants to switch door
        doSwitchDoors(unopenedDoor, doorChoice, choice);
        
        //Calls the didWin Function to check if the user is a winner
        didWin(name, choice, doorChoice, winningDoor, unopenedDoor, switched, wins, losses);
        
        //Display the Statistics at the end of the game
        cout << endl;
        game++;
        cout << "Wins: " << wins << endl;
        cout << "Losses: " << losses << endl;
        cout << "Switched: " << switched << endl;
        
        //Resets Variables Just to be safe no number from 1-3 is there
        doorChoice = 0;
        openedDoor = 0;
        unopenedDoor = 0;
        winningDoor = 0;
        
    } while (game <= gamesToPlay);
    cout << endl;
    //////////****************** GAME ENDS HERE ********************//////////
    cout << "The game is now over.\n";
    
    //End of the Program
    return 0;
}



//printDoors Function
void printDoors() {
    //Just prints the doors
    cout << endl;
    cout << "\t\t-----\t\t-----\t\t-----\n";
    cout << "\t\t|   |\t\t|   |\t\t|   |\n";
    cout << "\t\t| 1 |\t\t| 2 |\t\t| 3 |\n";
    cout << "\t\t|   |\t\t|   |\t\t|   |\n";
    cout << "\t\t-----\t\t-----\t\t-----\n";
    cout << endl;
}



//randomizeDoors Function
void randomizeDoors(int &door1, int &door2, int &door3, const int MAXPRIZE, const int MINPRIZE) {
    
    /* Randomly assigns any door any number from 1 to 3 and will continue to
     * do so if and only if none of the doors have a matching number.
     * This is to assign a prize to each door with 1 and 2 being goats, and 3 being a car.
     */
    
    do {
        door1 = (rand() % (MAXPRIZE - MINPRIZE + 1)) + MINPRIZE;
        door2 = (rand() % (MAXPRIZE - MINPRIZE + 1)) + MINPRIZE;
        door3 = (rand() % (MAXPRIZE - MINPRIZE + 1)) + MINPRIZE;
    } while (door1 == door2 || door2 == door3 || door3 == door1);
}



//choseDoor Function
void chooseDoor(int &doorChoice) {
    
    //Asks the user which door they want to open
    do {
        cout << "Which door do you choose (1, 2, or 3)? ";
        cin >> doorChoice; cin.ignore();
        
        //If the user enters an invalid option
        if (doorChoice < 1 || doorChoice > 3)
            cout << "Invalid Input.\n";
        
    } while (doorChoice < 1 || doorChoice > 3);
}



//openDoor Function
void getDoors(int doorChoice,int door1, int door2, int door3, int &openedDoor, const int MAXPRIZE, const int MINPRIZE, int &winningDoor, int &unopenedDoor) {
    
    //Start of the Variables
    int leftOverDoor1, leftOverDoor2;
    
    //Check which door is the winning door
    if (door1 == 3) winningDoor = 1;
    if (door2 == 3) winningDoor = 2;
    if (door3 == 3) winningDoor = 3;
    
    //Finds out which door isn't opened by randomly giving it a number from 1 to 3
    //and will continue to do so as long as the number doesn't equal the user's chosen door
    do {
        leftOverDoor1 = (rand() % (MAXPRIZE - MINPRIZE + 1)) + MINPRIZE;
    } while (leftOverDoor1 == doorChoice);
    
    /*Finds out which other door isn't opened by randomly giving it a number from 1 to 3
     *and will continue to do so as long as it is not the first unopened door and it
     *isn't the user's chosen door */
    do {
        leftOverDoor2 = (rand() % (MAXPRIZE - MINPRIZE + 1)) + MINPRIZE;
    } while (leftOverDoor2 == doorChoice || leftOverDoor2 == leftOverDoor1);
    
    //Will randomly assign a number from 1 to 3 and will continue to do so as long as it
    //does not equal the user's chosen door and the winning door.
    do {
        openedDoor = (rand() % (MAXPRIZE - MINPRIZE + 1)) + MINPRIZE;
    } while (openedDoor == doorChoice || openedDoor == winningDoor);
    
    //Figures out which door to open of the 2 unopened doors between 1 to 3 and
    //will continue to do so until it doesn't equal the user's door or opened door
    do {
        unopenedDoor = (rand() % (MAXPRIZE - MINPRIZE + 1))  + MINPRIZE;
    } while (unopenedDoor == doorChoice || unopenedDoor == openedDoor);
}



//doSwitchDoors Function
void doSwitchDoors(int unopenedDoor, int doorChoice, char &choice) {
    
    //Asks if the user wants to switch doors
    do {
        cout << "Do you want to switch to door number " << unopenedDoor << "? Your current choice is door number " << doorChoice << ". (Y/N)? ";
        cin >> choice;
        
        //Make sure the user didn't put an invalid option
        if ((choice != 'Y' && choice != 'y') && (choice != 'N' && choice != 'n'))
            cout << "Invalid input.\n";
        
    } while ((choice != 'Y' && choice != 'y') && (choice != 'N' && choice != 'n'));
}



//didWin Function
void didWin(string name, char choice, int doorChoice, int winningDoor, int unopenedDoor, int &switched, int &wins, int &losses) {
    cout << endl;
    
    //
    if (choice == 'n' || choice == 'N') {
        if (doorChoice == winningDoor) {
            cout << "Congratulations " << name << ", you just won a brand new car!" << endl;
            wins++;
            
        } else {
            cout << "I'm sorry but door number " << doorChoice << " has a goat!" << endl;
            losses++;
        }
    } else {
        doorChoice = unopenedDoor;
        switched++;
        if (doorChoice == winningDoor) {
            cout << "Congratulations " << name << ", you just won a brand new car!" << endl;
            wins++;
        } else {
            cout << "I'm sorry but door number " << doorChoice << " has a goat!" << endl;
            losses++;
        }
    }
}
