//Project 3
//Grace Ohlsen and Justin Jamrowski
#ifndef SUPERCOMPUTER
#define SUPERCOMPUTER

#include <iostream>
#include <vector>
using namespace std;

class SuperComputer
{
    public:
    SuperComputer();
    SuperComputer(string password, string file);
    void setWonGame(bool status);
    bool getGameStatus();

    void setPasswordToDestroy(string password);
    string getPasswordToDestroy();
    void setFileName(string file);
    string getFileName();
    bool fileContentMatches(string file);
    vector<string> getFileContent();

    private:
    bool wonGame;
    string passwordToDestroy;
    string fileName;
    vector<string> fileContent;

};

#endif