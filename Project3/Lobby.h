//Project 3
//Grace Ohlsen and Justin Jamrowski
#ifndef LOBBY_H
#define LOBBY_H
#include <iostream>
using namespace std;

class Lobby
{
    public:
    Lobby();
    Lobby(string hangmanWord);
    string getPasswordToRoomThree();
    string getDestroyComputerCode();
    void setPasswordToRoomThree(string hangmanWord);
    void printRoomOneChat();
    void printRoomTwoChat();
    bool roomThreeEntrance();
    string printRoomThreeChat();

    private:
    string passwordToRoomThree;
    string destroyComputerCode;
};

#endif