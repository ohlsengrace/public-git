//Project 3
//Grace Ohlsen and Justin Jamrowski
#include "Lobby.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

/*
This function takes in a string and returns it in its uppercase form
Parameters - string input (string w/ possible lowercase letters)
Return - string off input uppercases
*/
string uppercase(string input){
    int length = input.length();
    for (int i = 0; i < length; i++){
        
        if(input.at(i) >= 97 && input.at(i) <= 122){
            input.at(i) = (char)(input.at(i) - 32);
        }

    }
    return input;
}

/*
This function takes in a maximum and returns a random integer between 0 and the max.
Parameters - int max
Return - random number between 0 and max
*/
int getRandomNum(int max)
{    
    int randNum = 0;
    
    randNum = rand() % max;
    return randNum;
}

// default constructor for Lobby
Lobby::Lobby()
{
    // randomly generated, shouldn't use this constructor
    passwordToRoomThree = "testing password"; 
    destroyComputerCode = "testing code";
}

Lobby::Lobby(string hangmanWord){
    passwordToRoomThree = hangmanWord;
    destroyComputerCode = ""; // randomize, 9 digit code

    int max = 10;
    srand(time(NULL));

    // make destroyComputerCode a random 9-digit string
    for(int i = 0; i < 9; i++)
    {
        destroyComputerCode += to_string(getRandomNum(max));
    }
}

/*
This function gets the password to room three
Parameters - none
Return - string passwordToRoomThree 
*/
string Lobby::getPasswordToRoomThree()
{
    return passwordToRoomThree;
}

/*
This function gets the computer code that will destroy the SuperComputer
Parameters - none
Return - string destroyComputerCode (the code that destroys the SuperComputer)
*/
string Lobby::getDestroyComputerCode()
{
    return destroyComputerCode;
}   

/*
This function sets the password to room three
Parameters - string hangmanWord
Return - void
*/
void Lobby::setPasswordToRoomThree(string hangmanWord)
{
    passwordToRoomThree = hangmanWord;
}

/*
This function prints the chat of room one in the lobby
Parameters - n/a
Return - n/a... just prints to terminal
*/
void Lobby::printRoomOneChat()
{
    cout << "\nUser432: Isn't the MetaVerse great! Been waiting forever for it to finally come out. Virtual life is amazing!" << endl;
    cout << "Matt322: It's the best, this will be the greatest thing ever created for mankind." << endl;
    cout << "Josh211: Totally agree. This is the next step for the human race." << endl;
    cout << "Grace920: Right! I swear no one even uses their phones anymore. Just pop the glasses on and that is all you need.\n" << endl;
}

/*
This function prints the chat of room two in the lobby
Parameters - n/a
Return - n/a... just prints to terminal
*/
void Lobby::printRoomTwoChat()
{
    cout << "\nBryce892: Have you guys been to room three? Insane stuff in there." << endl;
    cout << "Winslow291: No.. is it some sort of like secret? Haven't heard of room three." << endl;
    cout << "Bryce892: Can't say much about it.. all I can say is Hangman was a blast to play! ;)\n" << endl;
}

/*
This function prints entrance to room three, gets user input, and if user input matches the password to room three, returns true
Parameters - n/a
Return - bool (if user input matched password to room three)
*/
bool Lobby::roomThreeEntrance()
{
    string input;
    cout << "\nEnter password for room three: ";
    cin >> input;

    // if password is correct, returns true
    if(uppercase(input) == uppercase(passwordToRoomThree))
    {
        return true;
    }
    // if password is incorrect, returns false
    else
    {
        return false;
    }
    
}

/*
This function prints the chat in room three of the lobby and returns the passwordToDestroy to defeat SuperComputer
Parameters - n/a
Return - string destroyComputerCode (password to defeat SuperComputer)
*/
string Lobby::printRoomThreeChat()
{
    cout << "\nHiddenUser: Fuck Zuckerberg.. this might be the worst thing ever created. It'll just isolate people even more." << endl;
    cout << "HiddenUser: Couldn't agree more." << endl;
    cout << "HiddenUser: Theres a group of people like us, they finally figured out the password to delete the MetaVerse." << endl;
    cout << "HiddenUser: " << destroyComputerCode << endl;
    cout << "** you jot down the password on a piece of paper and store it in your inventory\n" << endl;

    return destroyComputerCode;
}
