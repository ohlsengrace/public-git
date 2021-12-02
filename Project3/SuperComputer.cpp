//Project 3
//Grace Ohlsen and Justin Jamrowski
#include "SuperComputer.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;


/*
This function prints out a vector of size vSize using recursion
Parameters - vector<int> v, int vSize (size of v vector)
Return - void, just prints out vector
*/
void printVector(vector<string> v, int vSize){
    if(vSize < 1){
        cout << "\n";
        return;
    }
    else
    {
        cout << v.at(vSize - 1)  << "\n";
        printVector(v, vSize - 1);
        return;
    }
}

/*
This function takes in a maximum and returns a random integer between 0 and the max.
Parameters - int max
Return - random number between 0 and max
*/
int getRandoNum(int max)
{    
    int randNum = 0;
    
    randNum = rand() % max;
    return randNum;
}

SuperComputer::SuperComputer(){
    wonGame = false;
    passwordToDestroy = "";
    fileName = "";
}

SuperComputer::SuperComputer(string password, string file){
    wonGame = false;
    passwordToDestroy = password;
    fileName = file;

    // random number of lines between 5-20 
    // each line has random 20-digit string
    srand(time(NULL));

    int numLines = getRandoNum(15) + 5;
    
    for(int i = 0; i < numLines; i++)
    {
        string temp = "";
        
        for(int j = 0; j < 20; j++)
        {
            temp += to_string(getRandoNum(10));
        }
        fileContent.push_back(temp);
    }
}

void SuperComputer::setWonGame(bool status){
    wonGame = status;
}

bool SuperComputer::getGameStatus(){
    return wonGame;
}

void SuperComputer::setPasswordToDestroy(string password){
    passwordToDestroy = password;
}

string SuperComputer::getPasswordToDestroy(){
    return passwordToDestroy;
}

void SuperComputer::setFileName(string file){
    fileName = file;
}

string SuperComputer::getFileName(){
    return fileName;
}

bool SuperComputer::fileContentMatches(string file)
{
    vector<string> tempVector;
    bool contentMatches = false;
    
    
        ifstream in;
        in.open(file);

        if(in.is_open())
        {
            in.seekg(0, ios::end);
            unsigned long long last_pos = in.tellg();

            if(last_pos != 0)
            {
                string line = "";
                
                in.seekg(0, ios::beg);

                while(getline(in, line))
                {
                    tempVector.push_back(line);
                }

                if(tempVector == fileContent)
                {
                    printVector(tempVector, tempVector.size());
                    contentMatches = true;
                }
            }
            
        }
        
    
    return contentMatches;
}

vector<string> SuperComputer::getFileContent()
{
    return fileContent;
}
