//Project 3
//Grace Ohlsen and Justin Jamrowski
#ifndef GAMEROOM
#define GAMEROOM
#include <iostream>
#include <vector>
using namespace std;

class GameRoom
{
    public:
    GameRoom();
    bool hangman();
    bool trivia();
    string getHangmanWord();
    string getFileName();
    vector<string> getFileContent();

    private:
    bool wonHangman;
    bool wonTrivia;
    string hangmanWord;
    string fileName;
    vector<string> fileContent;
};

#endif