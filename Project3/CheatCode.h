//Project 3
//Grace Ohlsen and Justin Jamrowski
#ifndef CHEATCODE
#define CHEATCODE
#include <iostream>
using namespace std;

class CheatCode
{
    public:
    CheatCode();
    CheatCode(int x,int y);
    void printCheatCode();
    int getXCoord();
    int getYCoord();

    private:
    int xCoord;
    int yCoord;
};


#endif