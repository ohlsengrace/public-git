//Project 3
//Grace Ohlsen and Justin Jamrowski
#ifndef PLAYER
#define PLAYER
#include <iostream>
using namespace std;

class Player
{
    public:
    Player();
    
    
    void setName(string newName);
    string getName();
    void addStep();
    int getSteps();
    bool addToInventory(string object);
    void printInventory();
    string getObjectAt(int index);
    bool getGameStatus();
    void setGameStatus(bool);
    void getPlayerStats();
    int getNumItemsStored();

    private:
    string name;
    int numSteps;
    static const int INVENTORY_SIZE = 3;
    string inventory[INVENTORY_SIZE];
    int numItemsStored;
    bool wonGame;

};


#endif