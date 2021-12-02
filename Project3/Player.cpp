//Project 3
//Grace Ohlsen and Justin Jamrowski
#include "Player.h"
#include <iostream>
using namespace std;


// Default Constructor for Player
Player::Player()
{
    name = "Player";
    numSteps = 0;
    numItemsStored = 0;
    wonGame = false;
}

// sets name of Player
void Player::setName(string newName)
{
    name = newName;
}

// gets name of Player
string Player::getName()
{
    return name;
}

// adds one step to numSteps
void Player::addStep()
{
    numSteps++;
}

// get numSteps of Player
int Player::getSteps()
{
    return numSteps;
}

/*
This function takes in a string object and if it isn't already stored, stores it in the inventory array
Parameters - string object (object to be stored in inventory)
Return - bool (if object was added to inventory)
*/
bool Player::addToInventory(string object)
{

    // check if the string is already stored in inventory
    bool alreadyStored = false;
    for(int i = 0; i < numItemsStored; i++){
        if(inventory[i]==object){
            alreadyStored = true;
        }
    }

    // if the string isn't already in inventory, add it
    if(alreadyStored != true){
        inventory[numItemsStored] = object;
        numItemsStored++;
        return true;
    }
    // if the string is already in inventory, do not add it to inventory
    else{
        return false;
    }
    

}

/*
This function prints the player inventory
Parameters - n/a
Return - n/a... just prints to terminal
*/
void Player::printInventory()
{
    // goes through inventory array up to number of items stored and prints them out
    cout << "[ " ;
    for(int i = 0; i < numItemsStored; i++){
        cout << getObjectAt(i) ;
        if(i != numItemsStored - 1){
            cout << ", ";
        }
    }
    cout << " ]\n" << endl;
}

// returns string of object at passed index
string Player::getObjectAt(int index)
{
    return inventory[index];
}

// returns status of game... if won or not
bool Player::getGameStatus()
{
    return wonGame;
}

// sets status of game... won or loss
void Player::setGameStatus(bool status){
    wonGame = status;
}


/*
This function prints the stats (name, game status, and number of steps) of the player
Parameters - n/a
Return - n/a... just prints to terminal
*/
void Player::getPlayerStats(){
    // player name
    cout << "Player: " << name << ", ";
    
    // game status
    if(wonGame == false){
        cout << "Lost, " ;
    }else if(wonGame ==  true){
        cout << "Won, " ;
    }

    // number of steps
    cout << "Number of Steps: " << numSteps << endl;
}

// returns the number
int Player::getNumItemsStored(){
    return numItemsStored;
}