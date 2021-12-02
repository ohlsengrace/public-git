//Project 3
//Grace Ohlsen and Justin Jamrowski
#include "CheatCode.h"
#include <iostream>
using namespace std;

// Constructor for CheatCode
CheatCode::CheatCode()
{
    xCoord = -1;
    yCoord = -1;
}

// Parameterized Constructor for CheatCode
CheatCode::CheatCode(int x,int y){
    xCoord = x;
    yCoord = y;
}

/*
This function prints the coordinates of the virus in the game
Parameters - none
Return - void
*/
void CheatCode::printCheatCode()
{
    cout << "(" << xCoord + 1 << ", " << yCoord + 1 << ")" << endl;
}

/*
This function returns the x-coordinate of the virus
Parameters - none
Return - int xCoord (x-coordinate of virus)
*/
int CheatCode::getXCoord()
{
    return xCoord;
}

/*
This function returns the y-coordinate of the virus
Parameters - none
Return - int yCoord (y-coordinate of virus)
*/
int CheatCode::getYCoord()
{
    return yCoord;
}